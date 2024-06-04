#include "allincludes.h"

Shot::Shot(Engine * engine, int x, int y, int target_x, int target_y, int shotNr, int maxRange, int speed)
{        
    this->shotNr = shotNr;
    
    this->x = x;
    this->y = y;

    this->target_x = target_x;
    this->target_y = target_y;
    
    this->radius = 22;
    
    this->shotLength = 15;    
    this->maxRange = maxRange;  
    
    this->range = 0;    
    
    this->sV[0] = 0;
    this->sV[1] = 0;
    this->sV[2] = 0;
    this->sV[3] = 0;
    this->sV[4] = 0;
    this->sV[5] = 0;
    this->sV[6] = 0;
    this->sV[7] = 0;
    
    this->sC[0] = 0.0;
    this->sC[1] = 1.0;
    this->sC[2] = 0.0;
    this->sC[3] = 1.0;
    
    this->sC[4] = 0.0;    
    this->sC[5] = 1.0;
    this->sC[6] = 0.0;
    this->sC[7] = 1.0;
    
    this->sC[8] = 0.0;    
    this->sC[9] = 1.0;
    this->sC[10] = 0.0;
    this->sC[11] = 1.0;
    
    this->sC[12] = 0.0;    
    this->sC[13] = 1.0;
    this->sC[14] = 0.0;
    this->sC[15] = 1.0;
    
    this->listenerPos[0]=0.0;
    this->listenerPos[1]=0.0;
    this->listenerPos[2]=0.0;
    
    this->speed = speed;
    
    switch (shotNr) {
        case 1:
            this->sC[0] = 1.0;
            this->sC[1] = 0.0;
            this->sC[2] = 0.0;
            this->sC[3] = 1.0;
            
            this->sC[4] = 1.0;    
            this->sC[5] = 0.0;
            this->sC[6] = 0.0;
            this->sC[7] = 1.0;
            
            this->sC[8] = 1.0;    
            this->sC[9] = 0.0;
            this->sC[10] = 0.0;
            this->sC[11] = 1.0;
            
            this->sC[12] = 1.0;    
            this->sC[13] = 0.0;
            this->sC[14] = 0.0;
            this->sC[15] = 1.0;
            break;
    }
    
    this->engine = engine;    
    engine->registerMissile(this);
}

bool Shot::hit(Sprite * t)
{
    if (t->spriteNr == 0 && this->shotNr == 1) {
        return false;
    }
    return true;
}

void Shot::getCoords(int * x, int * y)
{
  *x = this->x;
  *y = this->y;
}

int Shot::getRadius()
{
  return this->radius;
}
