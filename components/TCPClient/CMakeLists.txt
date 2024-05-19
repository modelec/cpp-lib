cmake_minimum_required(VERSION 3.25)
project(TCPClient)

# Define the library
add_library(TCPClient SHARED
        src/TCPClient.cpp
)

# Specify include directories
target_include_directories(TCPClient PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Link against Utils
target_link_libraries(TCPClient PUBLIC Utils)

# Export target
install(TARGETS TCPClient
        EXPORT ModelecTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})