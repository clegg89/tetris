# Script to find CppUTest and CppUTestExt libraries
# -------------------------------------------------

set(CppUTest_SEARCH_PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr/
  /sw
  /opt/local
  /opt/csw
  /opt
  ${CppUTest_PATH}
  $ENV{CppUTest_PATH}
  )

find_path(CppUTest_INCLUDE_DIR CppUTest/TestHarness.h
  PATH_SUFFIXES include
  PATHS ${CppUTest_SEARCH_PATHS}
  )

find_library(CppUTest_LIBRARY_TEMP
  NAMES CppUTest
  PATH_SUFFIXES lib64 lib
  PATHS ${CppUTest_SEARCH_PATHS}
  )

find_library(CppUTestExt_LIBRARY_TEMP
  NAMES CppUTestExt
  PATH_SUFFIXES lib64 lib
  PATHS ${CppUTest_SEARCH_PATHS}
  )

set(CppUTest_LIBRARIES_TEMP ${CppUTest_LIBRARY_TEMP} ${CppUTestExt_LIBRARY_TEMP})

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(CppUTest REQUIRED_VARS CppUTest_LIBRARIES_TEMP CppUTest_INCLUDE_DIR)

if (CppUTest_FOUND)
  message(STATUS "Setting CppUTest variables")
  set(CppUTest_LIBRARIES ${CppUTest_LIBRARIES_TEMP})
  set(CppUTest_INCLUDE_DIRS ${CppUTest_INCLUDE_DIR})
  set(CppUTest_DEFINITIONS )
endif()
