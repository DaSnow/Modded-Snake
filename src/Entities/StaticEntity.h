#pragma once

#include "Entity.h"
#include "Snake.h"

class StaticEntity : public Entity {

    public:
        StaticEntity(int x, int y, int width, int height, ofImage sprite); //Constructor
        void draw();
        void update(Snake* snake);
};