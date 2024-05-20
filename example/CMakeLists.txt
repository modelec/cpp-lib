cmake_minimum_required(VERSION 3.10)

project(clientExample)

# Find the shared library package
find_package(Modelec COMPONENTS
        CLParser
        TCPClient
        Utils
    REQUIRED)

# Define the executable
add_executable(client main.cpp)

# Link the shared library to the executable
target_link_libraries(client
        Modelec::CLParser
        Modelec::TCPClient
        Modelec::Utils
)