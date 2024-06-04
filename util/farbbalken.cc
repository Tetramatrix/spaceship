#include "allincludes.h"

Farbbalken::Farbbalken() {

    farbPos = 0;
    scPos = 0;
    
    // init farbbalken
    
    float color = 0;    
    for (int i=0;i<100;i++){
        color += 0.01;
        farbverlauf[i][0] = 1.0;
        farbverlauf[i][1] = 0.0;
        farbverlauf[i][2] = color;
        farbverlauf[i][3] = 1.0;
    }
    color = 1.0;
    for (int i=100;i<200;i++){
        color -= 0.01;
        farbverlauf[i][0] = color;
        farbverlauf[i][1] = 0.0;
        farbverlauf[i][2] = 1.0;
        farbverlauf[i][3] = 1.0;
    }
    color = 0.0;
    for (int i=200;i<300;i++){
        color += 0.01;
        farbverlauf[i][0] = 0.0;
        farbverlauf[i][1] = color;
        farbverlauf[i][2] = 1.0;
        farbverlauf[i][3] = 1.0;
    }
    color = 1.0;
    for (int i=300;i<400;i++){
        color -= 0.01;
        farbverlauf[i][0] = 0.0;
        farbverlauf[i][1] = 1.0;
        farbverlauf[i][2] = color;
        farbverlauf[i][3] = 1.0;
    }
    color = 0.0;
    for (int i=400;i<500;i++){
        color += 0.01;
        farbverlauf[i][0] = color;
        farbverlauf[i][1] = 1.0;
        farbverlauf[i][2] = 0.0;
        farbverlauf[i][3] = 1.0;
    }    
    color = 1.0;
    for (int i=500;i<600;i++){
        color -= 0.01;
        farbverlauf[i][0] = 1.0;
        farbverlauf[i][1] = color;
        farbverlauf[i][2] = 0.0;
        farbverlauf[i][3] = 1.0;
    }        
    
    int phase = 2;
    for (int i=0;i<600;i++){        
        for (int j=0;j<phase;j++) {
            farbbalken[i*phase+j][0] = farbverlauf[i][0];
            farbbalken[i*phase+j][1] = farbverlauf[i][1];
            farbbalken[i*phase+j][2] = farbverlauf[i][2];
            farbbalken[i*phase+j][3] = farbverlauf[i][3];
            //printf("%f:",farbbalken[i*phase+j+600*phase][0]);
        }
    }
    for (int i=0;i<600;i++){        
        for (int j=0;j<phase;j++) {
            farbbalken[i*phase+j+600*phase][0] = farbverlauf[i][0];
            farbbalken[i*phase+j+600*phase][1] = farbverlauf[i][1];
            farbbalken[i*phase+j+600*phase][2] = farbverlauf[i][2];
            farbbalken[i*phase+j+600*phase][3] = farbverlauf[i][3];
        }
    }   

    // init scroller colors
    
    int n=0;
    for (int i=0;i<150;i++) {
        scColorV[n++]=0;                
        scColorV[n++]=i+100;
        scColorV[n++]=800;                
        scColorV[n++]=i+100;
    }  
}


void Farbbalken::displayBalken(int screenWidth, int screenHeight) {

    // Farbbalken
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    glViewport(0, 0, screenWidth, screenHeight); 
    glMatrixMode(GL_MODELVIEW ); 
    glLoadIdentity();     
    glDisable(GL_BLEND);
    
    this->farbPos += 6;
    if (this->farbPos > 600*2) {
        this->farbPos=0;
    }

    glBegin( GL_POINTS );
        for (int i=0;i<screenWidth;i++) {    
            glColor4f(this->farbbalken[farbPos+360+i][0],this->farbbalken[farbPos+360+i][1],this->farbbalken[farbPos+360+i][2],this->farbbalken[farbPos+360+i][3]); 
            glVertex2i(i, 70);
            glColor4f(this->farbbalken[farbPos+360+i][0],this->farbbalken[farbPos+360+i][1],this->farbbalken[farbPos+360+i][2],this->farbbalken[farbPos+360+i][3]); 
            glVertex2i(i, 71);            
        }
    glEnd();

    glBegin( GL_POINTS );
        for (int i=0;i<screenWidth;i++) {    
            glColor4f(this->farbbalken[farbPos+i][0],this->farbbalken[farbPos+i][1],this->farbbalken[farbPos+i][2],this->farbbalken[farbPos+i][3]); 
            glVertex2i(i, 530);
            glColor4f(this->farbbalken[farbPos+i][0],this->farbbalken[farbPos+i][1],this->farbbalken[farbPos+i][2],this->farbbalken[farbPos+i][3]);
            glVertex2i(i, 531);            
        }
    glEnd();
        
}

void Farbbalken::displaySC(int screenWidth, int screenHeight) {

    // Scrollercolor
          
    scPos++;
    if (scPos > 600*2) {
        scPos = 0 ;
    }
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    glViewport(0, 0, screenWidth, screenHeight); 
    glMatrixMode(GL_MODELVIEW ); 
    glLoadIdentity();     
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_CONSTANT_COLOR, GL_ONE_MINUS_SRC_COLOR);
    glPointSize(1);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_INT, 0, scColorV);
    glColorPointer(4, GL_FLOAT, 0, this->farbbalken[scPos]);
    glDrawArrays(GL_LINES, 0, 300);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);    

}
