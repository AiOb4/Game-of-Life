/* Conway's Game of Life */

#include <iostream>
#include <ctime>
#include <algorithm>
#include <chrono>
#define delete "\x1B[2J\x1B[H"	// ASCII code to clear (visible) console
#define color "\033[107;107m" // white color and background
#define stop "\033[107;0m" // white color no background

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

void sleepcp(int milliseconds) // Cross-platform sleep function
{
    #ifdef _WIN32
        Sleep(milliseconds);
    #else
        usleep(milliseconds * 1000);
    #endif
}

using namespace std;

void draw(const bool board[][30]) {
    cout << delete << "\n\n" << color;
    for (int i = 0; i < 30; i++) {
        cout << stop << "    " << color;
        for (int j = 0; j < 30; j++) {
            if (board[i][j] == 0) {
                cout << "  ";
            }
            else {
                cout << stop << "  " << color;
            }
        }
        cout << "\n";
    }
    cout << stop << endl;
}

int check(const bool board[][30], bool newboard[][30]) {
    int count, aliveCount = 0, state = 1, sameCount = 0;
    bool same = false;
    
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            count = 0;
            if ((board[i + 1][j] == 1) && (i + 1 < 30)) {
                count++;
            }
            if ((board[i - 1][j] == 1) && (i - 1 >= 0)) {
                count++;
            }
            if ((board[i][j + 1] == 1) && (j + 1 < 30)) {
                count++;
            }
            if ((board[i][j - 1] == 1) && (j - 1 >= 0)) {
                count++;
            }
            if ((board[i + 1][j + 1] == 1) && (i + 1 < 30) && (j + 1 < 30)) {
                count++;
            }
            if ((board[i - 1][j + 1] == 1) && (i - 1 >= 0) && (j + 1 < 30)) {
                count++;
            }
            if ((board[i + 1][j - 1] == 1) && (i + 1 < 30) && (j - 1 >= 0)) {
                count++;
            }
            if ((board[i - 1][j - 1] == 1) && (i - 1 >= 0) && (j - 1 >= 0)) {
                count++;
            }
            if (board[i][j] == 1) {
                if (count < 2) {
                    newboard[i][j] = 0;
                }
                else if (count >= 4) {
                    newboard[i][j] = 0;
                }
                else {
                    newboard[i][j] = 1;
                    aliveCount++;
                }
            }
            else {
                if (count == 3) {
                    newboard[i][j] = 1;
                    aliveCount++;
                }
                else {
                    newboard[i][j] = 0;
                }
            }
        }
    }
    
    if (aliveCount == 0) {
        state = 0;
    }
    
    for (int i = 0, j = 0; (i < 30); i++) {
        for (j = 0; j < 30; j++) {
            if (board[i][j] != newboard[i][j]) {
                break;
            }
        }
        if (i == 29) {
            same = true;
        }
        if (board[i][j] != newboard[i][j]) {
            break;
        }
    }
    
    if (same) {
        state = 2;
    }
    
    return state;
}

int main()
{
    bool board1[30][30], board2[30][30];
    fill(*board1, *board1 + 30 * 30, 0);
    fill(*board2, *board2 + 30 * 30, 0);
    int seed, iteration = 0, boardState = 1;
    bool alive;
    
    cout << "Enter a Seed: ";
    cin >> seed;
    srand(seed);
    
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            alive = rand() % 4;
            board1[i][j] = !alive;
        }
    }
    
    draw(board1);
    cout << iteration << endl;
    sleepcp(600);
    
    
    while (boardState == 1) {
        if ((iteration % 2) == 0) {
            boardState = check(board1, board2);
            draw(board2);
        }
        else {
            boardState = check(board2, board1);
            draw(board1);
        }
        iteration++;
        cout << iteration << endl;
        
        sleepcp(600);
    }
    
    if (boardState == 0) {
        cout << "Your system died." << endl;
    }
    if (boardState == 2) {
        cout << "You created a completely stable system." << endl;
    }
    cout << "You had " << iteration << " iterations" << endl;
    
    return 0;
}

