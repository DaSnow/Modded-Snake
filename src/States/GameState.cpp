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
    setFinished(false);
    setNextState("");
}
//--------------------------------------------------------------
void GameState::update()
{
    if (snake->isCrashed())
    {
        this->setNextState("MenuState");
        this->setFinished(true);
        return;
    }

    if (snake->getHead()[0] == xPos && snake->getHead()[1] == yPos)
    {
        snake->grow();
        foodSpawned = false;
    }

    foodSpawner();

    if (ofGetFrameNum() % 1 == 0)
    {
        rotCounter += 1;
    }
    
    if (ofGetFrameNum() % 10 == 0)
    {
        snake->update();
    }
}
//--------------------------------------------------------------
void GameState::draw()
{
    drawBoardGrid();
    snake->draw();
    if (rotCounter % 60 == 0)
    {
        red -= 4;
        green += 3;
    }
    drawFood();
    if (rotCounter % 1800 == 0)
        foodSpawned = false;
}
//--------------------------------------------------------------
void GameState::keyPressed(int key)
{
    switch (key) // For letter keys
    {
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
        red = 255;
        green = 0;

        rotCounter = 0;
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
