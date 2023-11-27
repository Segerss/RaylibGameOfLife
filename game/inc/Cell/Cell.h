#pragma once

class Cell {
private:
    bool alive = false;

    int posX = 0;
    int posY = 0;

    int width = 0;
    int height = 0;

public:
    Cell();
    Cell(int posX, int posY);
    Cell(int posX, int posY, int width, int height);

    ~Cell();

    void setState(bool state);
    bool isAlive();

    int getX();
    int getY();

    int getWidth();
    int getHeight();
};
