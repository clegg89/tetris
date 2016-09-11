# Minimum required CMake version
cmake_minimum_required(VERSION 2.8)

# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

project(tetris)

enable_testing()

set(tetris_VERSION_MAJOR 1)
set(tetris_VERSION_MINOR 0)
set(tetris_VERSION_PATH 0)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

set(PRODUCTION_LIBRARY ${CMAKE_PROJECT_NAME}Library)
set(PRODUCTION_EXE ${CMAKE_PROJECT_NAME})
set(TEST_EXE ${CMAKE_PROJECT_NAME}Test)

add_subdirectory(src)
add_subdirectory(tests)

add_test(${TEST_EXE} tests/${TEST_EXE})

install(DIRECTORY media DESTINATION etc/${CMAKE_PROJECT_NAME})

include(InstallRequiredSystemLibraries)

# CPack setup
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A simple Tetris clone")
set(CPACK_PACKAGE_VENDOR "Clegg")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/ReadMe.md")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_EXECUTABLES "Tetris" "Tetris")

#Enable CPack
include(CPack)
