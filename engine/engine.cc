#include "allincludes.h"

Engine::Engine()
{       
    for (int i = 0; i < NUM_MISSILES;i++) {
        missiles[i] = NULL;
    };

    for (int i = 0; i < NUM_TARGETS;i++) {
        targets[i] = NULL;
    };
    
    for (int i = 0; i < NUM_BLEND_SHAPES; blendShapes[i++] = NULL);
   
    // init sound    
    #ifdef HAVE_OPENAL
      snd = new OpenALSound();
    #else
      snd = new Sound();
    #endif
    
    // init alien
    image[0] = new TargaFile("data/alien.tga");
    
    // init exlposion
    image[1] = new TargaFile("data/xpl.tga");
    
    // init asteroid
    image[2] = new TargaFile("data/asteroid.tga");
    
    /* create texture object */    
    glBindTexture(GL_TEXTURE_2D, texName[0]);

    /* set up wrap & filter params */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    /* load tex image */     
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[1]->width, image[1]->height,0, GL_RGBA, GL_UNSIGNED_BYTE, image[1]->img);
}

Engine::~Engine()
{
}

void Engine::update()
{     
  for (int i = 0; i < NUM_BLEND_SHAPES; i++)
    if (blendShapes[i] != NULL)
      updateShape(blendShapes[i]);
}

inline void Engine::updateShape(Explosion * s)
{
  s->update();
   
  if (s->ttl >= 0)
    {
    s->ttl--;     
    if (s->ttl == 0) {
        unregisterBlendShape(s);
        delete s;
        }
    }
}

void Engine::display(Spaceship * player, int screenWidth, int screenHeight)
{
    // Store screen dimensions
    
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight; 
    
    // Store player
    
    this->player = player;

    if (this->player->energy > 0) {
        collision();
    }
    
    // Second Stage: Blending; Lighting Disabled; No depth buffer writes    
        
    glViewport(0, 0, this->screenWidth, this->screenHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();    
    gluPerspective(165.0, (GLfloat)this->screenWidth/(GLfloat)this->screenHeight, 0.1, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();  
    
    // Material Setup
    
    float ambientAndDiffuse[4];
    float specular[4];
    float shininess;
    
    ambientAndDiffuse[0] = 0.7;
    ambientAndDiffuse[1] = 0.7;
    ambientAndDiffuse[2] = 0.7;
    ambientAndDiffuse[3] = 0.7;
    
    specular[0] = 1.3;
    specular[1] = 1.3;
    specular[2] = 1.3;
    specular[3] = 1.3;
    
    shininess = 120;

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ambientAndDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);    
    
    // Lighting Setup
   
    float sunPosition[4], sunAmbient[4], sunDiffuse[4], sunSpecular[4];
    
    sunPosition[0] = -1;
    sunPosition[1] = 0;
    sunPosition[2] = 0;
    sunPosition[3] = 0;
    
    sunAmbient[0] = 2;
    sunAmbient[1] = 2;
    sunAmbient[2] = 2;
    sunAmbient[3] = 2;
    
    sunDiffuse[0] = 1.4;
    sunDiffuse[1] = 1.4;
    sunDiffuse[2] = 1.4;
    sunDiffuse[3] = 1.4;
    
    sunSpecular[0] = 3;
    sunSpecular[1] = 3;
    sunSpecular[2] = 3;
    sunSpecular[3] = 3;
    
    glLightfv(GL_LIGHT0, GL_POSITION, sunPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, sunAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sunDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, sunSpecular);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);  

    /* set culling params */
    
    glEnable(GL_CULL_FACE);		
    glCullFace(GL_BACK);		/* cull back facing polygons */
    
    /* disable depth buffering */
    
    glDisable(GL_DEPTH_TEST);
    
    /* set texturing function */
    
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    //glBlendFunc(GL_SRC_ALPHA, GL_DST_COLOR);   

    for (int n = 0; n < NUM_BLEND_SHAPES; n++) {
        if (blendShapes[n] != NULL)
          {   
            blendShapes[n]->render();
          }
      }
    
    glDisable(GL_TEXTURE_2D); 
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);      
    glDisable(GL_LIGHTING);      
}



void Engine::registerMissile(Shot * m)
{
  for (int i = 0; i < NUM_MISSILES; i++)
    if (missiles[i] == NULL)
      {
	missiles[i] = m;
	return;
      }
}

void Engine::unregisterMissile(Shot * m)
{
  for (int i = 0; i < NUM_MISSILES; i++)
    if (missiles[i] == m)
      {
	missiles[i] = NULL;
	return;
      }
}

void Engine::registerTarget(Sprite * t)
{
  for (int i = 0; i < NUM_TARGETS; i++)
    if (targets[i] == NULL)
      {
	targets[i] = t;
	return;
      }
}

void Engine::unregisterTarget(Sprite * t)
{
  for (int i = 0; i < NUM_TARGETS; i++)
    if (targets[i] == t)
      {
	targets[i] = NULL;
	return;
      }
}

