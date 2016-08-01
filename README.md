# Introduction
This is a simple tetris clone written in C++. The project works with either SFML or SDL. It is a work in progress.

# Dependencies
This project requires either [SFML](www.sfml-dev.org) or [SDL2](www.libsdl.org) to build. The current CMake setup only works with SFML.

# Building
The project is currently being setup to use CMake to build and install. As of this writing, the following commands build the project:
```bash
mkdir -p build && cd build
cmake ..
cmake --build .
```
