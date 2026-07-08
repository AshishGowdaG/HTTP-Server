#include "Server.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "MimeTypes.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>

Server::Server(uint16_t port)
    : port(port)
{}

void Server::start(){
    sock.bind(port);
    sock.listen();

    while(true){
        Socket client = sock.accept();
        Request request(client.recv());
        Response response;
        std::string path = request.getPath();
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
        client.send(response.toString());

    }
}