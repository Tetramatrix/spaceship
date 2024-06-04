#include "allincludes.h"

Sprite::Sprite(Engine * engine, int x, int y, int speed, int spriteNr)
{
    this->engine = engine;
    
    this->x = x;
    this->y = y;
    this->speed = speed;
    
    this->radius = 10;    
    this->score = 50;
    
    switch (spriteNr) {
        case 0:
            this->spriteNr = 0;
            this->energy = 100;
            break;
        case 1:
            this->spriteNr = 2;
            this->energy = 800;
            break;
    }  
    
    this->shotTime = 2;
    this->shotMaxRange = 500;
    this->shotLength = 15;
    this->shotRadius = 1;
    this->shotSpeed = 2;    
    this->last_measure = 0;
    
    this->listenerPos[0]=0.0;
    this->listenerPos[1]=0.0;
    this->listenerPos[2]=0.0;    
    
    engine->registerTarget(this);
}
bool Sprite::hit()
{
    return true;
}
bool Sprite::collisionWith()
{    
    if (this->spriteNr == 2) {
        energy = 0;
    }
    
    energy -= 100;        
       
    if (energy <= 0)
    {
      engine->frag(this);
      engine->snd->stopPlay(3);
      engine->snd->play(3, this->listenerPos, 0.002);  
      return true;
    }
    
    return false;
}


bool Sprite::hitBy(Shot * s)
{
    if (s->shotNr == 1 && this->spriteNr == 0) {
        return false;
    }
    engine->snd->stopPlay(2);
    engine->snd->play(2, s->listenerPos, 0.002);
    energy -= 20;
    
    if (energy <= 0)
    {
      engine->frag(this);
      engine->snd->stopPlay(3);
      engine->snd->play(3, s->listenerPos, 0.002);  
      return true;
    }
    
    return false;
}

void Sprite::getCoords(int * x, int * y)
{
  *x = this->x;
  *y = this->y;
}

int Sprite::getRadius()
{
  return this->radius;
}

int Sprite::getScore()
{
  return this->score;
}


void Sprite::update(Engine * engine, int player_rad, int player_x, int player_y) {
    
    float dx = player_x - this->x-this->speed;            
    float dy = player_y - this->y;
    float dr = (dx*dx + dy*dy);
    float ur = player_rad + this->shotMaxRange/2;
    
    if (dr < ur*ur) {
    
        dx = player_x - this->x-this->speed;            
        dy = player_y - this->y;
        if (dx == 0) {
            dx = 1.0;
        }
        if (dy == 0) {
            dy = 1.0;
        }        
        dr = roundf(sqrt(dx*dx + dy*dy));
               
        dx /= dr;
        dy /= dr;
        
        int xv = player_x + (int)roundf(dx * this->shotMaxRange);
        int yv = player_y + (int)roundf(dy * this->shotMaxRange);
            
        int time = time_millis();    
        if (time - this->last_measure > 1000*this->shotTime)
        {
            this->last_measure = time;
            Shot * s = new Shot(engine, this->x-this->speed-32,this->y+10, xv, yv, 1, this->shotMaxRange, this->shotSpeed+this->speed);
            engine->snd->stopPlay(5);
            engine->snd->play(5, s->listenerPos, 0.01);
        }
               
    }
}
