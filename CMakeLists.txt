# Minimum required CMake version
cmake_minimum_required(VERSION 2.8)

# Allow VERSION argument for project
if(POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif()

# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/third-party")

include(GetGitRevisionDescription)
git_describe(GIT_VERSION --tags --abbrev=0)

project(tetris VERSION ${GIT_VERSION})

enable_testing()

set(PRODUCTION_LIBRARY "${CMAKE_PROJECT_NAME}Code")
set(PRODUCTION_EXE ${CMAKE_PROJECT_NAME})
set(TEST_EXE "${CMAKE_PROJECT_NAME}Test")

set(RESOURCE_PREFIX "etc/${CMAKE_PROJECT_NAME}")
configure_file(${CMAKE_SOURCE_DIR}/includes/Config.hpp.in ${CMAKE_BINARY_DIR}/includes/Config.hpp)

include_directories("${CMAKE_BINARY_DIR}/includes")
include_directories("${PROJECT_SOURCE_DIR}/includes")

add_subdirectory(src)
add_subdirectory(tests)

# Install
install(DIRECTORY media DESTINATION ${RESOURCE_PREFIX})

add_test(${TEST_EXE} tests/${TEST_EXE})

include(InstallRequiredSystemLibraries)

# CPack setup
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A simple Tetris clone")
set(CPACK_PACKAGE_VENDOR "Clegg")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_EXECUTABLES "Tetris" "Tetris")

#Enable CPack
include(CPack)
