cmake_minimum_required(VERSION 3.25)
project(ModelecProject VERSION 1.1.0 LANGUAGES CXX DESCRIPTION "Modelec Lib")

# Define default install path if not provided
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "/usr/local" CACHE PATH "..." FORCE)
endif()

# Library and executable paths
include(GNUInstallDirs)

# Function to safely add a component
function(add_component component_dir)
    if(IS_DIRECTORY ${component_dir})
        if(EXISTS ${component_dir}/CMakeLists.txt)
            message(STATUS "Adding component: ${component_dir}")
            add_subdirectory(${component_dir})
        else()
            message(WARNING "Skipping component: ${component_dir} (no CMakeLists.txt found)")
        endif()
    else()
        message(WARNING "Skipping invalid directory: ${component_dir}")
    endif()
endfunction()

# Automatically add subdirectories found in the components directory
file(GLOB children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/components ${CMAKE_CURRENT_SOURCE_DIR}/components/*)
foreach(child ${children})
    add_component(${CMAKE_CURRENT_SOURCE_DIR}/components/${child})
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
