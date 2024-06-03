#include <conio.h> 
#include <iostream>
#include <string>
#include <windows.h> 

using namespace std; 

// Width & height
int window[2] = {100, 25};

// x, y coordinates
int coords[2];

// x, y coordinates of fruit and tail
int fruitLoc[2];
int tailLoc[2][100];

// Length of tail
int length;
// Player's score
int score;

// Determine if is over or not, true or false
bool isOver;

enum keys {
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

// Get key direction
keys kDirection;

// Initialize game variables, default settings
void Init(void) {
    isOver = false;

    // Initial state of snake = paused
    kDirection = STOP;

    // Get midpoint
    coords[0] = window[0] / 2;
    coords[1] = window[1] / 2;

    // Set random fruit location within window
    fruitLoc[0] = rand() % window[0];
    fruitLoc[1] = rand() % window[1];

    score = 0; // Default and initial score
}

// Draw and lay out boundaries
void Draw(void) {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0,0});
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

    // Top border
    for (int i = 0; i <= window[0]; i++) // Draw width of top border
        cout << "_";
    
    cout << endl;
    cout << endl;

    // Heights
    for (int i = 0; i <= window[1]; i++) {
        for (int j = 0; j <= window[0]; j++) {
            // Left and right borders
            if (j == 0 || j == window[0])
                cout << "|";

            // Snake head
            else if (i == coords[1] && j == coords[0]) // x & y coords
                cout << "O";
            
            // Food
            else if (i == fruitLoc[1] && j == fruitLoc[0])
                cout << "x";

            // Snake tail
            else {
                bool print = false;

                for (int k = 0; k < length; k++) {
                    if (i == tailLoc[1][k] && j == tailLoc[0][k]) {
                        cout << "+";
                        print = true;
                    }
                }

                if (!print)
                    cout << " ";
            }
        }

        cout << endl;
    }

    // Draw lower border
    for (int i = 0; i <= window[0]; i++)
        cout << "_";

    cout << endl;
    cout << "\nScore: " << score << endl;
}

// Get user input to determine direction of snake
void Input(void) {
    if (_kbhit()) {
        char key = _getch();

        if (key == 'w' || key == 'W' || key == 72) {
            if (kDirection != DOWN)
                kDirection = UP;
        }

        if (key == 's' || key == 'S' || key == 80) {
            if (kDirection != UP)
                kDirection = DOWN;
        }

        if (key == 'a' || key == 'A' || key == 75) {
            if (kDirection != RIGHT)
                kDirection = LEFT;
        }

        if (key == 'd' || key == 'D' || key == 77) {
            if (kDirection != LEFT)
                kDirection = RIGHT;
        }
    }
}

void Update(void) {
    // Update tail positions
    for (int i = length - 1; i > 0; --i) {
        tailLoc[0][i] = tailLoc[0][i - 1];
        tailLoc[1][i] = tailLoc[1][i - 1];
    }

    // Move the head to the new position
    tailLoc[0][0] = coords[0]; // x coordinate
    tailLoc[1][0] = coords[1]; // y coordinate

    // Move the head based on the direction
    switch (kDirection) {
        case UP:
            coords[1]--;
            break;
        case DOWN:
            coords[1]++;
            break;
        case LEFT:
            coords[0]--;
            break;
        case RIGHT:
            coords[0]++;
            break;
        default:
            break;
    }

    // Check for collisions with the borders
    if (coords[0] < 0 || coords[0] > window[0] || coords[1] < 0 || coords[1] > window[1])
        isOver = true;

    // Check for collisions with the tail
    for (int i = 0; i < length; i++) {
        if (coords[0] == tailLoc[0][i] && coords[1] == tailLoc[1][i])
            isOver = true;
    }

    // Check if eaten food and update score
    if (coords[0] == fruitLoc[0] && coords[1] == fruitLoc[1]) {
        score += 100;
        fruitLoc[0] = rand() % window[0];
        fruitLoc[1] = rand() % window[1];
        length++;
    }
}

int main() {
    Init(); // Initialize the game

    // As long as it is not game over
    while (!isOver) {
        Draw(); // Draw the boundaries
        Input(); // Get user input
        Update(); // Update game
        Sleep(10);
    }

    // Once isOver = true
    cout << "GGs!" << endl;
    return 0;
}