//
// Created by TheTrollGod on 10/14/2024.
//

#include "snake.h"
#include <random>
#include <sstream>
#include <cstdlib>

// Initalize the clearScreen function
void clearScreen();

// Class constructor
snake::snake() {
    setupBoard();
}


void snake::setupBoard() {
    // Create a 15 x 15 array of dots for the gameboard

    // Creates the coordinates for the gameboard
    for(int i = 0; i < 15; i++) {
        for(int j =0; j < 15; j++) {
            // X cords
            boardCords[i][j][0] = {j};
            // Y cords
            boardCords[i][j][1] = {i};
        }
    }
    getFruit();
};


void snake::getFruit() {
    std::vector<std::array<int, 2>> unOccupiedCords;
    // Iterates through the game board
    for(int i = 0; i < 15; i ++) {
        for(int j = 0; j < 15; j++) {
            // Iterates through the snake body to see if it ocupies the game board
            for (int k = 0; k < playerCords.size(); k++) {
                if (boardCords[i][j][0] != playerCords[k][0] && boardCords[i][j][1] != playerCords[k][1]) {
                    //inserts the unocupied cordinate into the vector
                    unOccupiedCords.push_back({j,i});
                }
            }
        }
    }
    // Get a random location
    int randomIndex = std::rand() % unOccupiedCords.size() - 1;
    // Get random space and assign it to the fruit coordinate
    fruitCord[0] = unOccupiedCords[randomIndex][0];
    fruitCord[1] = unOccupiedCords[randomIndex][1];
}


void snake::drawBoard() {
    //Clear the screen to prepare the newboard
    clearScreen();

    // Creates a variable for the ostream to add to
    std::ostringstream out;
    // use ostream to add all the game objects and update the board once

    // Itterates through the entire board
    for(int i = 0; i < 15; i++) {
        for(int j =0; j < 15; j++) {

            // Is fruit there?
            if (fruitCord[0] == j && fruitCord[1] == i) {
                out << "<>";
                continue;
            }

            // Is the head there?
            if (headCords[0] == j && headCords[1] == i) {
                out << "}{";
                continue;
            }

            //uses this bool to make sure the body is counted correctly
            bool isSnakeBody = false;
            //Is the snake there?
            for (int k = 0; k < playerCords.size(); k++) {
                if (playerCords[k][0] == j && playerCords[k][1] == i) {
                    out << "[]";
                    isSnakeBody = true;
                    break;
                }
            }

            if (!isSnakeBody) {
                out << ". ";
            }

        }
        // New line when the end of the array is reached to display the 2d array
        out << std::endl;
    }

    // Print the entire display
    std::cout << out.str();
}

// TODO:
//  void move();
//  void collisions();
//  void start();
//  void die();

void snake::move() {
    // Add the head coordinate to the body coordinate
    playerCords.push_back({headCords[0], headCords[1]});

    // Sees if the snake needs to extend
    if (extendSnake == false) {
        // Remove the cords of the head from the coordinates if it does not extend
        playerCords.erase(playerCords.begin());
    }
    else {
        extendSnake = false;
    }

    // Add direction to the head
    if (snakeDirection == north && headCords[1] - 1 >= 0) {
        // Move north (up) by decreasing the y-coordinate
        headCords[1] -= 1;
    }
    else if (snakeDirection == east && headCords[0] + 1 <= 14) {
        // Move east (right) by increasing the x-coordinate
        headCords[0] += 1;
    }
    else if (snakeDirection == south && headCords[1] + 1 <= 14) {
        // Move south (down) by increasing the y-coordinate
        headCords[1] += 1;
    }
    else if (snakeDirection == west && headCords[0] - 1 >= 0) {
        // Move west (left) by decreasing the x-coordinate
        headCords[0] -= 1;
    }
    else {
        // If none of the directions can be moved, stop the loop
        isLoop = false;
    }
}

void snake::collisions() {
    // Checks for collision with walls and fruits
    if (headCords[0] == fruitCord[0] && headCords[1] == fruitCord[1]) {
        // Add points for fruit
        points += 1;
        getFruit();
        extendSnake = true;
        return;
    }
    // Checks the entire arrary is the head collides with the body
    for (int i =0; i < playerCords.size(); i++) {
        if (headCords[0] == playerCords[i][0] && headCords[1] == playerCords[i][1]) {
            isLoop = false;
        }
    }
}




//Googled how to do this because I know that some people use Unix :)
void clearScreen() {
    #if defined(_WIN32) || defined(_WIN64)  //Checks for windows
        system("cls");
    #else //Unix
        system("clear");
    #endif
}