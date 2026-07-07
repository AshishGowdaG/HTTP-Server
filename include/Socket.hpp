#pragma once
#include <cstdint>
#include <string>
#include <cstddef>
#include <sys/types.h>

class Socket{
    public:
        Socket();
        ~Socket();
        explicit Socket(int sockfd);
        //explicit is so that Socket s = 5 does not compile
        //cause the compiler might implicitly use the constructor
        //which takes int input. So only Socket s(5) works.
        Socket(const Socket&) = delete; 
        //removing the copy constructor so each socket is uniquely owned
        // Socket s2 = s1; is not possible
        Socket& operator=(const Socket&) = delete;
        //assignment operator cannot copy a socket either
        //Socket s1; Socket s2; s1 = s2; won't happen
        Socket(Socket&& other) noexcept;
        //move constructor
        //transfers ownership using std::move()
        //this has been set up to implement accept() since it
        //returns another socket and trying to assign it would fail
        //Above is not always true cause Copy Elision often requires
        //no move constructor as the object is directly called in the
        //caller's storage
        Socket& operator=(Socket&& other) noexcept;
        //noexcept allows STL to optimize operations on containers
        //like vectors because "nothing can fail in the moving opertation"
        //we copy one integer and set the othet to -1
        void bind(uint16_t port);
        //unsigned 16 bit integer or short
        void listen(int backlog=10);
        //non blocking
        //tells the os that it can queue <=backlog amount of
        //items at this socket
        Socket accept();
        //blocking 
        //blocks until a valid client connects and returns a 
        //new socket
        std::string recv(size_t buffer_size = 4096);
        //0 means the connection is properly terminated
        void send(const std::string& data);
        //ssize_t is signed size_t. Allows -1 on error. (size_t>=0)
    private:
        int sockfd{-1};
};