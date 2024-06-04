#include "allincludes.h"

Spaceship::Spaceship(Engine * engine)

{
    // init raumschiff
    
    this->engine = engine;
    
    this->image[0] = new TargaFile("data/raumschiff.tga");
    this->image[1] = new TargaFile("data/raumschiff1.tga");
    this->image[2] = new TargaFile("data/raumschiff2.tga");
    this->image[3] = new TargaFile("data/raumschiff3.tga");
    
    this->listenerPos[0]=0.0;
    this->listenerPos[1]=0.0;
    this->listenerPos[2]=0.0;
    
    this->fireCooldown = 0;
    this->speed = 0; this->maxSpeed = 3; this->minSpeed = -3;    
    this->steer = 0; this->minSteer = 2; this->maxSteer = 3;
        
    this->x = 10;
    this->y = 284;
    
    this->ani[0] = 0;             //image
    this->ani[1] = 20;            //phase
    this->ani[2] = 0;             //counter
       
    this->energy = 100;
    this->radius = 16;
    
    
    this->last_measure = 0;
    this->timeLeft = 60;    
    this->gameOver = false;
    
    this->score = 0;
    this->shotCount = 0;
    this->alienCount = 0;
    this->alienDestroyed = 0;
    this->highscoreDone = false;
    this->showHighscore = false;
}

void Spaceship::update()
{
  if (fireCooldown > 0)
    fireCooldown--;  
}

bool Spaceship::hitBy(Sprite * sprite)
{
    energy -= 5;
    
    if (energy <= 0)
    {
        //engine->frag(sprite);
        return true;
    }   
    
    return false;
}
bool Spaceship::collisionWith(Sprite * sprite)
{   
    if (sprite->spriteNr == 2) {
        return true;        
    }
    energy -= 25;
    if (energy <= 0)
    {
      return true;
    }
    
    return false;
}


void Spaceship::up()
{
    if (steer == 0 || steer < 0) {
        steer = minSteer;
    }
     y += steer;
    if (y > 498) {
        y = 498;
    }    
}

void Spaceship::down()
{
    if (steer == 0 || steer < 0) {
        steer = minSteer;
    }
    y -= steer;
    if (y < 71) {
        y = 71;
    }
}

void Spaceship::fire(Engine * engine)
{
    if (fireCooldown > 0)
        return;
    
    fireCooldown = 10;  
    
    Shot * s = new Shot(engine, x+15, y, x+15+200,y , 0, 30, 8);           
    engine->snd->stopPlay(1);    
    engine->snd->play(1, s->listenerPos, 0.01);
    shotCount++;
}

void Spaceship::accelerate()
{
  speed += 1;
  steer += 1;
  if (speed > maxSpeed) {
    speed = maxSpeed;    
  }
  if (steer > maxSteer) {
      steer = maxSteer;
  }
}

void Spaceship::brake()
{
  speed -= 1;
  steer -= 1;
  if (speed < minSpeed) {
    speed = minSpeed;
  }
  if (steer < minSteer) {
      steer = minSteer;
  }
}


void Spaceship::getCoords(int * x, int * y)
{
  *x = this->x;
  *y = this->y;

}

int Spaceship::getRadius()
{
  return this->radius;
}

void Spaceship::resetPlayer() {
    
    this->fireCooldown = 0;
    this->x = 10;
    this->y = 284;
    
    this->ani[0] = 0;             //image
    this->ani[1] = 20;            //phase
    this->ani[2] = 0;             //counter
    
    this->energy = 100;
    this->score = 0;
    
    this->speed = 0;
    this->steer = 0;

    this->last_measure = 0;
    this->timeLeft = 60;
    this->gameOver = false;
    this->shotCount = 0;
    this->alienCount = 0;
    this->alienDestroyed = 0;
    this->highscoreDone = false;
}

void Spaceship::addScore(int score) {
    this->score += score;
    this->alienDestroyed++;
}

void Spaceship::setGameOver() {
    this->gameOver = true;
}


void Spaceship::displayStats(int screenWidth, int screenHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    glViewport(0, 0, screenWidth, screenHeight); 
    glMatrixMode(GL_MODELVIEW ); 
    glLoadIdentity();     
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_BLEND);
    glColor4f(1,1,1,1);
    
    char buf[256];
    sprintf(buf, "Time: %d Energie: %d Score: %d", this->timeLeft,this->energy, this->score);
    afPrintAt(screenWidth-34*8, 60, buf);
}


void Spaceship::timer() {
    int time = time_millis();    
    if (time - this->last_measure > 1000)
    {
        this->last_measure = time;
        this->timeLeft--;
        if (this->timeLeft < 1) {
            this->setGameOver();
        }
    }
}

void Spaceship::regAlien() {
    this->alienCount++;
}
