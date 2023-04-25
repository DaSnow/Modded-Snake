#pragma once

#include "State.h"
#include "Snake.h"
#include "ofMain.h"
#include "PauseState.h"

class GameState : public State
{
public:
    GameState();
    ~GameState();
    void reset();
    void update();
    void draw();
    void keyPressed(int key);
    void foodSpawner();
    void drawFood();
    void drawStartScreen();
    void drawLostScreen();
    void drawBoardGrid();

    Snake *snake;

    bool foodSpawned = false;

    int xPos;
    int yPos;

    int boardSizeWidth, boardSizeHeight;
    int cellSize; // Pixels
};