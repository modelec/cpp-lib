cmake_minimum_required(VERSION 3.25)
project(ModelecProject VERSION 1.0.0 LANGUAGES CXX DESCRIPTION "Modelec Lib")

# Define default install path if not provided
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "/usr/local" CACHE PATH "..." FORCE)
endif()

# Library and executable paths
include(GNUInstallDirs)

# Automatically add subdirectories found in the components directory
file(GLOB children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/components ${CMAKE_CURRENT_SOURCE_DIR}/components/*)
foreach(child ${children})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/components/${child})
        message(STATUS "Adding component: ${child}")
        add_subdirectory(components/${child})
    endif()
endforeach()

# Configuration for installation and find_package()
include(CMakePackageConfigHelpers)
configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/ModelecConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/ModelecConfig.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Modelec
)

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/ModelecConfig.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Modelec
)

# Install the export set for later use by find_package()
install(EXPORT ModelecTargets
        FILE ModelecTargets.cmake
        NAMESPACE Modelec::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Modelec
)
