#include "allincludes.h"

Particle::Particle(Engine * engine, int texnr): TNVShape(engine->getTNVProto(0), engine->getTextureProto(texnr))
{
  this->engine = engine;
  engine->registerBlendShape(this);
  billboard = true;
}

Particle::~Particle()
{
  engine->unregisterBlendShape(this);
//  engine->msgListener->invalidShape(this);
}
