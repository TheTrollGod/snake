//
// Created by TheTrollGod on 10/14/2024.
//
#include <string>
#include <iostream>
#include <string>
#include <conio.h>
#include <array>
#include <vector>

#ifndef SNAKE_H
#define SNAKE_H



class snake {
public:
    // Game points
    int points = 0;



    // Constructor
    snake();

    // Game setup
    void setupBoard();


    // Game Play
    void drawBoard();
    void move();
    void collisions();
    void start();
    void die();


private:
    // 2d array of 15 x 15 for the board

    int boardCords[15][15][2];          // Game board is 15 x 15, which is 225 total slots. Need to make it a 3d array to give each spot coordinates.
                                        // boardCords[14][14][0] is the last column and last row of the grid and would give the X cord
                                        // boardCords[14][14][1] is the last column and last row of the grid and would give the y cord

    // Array to store current cords for the player
    std::vector<std::array<int, 2>> playerCords;    // Makes a vector that only accepts 1x2 arrarys
    int headCords[2] = {8,8};

    // Current direction of the player
    // Use east as 0
    enum direction {east = 0, west, north, south};
    //initalize the default game state
    direction snakeDirection = south;

    // Fruit Generation
    void getFruit();            // Calculates the coordinates for each fruit
    int fruitCord [2];          // Stores fruit coordinates

    // Loop Controls
    bool isLoop = true;
    bool extendSnake = false;
    float refreshRate = 0.4;    // Change this to adjust the refresh rate (how fast the snake moves)

};



#endif //SNAKE_H
