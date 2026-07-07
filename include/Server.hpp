#pragma once

#include "Socket.hpp"
#include <cstdint>

class Server{
    public:
        explicit Server(uint16_t port=8080);
        void start();
    private:
        Socket sock;
        uint16_t port;
};