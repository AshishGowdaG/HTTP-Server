#include "MimeTypes.hpp"
#include <filesystem>
#include <unordered_map>

std::string MimeTypes::get(const std::string& path){
    static const std::unordered_map<std::string, std::string> mime_types{
        {".html", "text/html"},
        {".css",  "text/css"},
        {".js",   "application/javascript"},
        {".txt",  "text/plain"},
        {".png",  "image/png"},
        {".jpg",  "image/jpeg"},
        {".jpeg", "image/jpeg"},
        {".gif",  "image/gif"}
    };
    //static so the map is not constructed everytime the func is called
    std::filesystem::path p(path);
    auto it = mime_types.find(p.extension().string());
    if(it==mime_types.end()){
        return "application/octet-stream";
    }
    //unknown extension
    //browsers treat it as a downloadable binary file
    return it->second;
}
