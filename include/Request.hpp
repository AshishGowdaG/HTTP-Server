#pragma once

#include <string>
#include <unordered_map>

class Request{
    public:
        explicit Request(const std::string& request);
        const std::string& getMethod() const;
        const std::string& getPath() const;
        const std::string& getVersion() const;
        const std::string& getHeader(const std::string& key) const;
        //!!!!only do this when returning existing members or objects
        //reference to string(string&) is being returned to save
        //copying time since requests can get long
        //the first const ensures that the refernce cannot be modified
        //from outside only viewed
        //the last const tells the compiler the function does not
        //change any member variable or the internal state
    private:
        static void trim(std::string& s);
        //static cause doesn't really use any class members
        std::string method;
        std::string path;
        std::string version;
        std::unordered_map<std::string, std::string> headers;
};
