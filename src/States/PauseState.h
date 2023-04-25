#pragma once

#include "State.h"
#include "Snake.h"
#include "ofMain.h"
#include "GameState.h"

class PauseState : public State
{

public:
    PauseState();
    ~PauseState();
    void reset();
    void update();
    void draw();
    void keyPressed(int key);
};