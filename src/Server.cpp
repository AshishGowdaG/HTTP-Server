#include "Server.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include <iostream>

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
        response.setHeader("Content-Type", "text/plain");
        response.setBody("Hello");
        client.send(response.toString());
    }
}