
#include "allincludes.h"

Logo::Logo(int width, int height, unsigned int * pointer)
{
    wobblePos = 0.0;
    
    img = new unsigned int[width];
    
    for (int i=0;i<width;i++) {
        img[i] = pointer[i+height*width];
    }    
};


void Logo::display(int screenWidth, int screenHeight, TargaFile * image, Logo * wobbler[]) {
 
    // Logo
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    //glViewport(-32, 0, mainMod->screenWidth+32, mainMod->screenHeight); 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); 
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    this->wobblePos += 0.1;
    if (this->wobblePos > 63) {
        this->wobblePos = 0.0;
    }
    float wPos = this->wobblePos;
    for (int i=0;i<image->height;i++) {
        glRasterPos2i(screenWidth/2 - image->width/2 +(int) roundf(fmcos(wPos)*10 + 20), 400 - image->height/2 + i);
        glDrawPixels(image->width, 1, GL_RGBA, GL_UNSIGNED_BYTE, wobbler[i]->img);;
        wPos+= 0.1;
    }    
}

