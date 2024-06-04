#include "allincludes.h"
 
Farbpfeile::Farbpfeile(float farbverlauf[][4]) {
 
     // init farbpfeile   
    
    maxPfeile = 15+1;
    currentPfeile = 0;
 
      float red, green, blue;
    for (int i=0;i<100;i++){
        red = farbverlauf[i][0];
        for (int j=74;j>0;j--) {          
            red-=0.01;
            farbpfeile[i][j][0]=red;
            farbpfeile[i][j][1]=farbverlauf[i][1];
            farbpfeile[i][j][2]=farbverlauf[i][2];
            farbpfeile[i][j][3]=farbverlauf[i][3]; 
        }
        red = farbverlauf[i][0];
        for (int j=75;j<149;j++) {
            red-=0.01;
            farbpfeile[i][j][0]=red;
            farbpfeile[i][j][1]=farbverlauf[i][1];
            farbpfeile[i][j][2]=farbverlauf[i][2];
            farbpfeile[i][j][3]=farbverlauf[i][3]; 
        }    
    }
    for (int i=100;i<200;i++){
        red = farbverlauf[i][0];
        blue = farbverlauf[i][3];
        for (int j=74;j>0;j--) {          
            red-=0.01;
            blue-=0.01;
            farbpfeile[i][j][0]=red;
            farbpfeile[i][j][1]=farbverlauf[i][1];
            farbpfeile[i][j][2]=blue;
            farbpfeile[i][j][3]=farbverlauf[i][3]; 
        }
        red = farbverlauf[i][0];
        blue = farbverlauf[i][3];
        for (int j=75;j<149;j++) {
            red-=0.01;
            blue-=0.01;
            farbpfeile[i][j][0]=red;
            farbpfeile[i][j][1]=farbverlauf[i][1];
            farbpfeile[i][j][2]=blue;
            farbpfeile[i][j][3]=farbverlauf[i][3]; 
        } 
    }
    for (int i=200;i<300;i++){
        green = farbverlauf[i][2];
        blue = farbverlauf[i][3];
        for (int j=74;j>0;j--) {          
            green-=0.01;
            blue-=0.01;
            farbpfeile[i][j][0]=farbverlauf[i][0];
            farbpfeile[i][j][1]=green;
            farbpfeile[i][j][2]=blue;
            farbpfeile[i][j][3]=farbverlauf[i][3]; 
        }
        green = farbverlauf[i][2];
        blue = farbverlauf[i][3];
        for (int j=75;j<149;j++) {
            green-=0.01;
            blue-=0.01;
            farbpfeile[i][j][0]=farbverlauf[i][0];
            farbpfeile[i][j][1]=green;
            farbpfeile[i][j][2]=blue;
            farbpfeile[i][j][3]=farbverlauf[i][3]; 
        } 
    }    
    for (int i=300;i<400;i++){
        green = farbverlauf[i][2];
        blue = farbverlauf[i][3];
        for (int j=74;j>0;j--) {          
            green-=0.01;
            blue-=0.01;
            farbpfeile[i][j][0]=farbverlauf[i][0];
            farbpfeile[i][j][1]=green;
            farbpfeile[i][j][2]=blue;
            farbpfeile[i][j][3]=farbverlauf[i][3]; 
        }
        green = farbverlauf[i][2];
        blue = farbverlauf[i][3];
        for (int j=75;j<149;j++) {
            green-=0.01;
            blue-=0.01;
            farbpfeile[i][j][0]=farbverlauf[i][0];
            farbpfeile[i][j][1]=green;
            farbpfeile[i][j][2]=blue;
            farbpfeile[i][j][3]=farbverlauf[i][3]; 
        }   
    }
    for (int i=400;i<500;i++){
        red = farbverlauf[i][2];
        green = farbverlauf[i][3];
        for (int j=74;j>0;j--) {          
            red-=0.01;
            green-=0.01;
            farbpfeile[i][j][0]=red;
            farbpfeile[i][j][1]=green;
            farbpfeile[i][j][2]=farbverlauf[i][2];
            farbpfeile[i][j][3]=farbverlauf[i][3]; 
        }
        red = farbverlauf[i][2];
        green = farbverlauf[i][3];
        for (int j=75;j<149;j++) {
            red-=0.01;
            green-=0.01;
            farbpfeile[i][j][0]=red;
            farbpfeile[i][j][1]=green;
            farbpfeile[i][j][2]=farbverlauf[i][2];
            farbpfeile[i][j][3]=farbverlauf[i][3]; 
        }   
    }
    for (int i=500;i<600;i++){
        red = farbverlauf[i][0];
        green = farbverlauf[i][1];
        for (int j=74;j>0;j--) {          
            red-=0.01;
            green-=0.01;
            farbpfeile[i][j][0]=red;
            farbpfeile[i][j][1]=green;
            farbpfeile[i][j][2]=farbverlauf[i][2];
            farbpfeile[i][j][3]=farbverlauf[i][3]; 
        }
        red = farbverlauf[i][0];
        green = farbverlauf[i][1];
        for (int j=75;j<149;j++) {
            red-=0.01;
            green-=0.01;
            farbpfeile[i][j][0]=red;
            farbpfeile[i][j][1]=green;
            farbpfeile[i][j][2]=farbverlauf[i][2];
            farbpfeile[i][j][3]=farbverlauf[i][3]; 
        }   
    }
  
    
};

