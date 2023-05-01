#include "GameState.h"

//--------------------------------------------------------------
GameState::GameState()
{
    cellSize = 25;
    boardSizeWidth = 64;
    boardSizeHeight = 36;
    foodSpawned = false;
    snake = new Snake(cellSize, boardSizeWidth, boardSizeHeight);
}
//--------------------------------------------------------------
GameState::~GameState()
{
    delete snake;
}
//--------------------------------------------------------------
void GameState::reset()
{
    delete snake;
    snake = new Snake(cellSize, boardSizeWidth, boardSizeHeight);
    foodSpawned = false;
    sonicMode = false;
    storeCounter = 0;
    powerMode = 0;
    setFinished(false);
    setNextState("");
}
//--------------------------------------------------------------
void GameState::update()
{
    if (snake->isCrashed())
    {
        this->setNextState("LoseState");
        this->setFinished(true);
        return;
    }

    if (snake->getHead()[0] == xPos && snake->getHead()[1] == yPos)
    {
        foodSpawned = false;

        switch (fruitType)
        {
        case NORMAL:
            snake->grow();
            break;
        case SPEED:
            sonicMode = true;
            speedCounter = 0;
            break;
        case DOUBLE:
            snake->grow();
            snake->grow();
            break;
        case GOD:
            snake->godMode = true;
            godCounter = 0;
            break;
        }
    }

    foodSpawner();

    if (ofGetFrameNum() % 1 == 0)
    {
        rotCounter += 1;
        speedCounter += 1;
        godCounter += 1;
    }

    if (sonicMode)
    {
        if (ofGetFrameNum() % 5 == 0)
            snake->update();
    }
    else
    {
        if (ofGetFrameNum() % 10 == 0)
            snake->update();
    }

    if (speedCounter % 900 == 0)
    {
        sonicMode = false;
    }

    if (godCounter % 600 == 0)
    {
        snake->godMode = false;
    }
}
//--------------------------------------------------------------
void GameState::draw()
{
    drawBoardGrid();
    snake->draw();
    if (rotCounter % 60 == 0) // 1 second
    {
        red -= 4;
        green += 3;
    }
    drawFood();
    if (rotCounter % 1800 == 0) // 30 seconds
        foodSpawned = false;
}
//--------------------------------------------------------------
void GameState::keyPressed(int key)
{
    switch (key) // For letter keys
    {
    case 'b':
        powerUpStorage();
        break;
    case 'u':
        snake->loseFat();
        break;
    case 'p':
        this->setNextState("PauseState");
        this->setFinished(true);
        return;
        break;
    }

    switch (key) // For arrow keys
    {
    case OF_KEY_LEFT:
        snake->changeDirection(LEFT);
        break;
    case OF_KEY_RIGHT:
        snake->changeDirection(RIGHT);
        break;
    case OF_KEY_UP:
        snake->changeDirection(UP);
        break;
    case OF_KEY_DOWN:
        snake->changeDirection(DOWN);
        break;
    case NONE:
        return;
        break;
    }
}
//--------------------------------------------------------------
void GameState::foodSpawner()
{
    if (!foodSpawned)
    {
        bool isInSnakeBody;
        do
        {
            isInSnakeBody = false;
            xPos = ofRandom(1, boardSizeWidth - 1);
            yPos = ofRandom(1, boardSizeHeight - 1);
            for (unsigned int i = 0; i < snake->getBody().size(); i++)
            {
                if (xPos == snake->getBody()[i][0] and yPos == snake->getBody()[i][1])
                {
                    isInSnakeBody = true;
                }
            }
        } while (isInSnakeBody);
        foodSpawned = true;
        fruitType = ofRandom(0, 4); // To be changed to implement activation conditions
        red = 255;
        green = 0;

        rotCounter = 0;
    }
}
//--------------------------------------------------------------
void GameState::powerUpStorage()
{
    if (powerMode == SPEED)
    {
        sonicMode = true;
        speedCounter = storeCounter;
        powerMode = 0;
    }
    else if (powerMode == GOD)
    {
        snake->godMode = true;
        godCounter = storeCounter;
        powerMode = 0;
    }
    else
    {
        if (sonicMode)
        {
            powerMode = SPEED;
            storeCounter = speedCounter;
            sonicMode = false;
        }
        else if (snake->godMode)
        {
            powerMode = GOD;
            storeCounter = godCounter;
            snake->godMode = false;
        }
    }
}
//--------------------------------------------------------------
void GameState::drawFood()
{
    ofSetColor(red, green, 0);
    if (foodSpawned)
    {
        ofDrawRectangle(xPos * cellSize, yPos * cellSize, cellSize, cellSize);
    }
}
//--------------------------------------------------------------
void GameState::drawStartScreen()
{
    ofSetColor(ofColor::black);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    ofSetColor(ofColor::white);
    string text = "Press any arrow key to start.";
    ofDrawBitmapString(text, ofGetWidth() / 2 - 8 * text.length() / 2, ofGetHeight() / 2 - 11);
    return;
}
//--------------------------------------------------------------
void GameState::drawLostScreen()
{
    reset();
    this->setNextState("LoseState");
    this->setFinished(true);
    return;
}
//--------------------------------------------------------------
void GameState::drawBoardGrid()
{

    ofDrawGrid(25, 64, false, false, false, true);

    // ofSetColor(ofColor::white);
    // for(int i = 0; i <= boardSize; i++) {
    //     ofDrawLine(i*cellSize, 0, i*cellSize, ofGetHeight());
    //     ofDrawLine(0, i*cellSize, ofGetWidth(), i*cellSize);
    // }
}
//--------------------------------------------------------------
