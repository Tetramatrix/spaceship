#ifndef __FARBBALKEN_H
#define __FARBBALKEN_H

class Farbbalken
{
 public:
     
    float farbverlauf[600][4]; 
    float farbbalken[600*10][4];
    int farbPos, scPos;
 
    /* Scrollercolor */
    int scColorV[150*4];
 
    Farbbalken();
 
    void displayBalken(int screenWidth, int screenHeight);
    void displaySC(int screenWidth, int screenHeight);
 
};

#endif
