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
  )

# Detect and add SDL
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2 COMPONENTS system window graphics network audio)

if(SFML_FOUND)

  set(SRC
    ${SRC}
    ${SRCROOT}/GameIO/SFML/GameIOImpl.cpp
    ${SRCROOT}/GameIO/SFML/Timer.cpp
    )

  include_directories(${SFML_INCLUDE_DIR})

  set(MEDIA_LIBRARIES ${SFML_LIBRARIES})

else()

  find_package(SDL2 REQUIRED)
  find_package(SDL2_image REQUIRED)
  find_package(SDL2_ttf REQUIRED)
  find_package(SDL2_mixer REQUIRED)

  if(SDL2_FOUND)

    set(SRC
      ${SRC}
      ${SRCROOT}/GameIO/SDL/GameIOImpl.cpp
      ${SRCROOT}/GameIO/SDL/Timer.cpp
      )

    include_directories(
      ${SDL2_INCLUDE_DIR}
      ${SDL2_IMAGE_INCLUDE_DIR}
      ${SDL2_TTF_INCLUDE_DIR}
      ${SDL2_MIXER_INCLUDE_DIR}
      )

    set(MEDIA_LIBRARIES
      ${SDL2_LIBRARY}
      ${SDL2_IMAGE_LIBRARY}
      ${SDL2_TTF_LIBRARY}
      ${SDL2_MIXER_LIBRARY}
      )

  endif()
endif()

add_executable(${EXECUTABLE_NAME} ${SRC})
target_link_libraries(${EXECUTABLE_NAME} ${MEDIA_LIBRARIES})
set_property(TARGET ${EXECUTABLE_NAME} PROPERTY CXX_STANDARD 11)

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION ${PROJECT_BINARY_DIR}/bin)