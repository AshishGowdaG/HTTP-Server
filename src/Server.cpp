#include "Server.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "MimeTypes.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <thread>

Server::Server(uint16_t port)
    : port(port)
{}

void Server::handleClient(Socket client){
    Request request(client.recv());
    Response response;
    if(!request.isValid()){
        response.setStatus(400);
        response.setHeader("Content-Type", "text/plain");
        response.setBody("400 Bad Request");
    }
    else if(request.getMethod() != "GET" && 
            request.getMethod() != "HEAD" &&
            request.getMethod() != "OPTIONS"
    ) 
    {
        response.setStatus(405);
        response.setHeader("Allow", "GET");
        response.setHeader("Content-Type", "text/plain");
        response.setBody("405 Method Not Allowed");
    }
    else if(request.getMethod() == "OPTIONS"){
        response.setStatus(204);
        response.setHeader("Allow", "GET, HEAD, OPTIONS");
        response.setBody("");
    }
    else{
        std::string path = request.getPath();
        if(path.find("..") != std::string::npos){
            response.setStatus(403);
            response.setHeader("Content-Type", "text/plain");
            response.setBody("403 Forbidden");
        }
        //if the path is something like public/../whatever 
        //this will allow access outside public
        else{
            if(path=="/") path = "/index.html";
            path = "public" + path;
            std::ifstream file(path);
            if(file){
                std::ostringstream buff;
                
                buff << file.rdbuf();
                response.setHeader("Content-Type", MimeTypes::get(path));
                response.setBody(buff.str());
            }
            else{
                response.setStatus(404);
                response.setHeader("Content-Type", "text/plain");
                response.setBody("File misnamed or does not exist");
            }
        }
    }
    auto now = std::chrono::system_clock::now();
    std::time_t curr = std::chrono::system_clock::to_time_t(now);
    {
    std::lock_guard<std::mutex> lock(logMutex);
    std::cout << "["
        << std::put_time(std::localtime(&curr), "%Y-%m-%d %H:%M:%S")
        << "] "
        << request.getMethod() << " "
        << request.getPath()
        << " -> Response: "
        << response.getStatus()
        << " "
        << response.reason(response.getStatus())
        << '\n';
    }
    client.send(response.toString(request.getMethod() != "HEAD"));   
}

void Server::start(){
    sock.bind(port);
    sock.listen();
    while(true){
        Socket client = sock.accept();
        std::thread(&Server::handleClient, this, std::move(client)).detach();
    }
}