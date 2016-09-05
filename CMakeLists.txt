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

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

set(PRODUCTION_LIBRARY ${CMAKE_PROJECT_NAME}Library)
set(PRODUCTION_EXE ${CMAKE_PROJECT_NAME})
set(TEST_EXE ${CMAKE_PROJECT_NAME}Test)

add_subdirectory(src)
add_subdirectory(tests)

install(DIRECTORY media DESTINATION ${PROJECT_BINARY_DIR}/bin)
