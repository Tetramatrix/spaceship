#ifndef MAIN_H
#define MAIN_H

class Main
{
    public:

        /* module state */
        
        int updates_per_second;
        int screenWidth, screenHeight;
    
        bool intro;
    
        /* Logo */
        TargaFile * image[1];
        
        /* Wobbler */
        Logo * wobblerImg[4096];
        
        /* Farbbalken */
        Farbbalken * farbbalken;
        
        /* Farbpfeile */
        Farbpfeile * farbpfeile;
    
        /* constructor */
        
        Main();
        
        /* functions */
        
        
        
        /* virtuals */        
    
        virtual void update();
        virtual void display();  
        virtual void keyboard(unsigned char key, int state);  
        virtual void keyboardSpecial(int key, int state);   
        virtual void resetGame();
        virtual void skipIntro();
        virtual void setPause();
};

#endif