void Engine::registerBlendShape(Explosion * s)
{
  for (int i = 0; i < NUM_BLEND_SHAPES; i++)
    if (blendShapes[i] == NULL)
      {
	blendShapes[i] = s;
	return;
      }
}

void Engine::unregisterBlendShape(Explosion * s)
{
  for (int i = 0; i < NUM_BLEND_SHAPES; i++)
    if (blendShapes[i] == s)
      {
	blendShapes[i] = NULL;
	return;
      }
}

void Engine::collision()
{    
    // Raumschiff
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    glViewport(0, 0, this->screenWidth, this->screenHeight); 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); 
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);     
    
    player->ani[2]++;
    if (player->ani[1] == player->ani[2]) {
        player->ani[2] = 0;
        player->ani[0]++;
        if (player->ani[0] > 3) {
            player->ani[0] = 0;
        }
    }
   
    player->x += player->speed;
    if (player->x > this->screenWidth-(player->image[0]->width)) {
        player->x = this->screenWidth-(player->image[0]->width);
    } else if (player->x < 0) {
        player->x = 0;
    }     
    if (player->y < 71) {
        player->y = 71;
    } else if (player->y > 498) {
        player->y = 498;
    }  
    
    glRasterPos2i(player->x, player->y);
    glDrawPixels(player->image[0]->width, player->image[0]->height, GL_RGBA, GL_UNSIGNED_BYTE, player->image[player->ani[0]]->img);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    glViewport(0, 0, screenWidth, screenHeight); 
    glMatrixMode(GL_MODELVIEW ); 
    glLoadIdentity();     
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_BLEND);
    glEnable( GL_LINE_SMOOTH );
    glLineWidth( 1.0 );
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    for (int i = 0; i < NUM_MISSILES; i++) { 
        
        if (missiles[i] != NULL) {
            Shot * m = missiles[i];
            
            float dx = m->target_x - m->x;            
            float dy = m->target_y - m->y;
            if (dx == 0) {
                dx = 1.0;
            }
            if (dy == 0) {
                dy = 1.0;
            }
            float dr = roundf(sqrt(dx*dx + dy*dy));
            dx /= dr;
            dy /= dr;
            m->x += (int)roundf(dx * m->speed);
            m->y += (int)roundf(dy * m->speed);            
            int xv = m->x + (int)roundf(dx * m->shotLength);
            int yv = m->y + (int)roundf(dy * m->shotLength);
            
            if (dr < m->maxRange) {
                unregisterMissile(m);
                delete m;

            } else {      
          
                // target collision
                
                int tx = 0, ty = 0;
                m->getCoords(&tx, &ty);
                int tr = m->getRadius();
                
                bool delM = false;
                for (int j = 0; j < NUM_TARGETS; j++) {
                  if (targets[j] != NULL)
                    {
                        Sprite * t = targets[j];
                        
                        int ux = 0, uy = 0;
                        t->getCoords(&ux, &uy);
                        int ur = t->getRadius();
                        
                        int dx = ux - tx;
                        int dy = uy - ty-8;
     
                        int d2 = dx*dx + dy*dy;
                        int rs = ur + tr;
                        
                        if (d2 < rs*rs)
                        {
                            delM = m->hit(t);
                            bool delT = t->hitBy(m);
                           
                            if (delT) {
                                int score = t->getScore();
                                player->addScore(score);
                                unregisterTarget(t);
                                delete t;
                            }
                        }                
                    }
                }
                
                // player collision
                
                if (m->shotNr == 1) {
                    int ux = 0, uy = 0;
                    ux = this->player->x+15;
                    uy = this->player->y+10;
                    int ur = this->player->radius/2;
                    
                    int dx = ux - tx;
                    int dy = uy - ty;
    
                    int d2 = dx*dx + dy*dy;
                    int rs = ur + tr;
                    
                    if (d2 < rs*rs)
                    {
                        delM = t->hit();
                        bool delT = player->hitBy(t);
                       
                        if (delM) {
                            snd->stopPlay(6);
                            snd->play(6, m->listenerPos, 0.002);
                        }
                        if (delT) {
                            snd->stopPlay(3);
                            snd->play(3, m->listenerPos, 0.002); 
                            player->setGameOver();
                            return;
                        }
                    }
                }
                
                if (delM) {
                    unregisterMissile(m);
                    delete m;
                
                } else {
                    
                    switch (m->shotNr) {                
                        case 0:
                            m->sV[0] = m->x;
                            m->sV[1] = m->y+2;
                            m->sV[2] = xv;
                            m->sV[3] = yv+2;
                        
                            m->sV[4] = m->x;
                            m->sV[5] = m->y+29;
                            m->sV[6] = xv;
                            m->sV[7] = yv+29;   
        
                            glVertexPointer(2, GL_INT, 0, m->sV);
                            glColorPointer(4, GL_FLOAT, 0, m->sC);
                            glDrawArrays(GL_LINES, 0, 4);                 
                            break;
                        
                        case 1:                        
                            m->sV[0] = m->x;
                            m->sV[1] = m->y;
                            m->sV[2] = xv;
                            m->sV[3] = yv;
        
                            glVertexPointer(2, GL_INT, 0, m->sV);
                            glColorPointer(4, GL_FLOAT, 0, m->sC);
                            glDrawArrays(GL_LINES, 0, 2);
                            break;
                    }
                }
            }
        }
    }  

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY); 
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    glViewport(-(image[0]->width*2), 0, screenWidth+(image[0]->width*2), screenHeight); 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); 
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
    
    for (int i = 0; i < NUM_TARGETS; i++) { 
        if (targets[i] != NULL) {
            
            Sprite * t = targets[i]; 
            
            t->x -= t->speed;
            if (t->x < -(image[0]->width*2)) {
                unregisterTarget(t);
                delete t;                
            } else {
            
                if (t->spriteNr == 2) {
                    float x = rand1();
                    float y = rand1();
                    float d = sqrt(x*x + y*y)*10 / 40;
                    x /= d;
                    y /= d;
                    t->x += (int) roundf(fmsin(x));
                    t->y += (int) roundf(fmsin(y));
                    
                } else { 
                   
                   t->update(this, player->radius, player->x, player->y); 
                }
                
                if (t->y < 71) {
                    t->y = 71;
                } else if (t->y > 498) {
                    t->y = 498;
                } 
                            
                int tx = 0, ty = 0;
                t->getCoords(&tx, &ty);
                int tr = t->getRadius();
                
                int ux = 0, uy = 0;
                ux = this->player->x+30;
                uy = this->player->y+20;
                int ur = this->player->radius;
                
                int dx = ux - tx;
                int dy = uy-10 - ty;
                
                int d2 = dx*dx + dy*dy;
                int rs = ur + tr;            
                
                if (d2 < rs*rs)
                {
                    if (t->spriteNr == 0) {
                        
                        bool delT = t->collisionWith();
                        bool delS = this->player->collisionWith(t);
                     
                        if (delT) {
                            unregisterTarget(t);
                            delete t;
                        }    
                        if (delS) {
                            player->setGameOver();
                            return;
                        }                    
        
                    } else {
                        
                        bool delT = t->collisionWith();
                        if (delT) {
                            unregisterTarget(t);
                            delete t;
                        }
                        player->setGameOver();
                        return;
                    }
                }
                
                for (int j = 0; j < NUM_TARGETS; j++) { 
                    
                    if (targets[j] != NULL && targets[j] != t) {                    
                        Sprite * u = targets[j]; 
                        u->getCoords(&ux, &uy);
                        int ur = u->getRadius();
     
                        int dx = ux - tx;
                        int dy = uy - ty;
                
                        int d2 = dx*dx + dy*dy;
                        int rs = ur + tr;            
                
                        if (d2 < rs*rs)
                        {    
                            if (t->spriteNr == 2 && u->spriteNr == 0) {
                                bool delT = u->collisionWith();
                                if (delT) {
                                    unregisterTarget(u);
                                    delete u;
                                }
                            }    
    
                            if ( t->spriteNr == 0 && u->spriteNr == 2) {
                                bool delT = t->collisionWith();
                                if (delT) {
                                    unregisterTarget(t);
                                    delete t;
                                }                            
                            }
                        }
                    }
                }
                    
                glRasterPos2i(t->x, t->y);
                glDrawPixels(image[t->spriteNr]->width, image[t->spriteNr]->height, GL_RGBA, GL_UNSIGNED_BYTE, image[t->spriteNr]->img);           
            }
        }
    }
}

