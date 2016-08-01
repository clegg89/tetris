# Minimum required CMake version
cmake_minimum_required(VERSION 2.8)

# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

project(tetris)

# Set version information in a config.h file
# No...
set(tetris_VERSION_MAJOR 1)
set(tetris_VERSION_MINOR 0)

# Define sources and executable
set(EXECUTABLE_NAME "tetris")
add_subdirectory(src)
