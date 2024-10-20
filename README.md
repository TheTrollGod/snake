# Snake Game

A simple, console-based Snake game built in C++.

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Game Controls](#game-controls)
- [Compilation and Execution](#compilation-and-execution)
- [Known Issues](#known-issues)
- [Credits](#credits)

## Introduction

This Snake game was created by TheTrollGod. It features a 15x15 game board, and the classic Snake mechanics where the player must guide the snake to eat fruit to score points.

## Features

- **Snake Movement**: Move the snake in four directions (up, down, left, right).
- **Fruit Collection**: Collect fruits to extend the snake and earn points.
- **Game Over**: The game ends if the snake collides with itself or the game boundaries.
- **ASCII Art**: Includes a splash screen with Snake-themed ASCII art.
- **Cross-Platform Support**: Compatible with both Windows and Unix-like operating systems.

## Game Controls

- **W**: Move Up
- **A**: Move Left
- **S**: Move Down
- **D**: Move Right
- **Q**: Exit the Game

## Compilation and Execution

### Prerequisites

- C++ Compiler (such as `g++` or `clang++` for Unix/Linux systems or MSVC for Windows)
- CMake version 3.29 or later
- For Unix/Linux systems, ensure that the `unistd.h` header is correctly installed for proper usage.

### Using CMake

1. Clone the repository to your local machine:
    ```bash
    git clone https://github.com/TheTrollGod/snake
    cd snake
    ```

2. Build the game using CMake:
    ```bash
    mkdir snake/build
    cd build
    cmake ..
    make
    ```

3. Run the game:
    ```bash
   Unix:
    ./snake
   Windows:
    snake.exe
    ```

### Windows (using g++/MinGW or MSVC)

Alternatively, you can compile using `g++`:

1. Set compilation the game:
    ```bash
    cmake -G "MinGW Makefiles" .
    ```
2. Compile the game:
    ```bash
    mingw32-make
    ```
3. Run the game:
    ```bash
    snake.exe
    ```

### Unix/Linux (using g++)

1. Compile the game using `g++`:
    ```bash
    g++ -o snake_game src/main.cpp src/snake.cpp -std=c++14
    ```

2. Run the game:
    ```bash
    ./snake_game
    ```

> **Note**: Ensure your terminal is large enough to properly display the game (minimum 15x15 characters).

## Known Issues
- Screen clearing and input handling behavior may differ slightly between operating systems.
- There is no in-game difficulty adjustment yet.

## Credits

- Game Design and Programming: TheTrollGod
- Special thanks to the various online resources used to figure out platform compatibility and input handling across different systems.

---

## CMake Configuration

Here is the CMake configuration used for this project:

```cmake
cmake_minimum_required(VERSION 3.29)
project(snake)

set(CMAKE_CXX_STANDARD 14)

add_executable(snake
        src/main.cpp
        inc/snake.cpp
        inc/snake.h)
