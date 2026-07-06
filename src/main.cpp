#include <iostream>
#include "Socket.hpp"

int main(){
    try{
        Socket server;
        server.bind(8080);
        server.listen();
        std::cout<<"Listening on 8080...\n";
        Socket client = server.accept();
        std::cout<<"Client connected\n";
    }
    catch(const std::exception& e){
        std::cerr<<e.what()<<std::endl;
        return 1;
    }
    return 0;
}