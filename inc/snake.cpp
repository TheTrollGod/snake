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
    std::vector<int[2]> unOccupiedCords;
    // Iterates through the game board
    for(int i = 0; i < 15; i ++) {
        for(int j = 0; j < 15; j++) {
            // Iterates through the snake body to see if it ocupies the game board
            for (int k = 0; k < playerCords.size(); k++) {
                if (boardCords[i][j] != playerCords[k]) {
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

    // Itterates through
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

    //Print the entire display
    std::cout << out.str();
}

// TODO:
//  void move();
//  void collisions();
//  void start();
//  void die();







//Googled how to do this because I know that some people use Unix :)
void clearScreen() {
#if defined(_WIN32) || defined(_WIN64)  //Checks for windows
    system("cls");
#else //Unix
    system("clear");
#endif
}