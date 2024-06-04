#ifndef SPACESHIP_H
#define SPACESHIP_H

class Spaceship 
{
  
 public:
 
    int fireCooldown;
    int x, y, speed, maxSpeed, minSpeed, ani[3];
    int steer, maxSteer, minSteer, energy, radius, score, last_measure, timeLeft, shotCount, alienCount, alienDestroyed;
    float listenerPos[3];
    bool gameOver, highscoreDone, showHighscore;
 
    bool hitBy(Sprite * sprite);
    bool collisionWith(Sprite * sprite);
    void getCoords(int*, int*);
    int getRadius();
    void resetPlayer();
 
    class Engine * engine;
    class Shot * s;
    class TargaFile * image[4];
    class Sprite * sprite;
 
    Spaceship(Engine * engine);
    
    virtual void up();
    virtual void down();
    virtual void fire(Engine * engine);
    virtual void accelerate();
    virtual void brake();
    virtual void update();
    virtual void addScore(int score);
    virtual void setGameOver();
    virtual void timer();
    virtual void displayStats(int screenWidth, int screenHeight);
    virtual void regAlien();
    
};

#endif
