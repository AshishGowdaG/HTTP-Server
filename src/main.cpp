#include <iostream>
#include "Server.hpp"

int main(){
    try{
        Server server;
        server.start();
    }
    catch(const std::exception& e){
        std::cerr<<e.what()<<std::endl;
        return 1;
    }
    return 0;
}