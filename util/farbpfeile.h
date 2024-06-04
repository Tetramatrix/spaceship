#ifndef __FARBPFEILE_H
#define __FARBPFEILE_H

class Farbpfeile
{
 public:
    
    float farbverlauf[][4];
    float farbpfeile[600][150][4];   
 
    int maxPfeile,currentPfeile;
    int screenWidth,screenHeight;
    int pfeilePos[][4];
 
    Farbpfeile(float farbverlauf[][4]);

    void Farbpfeile::registerPfeile(int screenWidth,int screenHeight);
    void Farbpfeile::display(int screenWidth, int screenHeight);
 
};

#endif
