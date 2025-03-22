#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define WIDTH 10
#define HEIGHT 20

void gameLoop();
void initializeBoard();
void drawBoard();
void showTetromino();
void clearTetromino();
int checkCollision(int newX, int newY);
void lockTetromino();
void moveTetromino(int dx, int dy);
void loseMessage();
void restartGame();
void spawnTetromino(int *tetrominoX, int *tetrominoY, int *type);
void turnTetrominoRight(int *pos, int *type);
void turnTetrominoLeft(int *pos, int *type);

char board[HEIGHT][WIDTH];
int currentTetromino[4][4];
int tetrominoX = 0, tetrominoY = 0;
int tetrominos[7][4][4][4] = {
    /* tetromino I */
    {
        {{0, 0, 0, 1}, {0, 0, 0, 1}, {0, 0, 0, 1}, {0, 0, 0, 1}},  // right
        {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},  // normal
        {{1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}},  // left
        {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}}   // reverse
    },
    /* tetromino T */
    {
        {{0, 0, 0, 0}, {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}},  // right
        {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},  // normal
        {{1, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},  // left
        {{0, 0, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}   // reverse
    },
    /* tetromino O */
    {
        {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},  // right
        {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},  // normal
        {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},  // left
        {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}   // reverse
    },
    /* tetromino Z */
    {
        {{0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},  // right
        {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},  // normal
        {{0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},  // left
        {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}   // reverse
    },
    /* tetromino S */
    {
        {{0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}},  // right
        {{0, 0, 1, 1}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},  // normal
        {{0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}},  // left
        {{0, 0, 1, 1}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}   // reverse
    },
    /* tetromino J */
    {
        {{1, 1, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}},  // right
        {{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},  // normal
        {{0, 0, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}},  // left
        {{0, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}}   // reverse
    },
    /* tetromino L */
    {
        {{1, 0, 0, 0}, {1, 0, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}},  // right
        {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},  // normal
        {{1, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},  // left
        {{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}   // reverse
    }
};

void initializeBoard() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            board[i][j] = 0;
        }
    }
}

void drawBoard() {
    system("cls");
    for (int i = 0; i < WIDTH; i++) {
        printf("##");
    }
    for (int i = 0; i < HEIGHT; i++) {
        printf("#");
        for (int j = 0; j < WIDTH; j++) {
            if (board[i][j] == 1) {
                printf("[]");
            } else {
                printf(". ");
            }
        }
        printf("#");
        printf("\n");
    }
    for (int i = 0; i < WIDTH; i++) {
        printf("##");
    }
}

void spawnTetromino(int *tetrominoX, int *tetrominoY, int *type) {
    *type = rand() % 7;
    *tetrominoX = WIDTH / 2 - 2;
    *tetrominoY = 0;

    for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
            currentTetromino[i][j] = tetrominos[*type][i][j];
        }
    }
}

void showTetromino() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (currentTetromino[i][j]) {
                int x = tetrominoX + j;
                int y = tetrominoY + i;
                if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH) {
                    board[y][x] = 1; // Set the board to show the tetromino
                }
            }
        }
    }
}

void clearTetromino() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (currentTetromino[i][j]) {
                int x = tetrominoX + j;
                int y = tetrominoY + i;
                if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH) {
                    board[y][x] = 0; // Clear the board where the tetromino is
                }
            }
        }
    }
}

int checkCollision(int newX, int newY) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (currentTetromino[i][j]) {
                int x = newX + j;
                int y = newY + i;
                if (x < 0 || x >= WIDTH || y >= HEIGHT || board[y][x] != 0) {
                    return 1; // Collision detected
                }
            }
        }
    }
    return 0; // No collision
}
 
void lockTetromino() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (currentTetromino[i][j]) {
                int x = tetrominoX + j;
                int y = tetrominoY + i;
                if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH) {
                    board[y][x] = 1; // Lock the tetromino onto the board
                }
            }
        }
    }
}

void moveTetromino(int dx, int dy) {
    clearTetromino();
    if (checkCollision(tetrominoX + dx, tetrominoY + dy)) {
        if (dy != 0) {
            lockTetromino();
            spawnTetromino(&tetrominoX, &tetrominoY, NULL); // Generate a new tetromino
        }
    } else {
        tetrominoX += dx;
        tetrominoY += dy;
    }
    showTetromino();
}

void turnTetrominoRight(int *type) {
    int temp[4][4];
    // Rotate current tetromino to the right
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp[i][j] = currentTetromino[3-j][i];
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            currentTetromino[i][j] = temp[i][j];
        }
    }
    // Check if the new rotation collides
    if (checkCollision(tetrominoX, tetrominoY)) {
        // If so, revert rotation
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                currentTetromino[i][j] = tetrominos[*type][i][j];
            }
        }
    }
}

void turnTetrominoLeft(int *type) {
    int temp[4][4];
    // Rotate current tetromino to the left
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp[i][j] = currentTetromino[j][3-i];
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            currentTetromino[i][j] = temp[i][j];
        }
    }
    // Check if the new rotation collides
    if (checkCollision(tetrominoX, tetrominoY)) {
        // If so, revert rotation
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                currentTetromino[i][j] = tetrominos[*type][i][j];
            }
        }
    }
}

void loseMessage() {
    printf("Game Over!\n");
    printf("Press any key to restart.\n");
    getch();
    restartGame();
}

void restartGame() {
    initializeBoard();
    tetrominoX = WIDTH / 2 - 2;
    tetrominoY = 0;
    spawnTetromino(&tetrominoX, &tetrominoY, NULL);
    gameLoop();
}

void gameLoop() {
    int gameOver = 0;
    int currentTetrominoType;
    spawnTetromino(&tetrominoX, &tetrominoY, &currentTetrominoType);
    
    while (!gameOver) {
        drawBoard();
        if (_kbhit()) {
            char key = _getch();
            if (key == 'q') {
                break; // Quit game
            } else if (key == 'a') {
                moveTetromino(-1, 0); // Move left
            } else if (key == 'd') {
                moveTetromino(1, 0);  // Move right
            } else if (key == 's') {
                moveTetromino(0, 1);  // Move down
            } else if (key == 'w') {
                turnTetrominoRight(&currentTetrominoType);  // Rotate right
            } else if (key == 'e') {
                turnTetrominoLeft(&currentTetrominoType);  // Rotate left
            }
        }

        moveTetromino(0, 1); // Automatically move the tetromino down every loop

        if (tetrominoY >= HEIGHT - 1) {
            lockTetromino();
            spawnTetromino(&tetrominoX, &tetrominoY, &currentTetrominoType);
        }
    }
}

int main() {
    srand(time(NULL));  // Initialize random seed
    initializeBoard();
    gameLoop();
    return 0;
}

