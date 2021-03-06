# Tetris Clone
[![Build Status](https://travis-ci.org/clegg89/tetris.svg?branch=master)](https://travis-ci.org/clegg89/tetris)
[![Build status](https://ci.appveyor.com/api/projects/status/r72c16219uxpmda3?svg=true)](https://ci.appveyor.com/project/clegg89/tetris)
[![build status](https://git.corporal-clegg.com/games/tetris/badges/master/build.svg)](https://git.corporal-clegg.com/games/tetris/commits/master)

# Introduction
This is a simple tetris clone written in C++. The project works with either SFML or SDL. It is a work in progress.

# Dependencies
This project requires either [SFML](www.sfml-dev.org) or [SDL2](www.libsdl.org) to build. CMake will preferentially select SFML. If it cannot locate SFML, it will use SDL2.

The project also uses the boost-filesystem library, which in turn uses boost-system. On linux, simply install libboost-filesystem-dev, which will pickup boost-system as a dependency. Windows requires building and installing Boost manually.

## Additional SDL2 Libraries

In addition to the main SDL2 development library, the following libraries are also required: [SDL2_image](https://www.libsdl.org/projects/SDL_image), [SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer), [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf).

# Building
The project uses CMake to build and install. As of this writing, the following commands build the project:
```bash
mkdir -p build && cd build
cmake ..
cmake --build .
cmake --build . --target install
```
The resulting binary will be located in build/bin.

# TODO
The following is a list of action items
* Refactor TetrominoFactory
* Refactor rest of code that uses C so that it is more C++
* Unit tests with [CppUTest](cpputest.github.io)