void Farbpfeile::registerPfeile(int screenWidth,int screenHeight) { 
    int n = currentPfeile;
    for (int i=0;i<maxPfeile-currentPfeile;i++) {
        int randomPfeile[] = {0,0,0,0,0,0,1,1};
        int registerPfeil = randomPfeile[rand()%7];;
        if (registerPfeil == 1) {  
            pfeilePos[n][0] = rand()%screenWidth+screenWidth;
            pfeilePos[n][1] = rand()%(screenHeight-142)+71;
            pfeilePos[n][2] = (rand()%35+1) + (rand()%35+1)%4;
            pfeilePos[n][3] = rand()%600;;
            //printf("%d:%d:%d:%d\n", pfeilePos[currentPfeile][0], pfeilePos[currentPfeile][1], pfeilePos[currentPfeile][2],pfeilePos[currentPfeile][3]);            
            n++;           
        }
    }
    currentPfeile = n;
    //printf("%d\n", n);
}


void Farbpfeile::display(int screenWidth, int screenHeight) {
    
    // farbpfeile
        
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    glViewport(0, 0, screenWidth, screenHeight); 
    glMatrixMode(GL_MODELVIEW ); 
    glLoadIdentity();  
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_LUMINANCE);
    
    if (this->currentPfeile == 0) {
        printf("restart Farbpfeil...\n");
        this->registerPfeile(screenWidth,screenHeight);
    } else {
        //int n=farbpfeile->currentPfeile;
        for (int j=0;j<this->currentPfeile;j++) {
            this->pfeilePos[j][0]-=this->pfeilePos[j][2];
            if (this->pfeilePos[j][0] < -150) {
                for (int i=j;i<this->currentPfeile;i++) {
                    this->pfeilePos[i][0] = this->pfeilePos[i+1][0];
                    this->pfeilePos[i][1] = this->pfeilePos[i+1][1];
                    this->pfeilePos[i][2] = this->pfeilePos[i+1][2];
                    this->pfeilePos[i][3] = this->pfeilePos[i+1][3];                
                }
                this->currentPfeile--;
                this->registerPfeile(screenWidth,screenHeight);
                //printf("Farbpfeile:%d\n",farbpfeile->currentPfeile);
            }
        }       
    }
    
    glBegin( GL_POINTS );
        for (int j=0;j<this->currentPfeile;j++) {
            for (int i=0;i<150;i++) {
                glColor4f(this->farbpfeile[this->pfeilePos[j][3]][i][0],this->farbpfeile[this->pfeilePos[j][3]][i][1],this->farbpfeile[this->pfeilePos[j][3]][i][2],this->farbpfeile[this->pfeilePos[j][3]][i][3]); 
                glVertex2i(this->pfeilePos[j][0]+i,this->pfeilePos[j][1]);
            }
        }
    glEnd(); 
    
}

