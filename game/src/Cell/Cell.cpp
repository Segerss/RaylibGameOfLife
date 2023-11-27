#include "Cell.h"

Cell::Cell() {}

Cell::Cell(int posX, int posY) {
    this->posX = posX;
    this->posY = posY;
}

Cell::Cell(int posX, int posY, int width, int height) {
    this->posX = posX;
    this->posY = posY;
    this->width = width;
    this->height = height;
}

Cell::~Cell() {}

void Cell::setState(bool state) { this->alive = state; }
bool Cell::isAlive() { return alive; }

int Cell::getX() { return posX; }
int Cell::getY() { return posY; }

int Cell::getWidth() { return width; }

int Cell::getHeight() { return height; }
