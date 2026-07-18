#pragma once

#include <string>
#include <unordered_map>

class Response{
    public:
        Response();
        void setStatus(int code);
        void setHeader(const std::string& key, const std::string& value);
        void setBody(const std::string& body);
        int getStatus() const;
        std::string toString() const;
        static std::string reason(int code);
        //cannot return a refernce because it is making a new string
        //will have to make static but then static is shared across
        //all objects. so calling the method in two different places
        //will change strings stored. it worked with empty string 
        //in request ofc.
    private:
        std::string version;
        int status;
        std::unordered_map<std::string, std::string> headers;
        std::string body;

};