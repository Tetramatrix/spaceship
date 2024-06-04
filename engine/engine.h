#ifndef ENGINE_H
#define ENGINE_H


const int NUM_TARGETS = 128; 
const int NUM_MISSILES = 128;
const int NUM_BLEND_SHAPES = 128;

class Engine
{ 
    
    class Shot * missiles[NUM_MISSILES];      
    class Sprite * targets[NUM_TARGETS];
    class Explosion * blendShapes[NUM_BLEND_SHAPES];          
      
    int screenWidth, screenHeight;     
        
    public:
    
        class Sound * snd;
        class Spaceship * player;   
        class Shot * m;      
        class Sprite * t;
        class Explosion * s;
            
        GLuint texName[2];		/* store of ground texture reference */
        
        TargaFile * image[3];
        
        Engine();
        ~Engine();
        
        void update();
        void display(Spaceship * player, int sw, int sh);
    
        void collision();
        void updateShape(Explosion * s);
        
        void registerBlendShape(class Explosion * s);
        void unregisterBlendShape(class Explosion * s);
      
        void registerMissile(class Shot * m);
        void unregisterMissile(class Shot * m);
            
        void registerTarget(class Sprite * t);
        void unregisterTarget(class Sprite * t);            

        void frag(Sprite * s);
        
        void resetEngine();
            
};

#endif
