/* $Id: targa.h,v 1.1 2005/02/09 03:19:43 dude Exp $ */

#ifndef __TARGA_H
#define __TARGA_H

class TargaFile
{
 public:

  int width, height;
  unsigned int * img;

  TargaFile(char * filename);
  ~TargaFile();
};

//int * loadTarga(char * filename);

#endif
