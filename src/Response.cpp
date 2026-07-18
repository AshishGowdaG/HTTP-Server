#include "Response.hpp"
#include <sstream>

Response::Response()
    : version("HTTP/1.1"), status(200)
{
    headers["Connection"] = "close";
}

void Response::setStatus(int code){
    status = code;
}

void Response::setHeader(const std::string& key, const std::string& value){
    headers[key] = value;
}

void Response::setBody(const std::string& body){
    this->body = body;
    headers["Content-Length"] = std::to_string(body.size());
}

std::string Response::reason(int code){
    switch(code){
        case 200:
            return "OK";
        case 400:
            return "Bad Request";
        case 403:
            return "Forbidden";
        case 404:
            return "Not Found";
        case 405:
            return "Method Not Allowed";
        case 500:
            return "Internal Server Error";
        default:
            return "Unknown";
    }
}

std::string Response::toString() const{
    std::ostringstream response;
    //output string stream
    response << version << " " << status << " " << reason(status) << "\r\n";
    //directly converts all types to strings
    //just like cout
    for(const auto& [key, value] : headers){
        response << key << ": " << value << "\r\n";
    }
    response << "\r\n";
    response << body;
    return response.str();
}