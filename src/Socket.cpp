#include "Socket.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdexcept>

Socket::Socket()
    : sockfd(socket(AF_INET, SOCK_STREAM, 0))
    //member initialiser list same as sockfd = socket(.);
    //better cause data members are intialised before constructor runs
    //hence it will first initalise sockfd=-1 and then try to give it 
    //the new value
{
    if(sockfd==-1) throw std::runtime_error("New Socket Error");
    
    int yes = 1;
    if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,
        sizeof(yes)) == -1) {
        throw std::runtime_error("setsockopt() failed");
    }
    //TCP Connection doesn't terminate immedaitely due to TIME_WAIT
    //if server turns off and on, bind fails due to this
    //Error: Address already in use
}

Socket::~Socket(){
    if(sockfd!=-1) close(sockfd);
}

Socket::Socket(int sockfd)
    : sockfd(sockfd)
{}

Socket::Socket(Socket&& other) noexcept
    : sockfd(other.sockfd)
{
    other.sockfd = -1;
}
//transfers ownership when new object is being created 
//and the other object already exists
//Socket s1(5); Socket s2(std::move(s1)) or Socket s2 = std::move(s1)
//Socket&& refers to the r value which means other is a temporary
//value(properties can be stolen). std::move takes a socket object and 
//makes it temporary 
//the compiler then knows it has to invoke move constructor as it
//is given a temporary value and it accepts r value type 
//R value- Readable/Right values
//if Socket& were written then it is called l(location) value


Socket& Socket::operator=(Socket&& other) noexcept{
    if(this!=&other){
        if(sockfd!=-1) close(sockfd);
        sockfd = other.sockfd;
        other.sockfd = -1;
    }
    return *this;
}
//transfers ownership during assignment when both objects exist
//Socket s1; Socket s2; s1 = std::move(s2);


void Socket::bind(uint16_t port){
    sockaddr_in serv_addr{};
    // {} is used to set bytes to zero same as memset in C
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    //uses long form of hton cause ipv4 is 32 bits while port is 16

    if(::bind(sockfd, reinterpret_cast<sockaddr*>(&serv_addr), 
        sizeof(serv_addr))==-1){
        throw std::runtime_error("Socket bind failed");
    }
    //reinterpret_cast is same as (sockaddr*)(&serv_addr) in C
}

void Socket::listen(int backlog){
    if(::listen(sockfd, backlog)==-1){
        throw std::runtime_error("Listen failed");
    }
}

Socket Socket::accept(){
    int client = ::accept(sockfd, nullptr, nullptr);
    if(client==-1) throw std::runtime_error("Accept failed");
    return Socket(client);
}


