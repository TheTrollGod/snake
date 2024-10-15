//
// Created by TheTrollGod on 10/14/2024.
//

#include "snake.h"


// Class constructor
snake::snake() {}


void snake::setupBoard() {
    // Create a 15 x 15 array of dots for the gameboard
    for(int i = 0; i < 15; i++) {
        for(int j =0; j < 15; j++) {
            board[i][j] = ". ";
        }
    }
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

}