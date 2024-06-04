#ifndef PARTICLE_H
#define PARTICLE_H

class Particle : public TNVShape
{
 public:

  Engine * engine;

  Particle(Engine * engine, int texnr);
  virtual ~Particle();
};

#endif