void Engine::frag(Sprite * s)
{
  float rad = s->getRadius();

  //for (int i = 0; i < rad*2 + 3; i++)
  for (int i = 0; i < 13; i++)
    {
    
    Explosion * e = new Explosion(this);    
    
    //int focal_distance = 38;        
    int focal_distance = 19;
        
    float dx = ((float)s->x-400)/focal_distance;
    float dy = ((float)s->y-300)/focal_distance;
        
    float x = rand1();
    float y = rand1();
    float z = rand1();
    float d = sqrt(x*x + y*y + z*z)*20 / (rad);

    x /= d;
    y /= d;
    z /= -d;
    x += dx;
    y += dy;

    float size = (1+rand01()*13) / rad;
    // fadeout time
    int ttl = 50+rand()%50;
    // fadein time
    int fadettl = (int) (ttl * (1-rand01()/2));
    
    e->x = x;
    e->y = y;
    e->z = z;
    
    e->size = size;
    e->ttl = ttl;
    e->fadettl = fadettl;
    e->fadeAlphaRef = 0.7;

    }
}


void Engine::resetEngine() {
    
    for (int i = 0; i < NUM_MISSILES;i++) {
        missiles[i] = NULL;
    };

    for (int i = 0; i < NUM_TARGETS;i++) {
        targets[i] = NULL;
    };
    
    for (int i = 0; i < NUM_BLEND_SHAPES; blendShapes[i++] = NULL);    
}


