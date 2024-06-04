#ifndef __HIGHSCORE_H
#define __HIGHSCORE_H

class Highscore
{
    public:
        
        char * highscoreFile; 
    
        typedef struct {
            int rang;
            int score;
            int shotsFired;
            int alienDestroyed;
            int totalAliens;    
            int accuracy;        
        } PlayerStats;
        
        PlayerStats HighscoreList[10];
        
        Highscore(char * filename);
        
        void save(char * filename);
        void makeHighscore(int rang, int score, int shotsFired, int alienDestroyed, int totalAliens, int accuracy);
        void showHighscore();
};

#endif
