#ifndef SPRITE_H
#define SPRITE_H

class Sprite
{     
    public:
        
        class Shot * s;            
        class Engine * engine;
            
        int x, y, speed, energy, radius, score, spriteNr, shotTime, shotMaxRange, last_measure; 
        int shotLength, shotRadius, player_rad, player_x, player_y, shotSpeed;
        
        float listenerPos[3];
        
        Sprite(Engine * engine, int x, int y, int speed, int spriteNr);
        
        bool hit();
        bool hitBy(Shot * s);
        bool collisionWith();
        
        virtual void update(Engine * engine, int player_rad, int player_x, int player_y);
        
        virtual void getCoords(int*, int*);
        virtual int getRadius();
        virtual int getScore();

};

#endif
