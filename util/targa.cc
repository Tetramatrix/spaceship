/* $Id: targa.cc,v 1.1 2005/02/09 03:19:43 dude Exp $ */

#include "allincludes.h"

TargaFile::TargaFile(char * filename)
{
  File * file = new File(filename);
  unsigned char * buf = new unsigned char[file->size()];
  file->read(buf);
  delete file;

  char itc = buf[2];

  width = buf[12] + buf[13] * 256;
  height = buf[14] + buf[15] * 256;
  int bpp = buf[16];
  int ps = 18 + buf[0];

  printf("%s: itc=%d, w=%d, h=%d, bpp=%d, ps=%d.\n",
	 filename, itc, width, height, bpp, ps);

  img = new unsigned int[width*height];

  switch (bpp)
    {
    case 24:
      for(int i=0; i<width*height; i++)
	{
	  int blue = (unsigned char) buf[ps+i*3];
	  int green =  (unsigned char) buf[ps+i*3+1];
	  int red =  (unsigned char) buf[ps+i*3+2];
#ifdef OSX	 
	  img[i]=(red<<24)+(green<<16)+(blue<<8)+0xff;
#else
	  img[i]=(0xff<<24)+(blue<<16)+(green<<8)+red;
#endif	 
	}
      break;

    case 32:
      for(int i=0; i<width*height; i++)
	{
	  int blue = (unsigned char) buf[ps+i*4];
	  int green =  (unsigned char) buf[ps+i*4+1];
	  int red =  (unsigned char) buf[ps+i*4+2];
	  int alpha = (unsigned char) buf[ps+i*4+3];
#ifdef OSX
	  img[i]=(red<<24) + (green<<16)+(blue<<8)+alpha;
#else
	  img[i]=(alpha<<24) + ((blue<<16)+(green<<8)+red);
	 
#endif
	}
      break;

    default:
      printf("ERROR: unsupported bpp %d.\n", bpp);
      exit(1);
    }

  delete [] buf;
}

TargaFile::~TargaFile()
{
  delete [] img;
}
