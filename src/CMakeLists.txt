# Add includes directory
include_directories("${PROJECT_SOURCE_DIR}/includes")

set(SRCROOT ${PROJECT_SOURCE_DIR}/src)

set(SRC
  ${SRCROOT}/main.cpp
  ${SRCROOT}/Game.cpp
  ${SRCROOT}/GameIO.cpp
  ${SRCROOT}/Board.cpp
  ${SRCROOT}/IntroState.cpp
  ${SRCROOT}/PauseState.cpp
  ${SRCROOT}/PlayState.cpp
  ${SRCROOT}/Tetromino.cpp
  ${SRCROOT}/TetrominoFactory.cpp
  ${SRCROOT}/GameIO/SFML/GameIOImpl.cpp
  ${SRCROOT}/GameIO/SFML/Timer.cpp
  )
add_executable(${EXECUTABLE_NAME} ${SRC})
set_property(TARGET ${EXECUTABLE_NAME} PROPERTY CXX_STANDARD 11)
# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
# Find any version 2.X of SFML
# See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
