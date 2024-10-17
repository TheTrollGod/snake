//
// Created by TheTrollGod on 10/14/2024.
//

#include "snake.h"
#include <random>
#include <sstream>
#include <cstdlib>

//Compatability stuff that I had to look up
#ifdef _WIN32
    // Windows systems
    #include <conio.h>
    #include <windows.h>

snake::direction getDirection() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'w': return snake::north;
            case 'd': return snake::east;
            case 's': return snake::south;
            case 'a': return snake::west;  // Corrected to west
            // Exit case
            case 'q': exit(0);
            // In case things break, you go up :)
            default: return snake::north;
        }
    }
    return snake::north;  // Return a default direction if no key is pressed
}
#else
//Unix systems
#include <unistd.h>

void setNonBlocking(bool enable) {
        struct termios ttystate;
        tcgetattr(STDIN_FILENO, &ttystate);

        if (enable) {
            ttystate.c_lflag &= ~ICANON;  // Turn off canonical mode
            ttystate.c_cc[VMIN] = 1;      // Minimum of 1 character
        } else {
            ttystate.c_lflag |= ICANON;   // Restore canonical mode
        }
        tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
    }

Direction getDirection() {
        setNonBlocking(true);
        int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

        int ch = getchar();
        setNonBlocking(false);

        switch (ch) {
            case 'w': return NORTH;
            case 'd': return EAST;
            case 's': return SOUTH;
            case 'a': return WEST;
            case 'q': exit(0);
            default: ;
        }
    }

#endif





// Initalize the clearScreen function
void clearScreen();
void sleepPlease(float);


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
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            bool occupied = false;  // Track if the current coordinate is occupied
            for (const auto& coord : playerCords) {
                if (boardCords[i][j][0] == coord[0] && boardCords[i][j][1] == coord[1]) {
                    occupied = true;  // Coordinate is occupied
                    break;
                }
            }
            if (!occupied) {
                unOccupiedCords.push_back({j, i});
            }
        }
    }
    // Get a random location only if unOccupiedCords is not empty
    if (!unOccupiedCords.empty()) {
        int randomIndex = std::rand() % unOccupiedCords.size();  // Ensure random index is valid
        fruitCord[0] = unOccupiedCords[randomIndex][0];
        fruitCord[1] = unOccupiedCords[randomIndex][1];
    }
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
//  void start();
//  void die();

void snake::move() {
    //Assign direction to the snake
    snakeDirection = getDirection();

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

void snake::start() {
    // Dummy vairable
    std::string i_dont_care;

    // ASCI art for game start screen

    std::string intro[18] = {" _______  _        _______  _        _______                ",
        "(  ____ \\( (    /|(  ___  )| \\    /\\(  ____ \\               ",
        "| (    \\/|  \\  ( || (   ) ||  \\  / /| (    \\/               ",
        "| (_____ |   \\ | || (___) ||  (_/ / | (__                   ",
        "(_____  )| (\\ \\) ||  ___  ||   _ (  |  __)                  ",
        "      ) || | \\   || (   ) ||  ( \\ \\ | (                     ",
        "/\\____) || )  \\  || )   ( ||  /  \\ \\| (____/\\               ",
        "\\_______)|/    )_)|/     \\||_/    \\/(_______/               ",
        "                                                            ",
        "____  ____  ____  ____  ____  ____  ____  ____  _        _ ",
        "(  __)(__  )(  __)(__  )(  __)(__  )(  __)(__  )( \\      / )",
        "| (      ) || (      ) || (      ) || (      ) | \\ \\    / / ",
        "| |      | || |      | || |      | || |      | |  \\ \\  / /  ",
        "| |      | || |      | || |      | || |      | |   ) )( (   ",
        "| |      | || |      | || |      | || |      | |  / /  \\ \\  ",
        "| (__  __) || (__  __) || (__  __) || (__  __) | / /    \\ \\ ",
        "(____)(____)(____)(____)(____)(____)(____)(____)(_/      \\_)"};


    for (int i = 0; i < 18; i++) {
        std::cout << intro[i] << std::endl;
        sleepPlease(0.2);
    }
    std::cout << "\n \n \nControls: \nUse WSAD to control the snake. Press Q to exit the game " << std::endl;
    std::cout << "Press enter to continue" << std::endl;
    // Just waits for enter key??
    std::cin >> i_dont_care;


    // Start the game
    do {
        clearScreen();
        move();
        collisions();
        drawBoard();
        sleepPlease(refreshRate);
    }
    while (isLoop);

    // Game end
    clearScreen();
    std::cout << "\n\n\nYou got " << points << " points!\nPress 'enter' to exit" << std::endl;
    std::cin >> i_dont_care;

}
//Googled how to do this because I know that some people use Unix :)
void clearScreen() {
    #if defined(_WIN32) || defined(_WIN64)  //Checks for windows
        system("cls");
    #else //Unix
        system("clear");
    #endif
}

// Why is there different syntax for sleep between windows and Unix???
// Why the hell is it not the same????
// Why cant it have this stuff in the first place ????
void sleepPlease(float time) {
#if defined(_WIN32) || defined(_WIN64)
    Sleep(time);
#else
    sleep(time);
#endif
}

