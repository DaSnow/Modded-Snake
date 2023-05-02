#pragma once

#include "State.h"
#include "Snake.h"
#include "ofMain.h"
#include "PauseState.h"
#include "ofSoundPlayer.h"

enum FruitType
{
    NORMAL,
    SPEED,
    DOUBLE,
    GOD
};

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
    void powerUpStorage();
    void drawFood();
    void drawStartScreen();
    void drawLostScreen();
    void drawBoardGrid();

    Snake *snake;

    bool foodSpawned = false;
    int fruitType;

    int rotCounter = 0;
    bool sonicMode = false;
    int speedCounter = 0;
    int godCounter = 0;

    int storeCounter;
    int powerMode;

    int red = 255;
    int green = 0;

    int xPos;
    int yPos;

    int boardSizeWidth, boardSizeHeight;
    int cellSize; // Pixels
    static int score;

    ofSoundPlayer sound;
};