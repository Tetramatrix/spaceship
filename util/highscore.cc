#include "allincludes.h"

const int screenWidth = 800;
const int screenHeight = 600;

Highscore::Highscore(char * filename)
{  
    //PlayerStats c;
    //this->HighscoreList[10] = c;
    
    File * file = new File(filename);
    int x = file->size();
    highscoreFile = new char[x];
    file->read(highscoreFile);  
    delete file;    
    
    int s1, a1, s2, a2, s3, a3, s4, a4, s5, a5, s6, a6, s7, a7, s8, a8, s9, a9, s10, a10;            
    sscanf(highscoreFile,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", &s1, &a1, &s2, &a2, &s3, &a3, &s4, &a4, &s5, &a5, &s6, &a6, &s7, &a7, &s8, &a8, &s9, &a9, &s10, &a10);    
            
    HighscoreList[0].score = s1;
    HighscoreList[1].score = s2;
    HighscoreList[2].score = s3;
    HighscoreList[3].score = s4;
    HighscoreList[4].score = s5;
    HighscoreList[5].score = s6;
    HighscoreList[6].score = s7;
    HighscoreList[7].score = s8;
    HighscoreList[8].score = s9;
    HighscoreList[9].score = s10;
    
    HighscoreList[0].accuracy = a1;       
    HighscoreList[1].accuracy = a2;       
    HighscoreList[2].accuracy = a3;       
    HighscoreList[3].accuracy = a4;       
    HighscoreList[4].accuracy = a5;       
    HighscoreList[5].accuracy = a6;       
    HighscoreList[6].accuracy = a7;       
    HighscoreList[7].accuracy = a8;       
    HighscoreList[8].accuracy = a9;       
    HighscoreList[9].accuracy = a10;   
    
    printf("%s\n",filename);  
}

void Highscore::save(char * filename)
{  
    int size=0;
    char buf[256];
    for (int i=0;i<10;i++) {    
       size+=sprintf(buf+size, "%d,%d,", HighscoreList[i].score, HighscoreList[i].accuracy);
    }    
    File * file = new File(filename);
    file->write(&buf, size);
    delete file;
    
}

void Highscore::showHighscore() {
    int i;
    char buf[256];

    sprintf(buf, "Highscore");
    afPrintAt(screenWidth/2-4*8, screenHeight/2+30, buf);
    
    sprintf(buf, "---------");
    afPrintAt(screenWidth/2-4*8, screenHeight/2+20, buf);

    for (i=1;i<10;i++) {
        sprintf(buf, "%d: Score:%d, Accuracy:%d", i, HighscoreList[i-1].score, HighscoreList[i-1].accuracy);
        afPrintAt(800/2-12*8, 600/2+10-i*10, buf);
    }    
    sprintf(buf, "%d: Score:%d, Accuracy:%d", i, HighscoreList[i-1].score, HighscoreList[i-1].accuracy);
    afPrintAt(800/2-13*8, 600/2+10-10*10, buf);
}

void Highscore::makeHighscore(int rang, int score, int shotsFired, int alienDestroyed, int totalAliens, int accuracy) {
    PlayerStats c; 
    c.rang = rang; 
    c.score = score;
    c.shotsFired = shotsFired;
    c.alienDestroyed = alienDestroyed; 
    c.totalAliens = totalAliens; 
    c.accuracy = accuracy;
    
    int i, j, k;
    PlayerStats tmp[10];
    
    for (i=0;i<10;i++) {
        if (HighscoreList[i].score <= c.score) {
            if (HighscoreList[i].score < c.score) {
                break;
            } else if (HighscoreList[i].accuracy <= c.accuracy) {
                break;
            }
        }
    }    
    j=i;
    k=0;
    for (i=j;i<10;i++) {
        tmp[k] = HighscoreList[i];
        k++;
    }    
    HighscoreList[j]=c;
    j++;
    k=0;
    for (i=j;i<10;i++) {
        HighscoreList[i] = tmp[k];
        k++;
    }
    
    this->save("data/highscore.txt");
}
