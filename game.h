#ifndef GAME_H
#define GAME_H


class Game : public Main
{

    public:

        /* 3D engine */
        class Engine * engine;
         
        /* Player */
        class Spaceship * player;
    
        class Highscore * highscore[1];
        
        /* Keyboard state */
        int keys[256];
        
        char buf[256];
        
            
        Game();
       
        
        void keyboard(unsigned char key, int state);
        void keyboardSpecial(int key, int state);
        
        void update();
        void display();
        
        void alienControl();
        void playerControl();
        void playerStats();
        
        void resetGame();
        void skipIntro();
        void setPause();
        
};

#endif
