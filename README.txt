# Attached README.md with a link to the project, as I couldn't attach an compressed archive.

# TL;DR

This is an 2D game engine written in C++ and OpenGL, making use of Allegro 5 as the render API an box2d for physics. It is a work in progress and is not yet ready for use.

It aims to be a 2D spacesim, where you are a commander of spaceship squads in an interlinked galaxy map, with a focus on resource management, some combat, and faction relations.

*At this point, only basic rendering is implemented, and the game is long way to be done.*

## Requirements

* CMake 3
* C++17
* Allegro 5
* GTest (for tests)
* spdlog (for logging)
* box2d (for physics)


## Taget Platforms
* Linux (Ubuntu 20/22)
* Windows

## Building

```bash
mkdir build
cd build
cmake ..
make
```

## Log location

The log file is located at `<BIN_LOCATION>/logs/core.log`


## GitHub link

https://github.com/Akryllax/Small-project