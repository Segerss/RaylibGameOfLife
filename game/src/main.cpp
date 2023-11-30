#include <iostream>

#include "Cell.h"
#include "raylib.h"

const int screenWidth = 1200;
const int screenHeight = 800;

const int cellWidth = 40;
const int cellHeight = 40;

const int rows = screenHeight / cellHeight;
const int cols = screenWidth / cellWidth;

const int amountOfCells = rows * cols;

Cell grid[rows][cols];

void CellDraw(Cell cell) {
    // std::cout << "Draw " << cell.getX() << ", " << cell.getY() << std::endl;

    Color cellColor;

    Color deadBlockColor = {.r = 46, .g = 46, .b = 46, .a = 0xFF};

    if (cell.isAlive()) {
        cellColor = RED;
    } else {
        cellColor = deadBlockColor;
    }

    struct Rectangle rec = {.x = (float)(cell.getX() * cell.getWidth()),
                            .y = (float)(cell.getY() * cell.getHeight()),
                            .width = (float)(cell.getWidth() - 1),
                            .height = (float)(cell.getHeight() - 1)};

    DrawRectangleRounded(rec, 0.4, 10, cellColor);

    // DrawRectangle(cell.getX() * cell.getWidth(), cell.getY() * cell.getHeight(), cell.getWidth() - 1,
    // cell.getHeight() - 1, cellColor);
}

bool coordinatesInCell(Cell cell, Vector2 pos) {
    if (pos.x > (cell.getX() * cellWidth) && pos.x < ((cell.getX() * cellWidth) + cell.getWidth())) {
        if (pos.y > (cell.getY() * cellHeight) && pos.y < ((cell.getY() * cellHeight) + cell.getWidth())) {
            return true;
        }
    }
    return false;
}
void GridDraw() {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            CellDraw(grid[r][c]);
        }
    }
}

bool validGridPosition(int posX, int posY) {
    // if (posX < 0 || posX >= rows) {
    // return false;
    //}
    // if (posY < 0 || posY >= cols) {
    // return false;
    //}
    if (posX < 0 || posX >= cols) {
        return false;
    }

    if (posY < 0 || posY >= rows) {
        return false;
    }
    return true;
}

int numberAliveSurroundingCells(Cell gridToCheck[rows][cols], Cell cellToCheck) {
    int totalAlive = 0;

    for (int r = -1; r <= 1; r++) {
        for (int c = -1; c <= 1; c++) {
            if (r == 0 && c == 0) {
                continue;
            }
            if (validGridPosition(cellToCheck.getX() + c, cellToCheck.getY() + r)) {
                if (grid[cellToCheck.getY() + r][cellToCheck.getX() + c].isAlive()) {
                    totalAlive++;
                }
            }
            // if (checkX + c < 0 || checkX + c >= cols) {
            // continue;
            //}

            // if (checkY + r < 0 || checkY + r >= rows) {
            // continue;
            //}

            //            if (grid[cellToCheck.getY() + r][cellToCheck.getX() + c].isAlive()) {
            //              totalAlive++;
            //         }
        }
    }
    return totalAlive;
}

void runGame() {
    Cell curGrid[rows][cols];

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            curGrid[r][c] = grid[r][c];
        }
    }

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            Cell* currentCell = &grid[r][c];
            int amountAlive = numberAliveSurroundingCells(curGrid, *currentCell);

            if (amountAlive > 0) {
                std::cout << "Amount Alive " << r << ", " << c << ": " << amountAlive << std::endl;
                std::cout << "cell data " << currentCell->getY() << ", " << currentCell->getX() << ": " << amountAlive
                          << std::endl;
            }

            if (currentCell->isAlive()) {
                if (amountAlive < 2) {
                    curGrid[r][c].setState(false);
                } else if (amountAlive == 2 || amountAlive == 3) {
                    curGrid[r][c].setState(true);
                } else if (amountAlive > 3) {
                    curGrid[r][c].setState(false);
                }
            } else {
                if (amountAlive == 3) {
                    curGrid[r][c].setState(true);
                }
            }

            // if(amountAlive < 2){
            // curGrid[r][c].setState(false);
            //}else if (currentCell->isAlive() &&

            // if (amountAlive > 3) {
            // currentCell->setState(true);
            //}
        }
    }

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            grid[r][c].setState(curGrid[r][c].isAlive());
        }
    }

    std::cout << "end of game" << std::endl;
}
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {

    InitWindow(screenWidth, screenHeight, "Conway's game of life in raylib");

    SetTargetFPS(60);

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            grid[r][c] = Cell(c, r, cellWidth, cellHeight);
        }
    }

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            std::cout << "Cell " << grid[r][c].getX() << ", " << grid[r][c].getY() << std::endl;
        }
    }

    bool paused = true;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_SPACE)) {
            paused = !paused;
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mPos = GetMousePosition();

            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < cols; c++) {
                    if (coordinatesInCell(grid[r][c], mPos)) {
                        Cell* cell = &grid[r][c];
                        cell->setState(!cell->isAlive());
                    }
                }
            }
        }

        if (!paused) {
            static int counter = 0;
            counter++;
            // if (counter % 30 == 0)
            runGame();
        }

        BeginDrawing();

        ClearBackground(BLACK);

        // DrawText("PAUSED", 350, 200, 30, GRAY);

        GridDraw();

        if (paused) {
            DrawText("PAUSED", 350, 200, 30, GRAY);
        }

        // for (int y = 0; y < rows; y++) {
        // for (int x = 0; x < cols; x++) {
        // DrawRectangleLines(x * cellHeight, y * cellWidth, cellWidth,
        // cellHeight, BLACK);
        //}
        //}

        DrawFPS(10, 10);

        EndDrawing();
        //-----------------------------------------------------
    }

    // De-Initialization
    //---------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //----------------------------------------------------------

    return 0;
}
