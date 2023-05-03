#include "StaticEntity.h"
#include "ofMain.h"

StaticEntity::StaticEntity(int x, int y, int width, int height, ofImage sprite) : Entity(x,y,width,height, sprite){
}

void StaticEntity::draw(){
    sprite.draw(x*25,y*25,width,height);
}

void StaticEntity::update(Snake* snake){
    if (snake->getHead()[0] == this->getX() && snake->getHead()[1] == this->getY()){
        snake->setCrashed(true);
    }
}