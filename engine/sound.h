/* $Id: sound.h,v 1.2 2005/02/10 15:58:02 dude Exp $ */

#ifndef SOUND_H
#define SOUND_H

#define NUM_BUFFERS 38

#define NUM_STATIC_SOURCES 6
#define NUM_DYNAMIC_SOURCES 32
#define NUM_SOURCES (NUM_STATIC_SOURCES+NUM_DYNAMIC_SOURCES)
#define DYNSOURCE_RANGE_START NUM_STATIC_SOURCES
#define DYNSOURCE_RANGE_END NUM_SOURCES

class Sound
{ public:

  Sound() {}
  virtual void loadWav(int slot, char * filename) {}
  virtual void setListener(float * pos, float * vel,
			   float * orientationLookAt,
			   float * orientationUp) {}
  virtual void play(int slot, float * pos, float rf) {}

  virtual void playStatic(int srcnum,
			  int slot,
			  bool loop,
			  float pitch) {}

  virtual void setSourcePos(int srcnum, float * pos) {}
  virtual void setPitch(int srcnum, float pitch) {}
  virtual void stopPlay(int srcnum) {}

};

#ifdef HAVE_OPENAL

class OpenALSound : public Sound
{ public:

  ALint	error;
  ALuint buffers[NUM_BUFFERS];
  ALuint sources[NUM_SOURCES];

  OpenALSound();

  void loadWav(int slot, char * filename);

  void setListener(float * pos, float * vel,
		   float * orientationLookAt,
		   float * orientationUp);

  void play(int slot, float * pos, float rf);

  void checkError();

  void playStatic(int srcnum,
		  int slot,
		  bool loop,
		  float pitch);
  
  void setSourcePos(int srcnum, float * pos);
  void setPitch(int srcnum, float pitch);
  void stopPlay(int srcnum);
};


#endif

#endif
