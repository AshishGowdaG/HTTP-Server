#include <iostream>
#include "Socket.hpp"

int main(){
    try{
        Socket server;
        server.bind(8080);
        server.listen();
        Socket client = server.accept();
        std::string request = client.recv();
        std::cout<<request<<'\n';
        client.send(
            "HTTP/1.1 200 OK\r\n"
            "Content-Length: 5\r\n"
            "\r\n"
            "Hello"
        );
        std::cout<<"Response sent\n";
    }
    catch(const std::exception& e){
        std::cerr<<e.what()<<std::endl;
        return 1;
    }
    return 0;
}