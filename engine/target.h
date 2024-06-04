#ifndef TARGET_H
#define TARGET_H

class Target
{
  
 public:
        
  enum target_type { TRASH, SPACESHIP };

  target_type type;
  bool solid;

  Target(target_type type);
  virtual ~Target();

  //virtual bool hitBy(Missile*);
  //virtual bool collisionWith(Target*);

  //cvirtual void getCoords(int x, int y) = 0;
  //virtual float getRadius() = 0;
  //virtual void getVelocity(float*, float*, float*) = 0;
};

#endif
