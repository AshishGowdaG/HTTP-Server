#pragma once

#include <string>
#include <unordered_map>

class Response{
    public:
        Response();
        void setStatus(int code);
        void setHeader(const std::string& key, const std::string& value);
        void setBody(const std::string& body);
        std::string toString() const;
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
        static std::string reason(int code);

};