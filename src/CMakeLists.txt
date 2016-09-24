set(SRCROOT ${PROJECT_SOURCE_DIR}/src)

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

# Statically link SFML
if(${WIN32})
  set(SFML_STATIC_LIBRARIES TRUE)
endif()
find_package(SFML 2 COMPONENTS audio graphics window system)

if(SFML_FOUND)

  set(SRC
    ${SRC}
    ${SRCROOT}/GameIO/SFML/GameIOImpl.cpp
    ${SRCROOT}/GameIO/SFML/Timer.cpp
    )

  include_directories(${SFML_INCLUDE_DIR})

  set(MEDIA_LIBRARIES ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

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

set(Boost_USE_STATIC_LIBS)
find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_library(${PRODUCTION_LIBRARY} ${SRC})
add_executable(${PRODUCTION_EXE} ${SRCROOT}/main.cpp)

if(WIN32 AND CMAKE_COMPILER_IS_GNUCC)
  target_link_libraries(${PRODUCTION_EXE} -static-libgcc -static-libstdc++ -static)
endif()

target_link_libraries(${PRODUCTION_EXE} ${PRODUCTION_LIBRARY} ${MEDIA_LIBRARIES} ${Boost_LIBRARIES})

set_property(TARGET ${PRODUCTION_LIBRARY} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${PRODUCTION_EXE} PROPERTY CXX_STANDARD 11)

install(TARGETS ${PRODUCTION_EXE} DESTINATION "bin")
