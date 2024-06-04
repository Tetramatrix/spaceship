#ifndef SHOT_H
#define SHOT_H

class Shot 
{   
    public:
        
        Engine * engine;
        class Sprite * t;
            
        int x, y, shotLength, sV[8], speed, radius, maxRange, range, target_x, target_y, shotNr;
        
        float sC[16],listenerPos[3];
    
        Shot(Engine * engine, int x, int y, int target_x, int target_y, int shotNr, int maxRange, int speed); 
                
        bool hit(Sprite * t);
        void getCoords(int*, int*);
        int getRadius();
        
};

#endif
