#ifndef __LOGO_H
#define __LOGO_H

class Logo
{
 public:
     
     unsigned int * img;
     unsigned int * pointer;
     TargaFile * image; 
     
 
     int width, height;
     float wobblePos;
 
     Logo(int width, int scanline, unsigned int * pointer);
     void display(int screenWidth, int screenHeight, TargaFile * image, Logo * wobbler[]);
     	
     Logo * wobbler[];
};

#endif
