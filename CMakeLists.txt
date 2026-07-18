cmake_minimum_required(VERSION 3.16)

project(HTTPServer
    VERSION 1.0
    DESCRIPTION "God's own Server"
    LANGUAGES CXX
)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_executable(http_server
    src/main.cpp
    src/Socket.cpp
    src/Server.cpp
    src/Request.cpp
    src/Response.cpp
    src/MimeTypes.cpp
)


target_include_directories(http_server PRIVATE include)

#thread library include(linux specific; macos doesn't need it)
find_package(Threads REQUIRED)
target_link_libraries(http_server PRIVATE Threads::Threads)