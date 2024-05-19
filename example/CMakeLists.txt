cmake_minimum_required(VERSION 3.10)

project(MySecondProject)

# Find the shared library package
find_package(Modelec COMPONENTS
        CLParser
    REQUIRED)

# Define the executable
add_executable(MyExecutable main.cpp)

# Link the shared library to the executable
target_link_libraries(MyExecutable
        Modelec::CLParser
)