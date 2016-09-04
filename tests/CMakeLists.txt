# Add includes directory
include_directories("${PROJECT_SOURCE_DIR}/includes")

set(TESTROOT ${PROJECT_SOURCE_DIR}/tests)

set(TESTS
  ${TESTROOT}/Starter_test.cpp
  )

set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads)
if(Threads_FOUND)
    message(STATUS "Found ${CMAKE_THREAD_LIBS_INIT}")
endif()

find_package(CppUTest REQUIRED)
if(CppUTest_FOUND)
    message(STATUS "Found ${CppUTest_LIBRARIES} ${CppUTest_VERSION_MAJOR}.${CppUTest_VERSION_MINOR}.${CppUTest_VERSION_PATCH}")
endif()

include_directories(${CppUTest_INCLUDE_DIR})

add_executable(${TEST_EXE} ${TESTROOT}/AllTests.cpp ${TESTS})
target_link_libraries(${TEST_EXE} ${PRODUCTION_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} ${CppUTest_LIBRARIES})

set_property(TARGET ${TEST_EXECUTABLE_NAME} PROPERTY CXX_STANDARD 11)
