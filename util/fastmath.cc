/* $Id: fastmath.cc,v 1.1 2005/02/09 14:45:06 dude Exp $ */

#include "allincludes.h"

#define SIN_TABLE_LEN 32768

float sintable[SIN_TABLE_LEN];

void fmInit()
{
  for (int i = 0; i < SIN_TABLE_LEN; i++)
    {
      float ang = ((float) i) * (2 * M_PI) / SIN_TABLE_LEN;
      sintable[i] = sin(ang);
    }
    printf("fmInit: sinustab ready\n");
}
float fmsin(float angle)
{
  if (angle < 0)
    return -fmsin(-angle);
  int i = (int) (angle * (float)SIN_TABLE_LEN / (2 * M_PI));
  i %= SIN_TABLE_LEN;
  return sintable[i];
}

float fmcos(float angle)
{
  return fmsin(angle + M_PI/2);
}
