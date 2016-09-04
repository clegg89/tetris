# Add includes directory
include_directories("${PROJECT_SOURCE_DIR}/includes")

set(SRCROOT ${PROJECT_SOURCE_DIR}/src)
set(TESTROOT ${PROJECT_SOURCE_DIR}/tests)

set(SRC
  ${SRCROOT}/Game.cpp
  ${SRCROOT}/GameIO.cpp
  ${SRCROOT}/Board.cpp
  ${SRCROOT}/IntroState.cpp
  ${SRCROOT}/PauseState.cpp
  ${SRCROOT}/PlayState.cpp
  ${SRCROOT}/Tetromino.cpp
  ${SRCROOT}/TetrominoFactory.cpp
  )

set(TESTS
  ${TESTROOT}/Starter_test.cpp
  )

set(TEST_EXECUTABLE_NAME "${EXECUTABLE_NAME}Tests")
set(PROD_LIB_NAME "${EXECUTABLE_NAME}Prod")

set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads)
if(Threads_FOUND)
    message(STATUS "Found ${CMAKE_THREAD_LIBS_INIT}")
endif()

find_package(CppUTest REQUIRED)
if(CppUTest_FOUND)
    message(STATUS "Found ${CppUTest_LIBRARIES} ${CppUTest_VERSION_MAJOR}.${CppUTest_VERSION_MINOR}.${CppUTest_VERSION_PATCH}")
endif()

add_library(${PROD_LIB_NAME} ${SRC})
include_directories(${CppUTest_INCLUDE_DIR})
add_executable(${TEST_EXECUTABLE_NAME} AllTests.cpp ${TESTS})
target_link_libraries(${TEST_EXECUTABLE_NAME} ${PROD_LIB_NAME} ${CMAKE_THREAD_LIBS_INIT} ${CppUTest_LIBRARIES})

set_property(TARGET ${PROD_LIB_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${TEST_EXECUTABLE_NAME} PROPERTY CXX_STANDARD 11)
