#ifndef __FARBPFEILE_H
#define __FARBPFEILE_H

class Farbpfeile
{
 public:
        
    float farbpfeile[600][150][4];   
 
    int maxPfeile,currentPfeile;
    int screenWidth,screenHeight;
     
    Farbpfeile(float farbverlauf[][4]);

    void registerPfeile(int screenWidth,int screenHeight);
    void display(int screenWidth, int screenHeight);
    	
    float farbverlauf[2000][4];
    
    int pfeilePos[][4];
 
};

#endif
