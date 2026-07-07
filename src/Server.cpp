#include "Server.hpp"
#include <iostream>

Server::Server(uint16_t port)
    : port(port)
{}

void Server::start(){
    sock.bind(port);
    sock.listen();

    while(true){
        Socket client = sock.accept();
        std::string request = client.recv();
        std::cout<<request<<"\n";
        client.send(
            "HTTP/1.1 200 OK\r\n"
            "Content-Length: 5\r\n"
            "\r\n"
            "Hello"
        );
        std::cout<<"Response sent\n";
    }
}