#include "allincludes.h"

Explosion::Explosion(Engine * engine) 
{
    this->engine = engine;
    this->x = x;
    this->y = y;
    this->z = z;
    this->drift = 0;
    
    this->size = 1;
    
    this->fadesize = true;
    this->fadesizeref = 1.43677;
    this->fadettl = 0;
    this->ttl = 0;
    
    this->color[0] = 1;
    this->color[1] = 1;
    this->color[2] = 1;
    this->color[3] = 1;       
                                 
    engine->registerBlendShape(this);
}

void Explosion::render() {
    
    //printf("%f:%f:%f\n",x,y,z);    
   
    glPushMatrix();
    glTranslatef( this->x+this->drift, this->y, -1.0 );  
    //glTranslatef( 0, 0, -1.0 );  
    
    glScalef( size, size, 1.0);
   
    glRotatef( rand1()*size*3, 0.0, 0.0, 1.0 );
    //glRotatef( rand1()*size*5, 0.0, 1.0, 0.0 );
    //glRotatef( rand1()*size*7, 1.0, 0.0, 0.0 );
    
    glColor4f(color[0],color[1],color[2],color[3]);      
    
    glBegin(GL_QUADS);
        glNormal3f(0.0, 0.0, 1.0);
        
        glTexCoord2f(1.0, 0.0);
        glVertex3f(1.0, -1.0, -1.0);
        
        glTexCoord2f(1.0, 1.0);
        glVertex3f(1.0, 1.0, -1.0);
        
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-1.0, 1.0, -1.0);
        
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-1.0, -1.0, -1.0);
    glEnd();
    
    glPopMatrix();
}

void Explosion::update() {

    if (fadettl > 0 && ttl < fadettl)
    {
        color[3] = (float) ttl * fadeAlphaRef / (float) fadettl;
        drift+=0.05;
        if (fadesize) {
        size = (float) ttl * fadesizeref / (float) (fadettl );        
        //printf("%f:",size);
        }
    }
}
