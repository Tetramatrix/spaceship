/* $Id: util.cc,v 1.1 2005/02/09 03:19:43 dude Exp $ */

#include "allincludes.h"

/* Stars */
static int starsV[200 * 2];
static float starsC[200 * 3];
static int starsS[200];

int time_millis()
{
  return glutGet(GLUT_ELAPSED_TIME);
}

float rand01()
{
  float r = rand();
  r /= RAND_MAX;
  return r;
}

float rand1()
{
  return (rand01() - 0.5)*2;
}


void initStars(int screenWidth, int screenHeight) {

    // init Stars
    
    for (int i = 0, n = 0; i < 200; i++) {
        starsV[n++] = rand()%screenWidth;
        starsV[n++] = rand()%(screenHeight-142)+71;
    }
    for (int i = 0, n = 0; i < 200; i++) {
        float c = 0.8 - rand01()/3;
        starsC[n++] = c;
        starsC[n++] = c;
        starsC[n++] = c;
    }
    for (int i = 0, n = 0; i < 200; i++) {
        starsS[n++] =  rand()%4 + 1;
    }
}

void displayStars(int screenWidth, int screenHeight) {
    
    //stars
    
    int sPos;
    for (int i = 0; i < 200; i++) {
        sPos = starsV[i*2] - starsS[i];
        if (sPos < 0) {
            sPos = screenWidth;
        }
        starsV[i*2] = sPos;
    }
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    glViewport(0, 0, screenWidth, screenHeight); 
    glMatrixMode(GL_MODELVIEW ); 
    glLoadIdentity();     
    glDisable(GL_BLEND);
    glColor4f(1.0,1.0,1.0,1.0);
    glPointSize(1);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_INT, 0, starsV);
    glColorPointer(3, GL_FLOAT, 0, starsC);
    glDrawArrays(GL_POINTS, 0, 200);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);    
   
}
