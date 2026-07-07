#include "Request.hpp"
#include <sstream>

Request::Request(const std::string& request){
    std::istringstream stream(request);
    //request put into a stream
    //can get individual lines now
    std::string line;
    std::getline(stream, line);
    //gets lines one by one(seperates the \n at the end)
    if(!line.empty() && line.back()=='\r') line.pop_back();
    //getline still includes '\r' so removing it manually
    std::istringstream line_stream(line);
    line_stream >> method >> path >> version;
    //same as reading from cin(cin and cout are streams ofc)
    //so can be used to ignore whitespaces(cin ignores them!)
    while(std::getline(stream, line)){
        if(!line.empty() && line.back()=='\r') line.pop_back();
        if(line.empty()) break;
        //if it is the last line and no more headers exist
        std::size_t col = line.find(':');
        if(col==std::string::npos) continue;
        //if find() does not find a :, means faulty header line
        std::string key = line.substr(0, col);
        std::string value = line.substr(col+1);
        trim(key);
        trim(value);
        //to remove leading or trailing spaces or tab characters
        headers[key] = value;   
    }    
}

void Request::trim(std::string& s){
    while(!s.empty() && (s.front()==' '||s.front()=='\t')) s.erase(0, 1);
    while(!s.empty() && (s.back()==' '||s.back()=='\t')) s.pop_back();
}

const std::string& Request::getMethod() const {
    return method;
}

const std::string& Request::getPath() const {
    return path;
}

const std::string& Request::getVersion() const {
    return version;
}

const std::string& Request::getHeader(const std::string& key) const {
    static const std::string empty{};
    //static cause we are returing a pointer and not by value
    //the empty gets out of scope of function and the
    //pointer points to nothing
    auto it = headers.find(key);
    if(it==headers.end()) return empty;
    return it->second;
}