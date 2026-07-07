#include "Server.hpp"
#include "Request.hpp"
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
        std::cout << "Method  : " << request.getMethod() << '\n';
        std::cout << "Path    : " << request.getPath() << '\n';
        std::cout << "Version : " << request.getVersion() << '\n';
        std::cout << "Host: "
          << request.getHeader("Host") << '\n';

        std::cout << "User-Agent: "
                << request.getHeader("User-Agent") << '\n';

        std::cout << "Fake: "
                << request.getHeader("Fake") << '\n';
        client.send(
            "HTTP/1.1 200 OK\r\n"
            "Content-Length: 5\r\n"
            "\r\n"
            "Hello"
        );
    }
}