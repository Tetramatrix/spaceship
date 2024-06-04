/* $Id: fileio.h,v 1.1 2005/02/09 03:19:43 dude Exp $ */

#ifndef FILEIO_H
#define FILEIO_H

class File
{
 public:

  char * filename;

  File(char * filename);
  ~File();

  int size();
  void read(void * buf);
  void write(void * buf, int bufSize);
};

#endif
