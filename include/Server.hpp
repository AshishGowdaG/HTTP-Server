#pragma once

#include "Socket.hpp"
#include <cstdint>
#include <mutex>

class Server{
    public:
        explicit Server(uint16_t port=8080);
        void handleClient(Socket client);
        void start();
    private:
        Socket sock;
        uint16_t port;
        std::mutex logMutex;
};