#ifndef EXPLOSION_H
#define EXPLOSION_H

class Explosion{

    public:
    
        class Engine * engine;    
        float x, y, z, drift;
        
        float color[4];       
        
        float fadeAlphaRef;
        bool fadesize;
        float fadesizeref;
        float fadettl;
        float ttl;
        float size;       
        
        Explosion(Engine * engine);    
    
        void render();
        void update();
};


#endif
