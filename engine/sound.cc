/* $Id: sound.cc,v 1.2 2005/02/10 15:58:02 dude Exp $ */

#include "allincludes.h"

#ifdef HAVE_OPENAL

OpenALSound::OpenALSound()
{
  printf("Initializing OpenAL...\n");

  alutInit(0, NULL);
  alGetError();

  alGenBuffers(NUM_BUFFERS, buffers);
  checkError();

  alGenSources(NUM_SOURCES, sources);

  checkError();

  alDistanceModel(AL_INVERSE_DISTANCE);
  //alDistanceModel(AL_NONE);
}

void OpenALSound::setListener(float * pos, float * vel,
			      float * ola,
			      float * oup)
{
  alListenerfv(AL_POSITION, pos);
  alListenerfv(AL_VELOCITY, vel);
  float orientation[] = {ola[0], ola[1], ola[2], oup[0], oup[1], oup[2]};
  alListenerfv(AL_ORIENTATION, orientation);
}

void OpenALSound::play(int slot, float * pos, float rf)
{
  static int nr = 0;
  nr ++;
  nr %= NUM_DYNAMIC_SOURCES;

  ALuint s = sources[DYNSOURCE_RANGE_START+nr];

  if (!alIsSource(s))
    printf("source %d not valid\n", s);

  alSourceStop(s);
  
  alSourcefv(s, AL_POSITION, pos);
  alSourcei(s, AL_BUFFER, buffers[slot]);
  alSourcef(s, AL_ROLLOFF_FACTOR, rf);
  alSourcePlay(s);
}

void OpenALSound::playStatic(int srcnum,
			     int slot,
			     bool loop,
			     float pitch)
{

  ALuint s = sources[srcnum];
  alSourcei(s, AL_BUFFER, buffers[slot]);
  alSourcei(s, AL_LOOPING, loop?AL_TRUE:AL_FALSE);
  alSourcef(s, AL_PITCH, pitch);
  alSourcef(s, AL_ROLLOFF_FACTOR, 0.1);
  alSourcePlay(s);
}

void OpenALSound::setSourcePos(int srcnum, float * pos)
{
  ALuint s = sources[srcnum];
  alSourcefv(s, AL_POSITION, pos);
}

void OpenALSound::setPitch(int srcnum, float pitch)
{
  ALuint s = sources[srcnum];
  alSourcef(s, AL_PITCH, pitch);
}

void OpenALSound::loadWav(int slot, char * filename)
{
  printf("[%d]: %s ", buffers[slot], filename);

  ALenum format;
  void * data = (void*) 0xDEADFACE;
  ALsizei size, freq;
  ALboolean loop;

  alutLoadWAVFile((ALbyte*)filename,&format,&data,&size,&freq,&loop);
  checkError();

  printf("data*=%p, size=%d, freq=%d\n",
	 data, size, freq);

  alBufferData(buffers[slot], format, data, size, freq);
  checkError();

  alutUnloadWAV(format, data, size, freq);
  checkError();
}
void OpenALSound::stopPlay(int srcnum)
{
    alSourceStop(sources[srcnum]);
}

void OpenALSound::checkError()
{
  int error = alGetError();
  if (error == AL_NO_ERROR)
    return;
  printf("AL ERROR: %d ", error);
  switch (error)
    {
    case AL_INVALID_NAME:
      printf("INVALID_NAME.\n");
      break;
    case AL_INVALID_ENUM:
      printf("INVALID_ENUM.\n");
      break;
    case AL_INVALID_VALUE:
      printf("INVALID_VALUE.\n");
      break;
    case AL_INVALID_OPERATION:
      printf("INVALID_OPERATION.\n");
      break;
    case AL_OUT_OF_MEMORY:
      printf("OUT_OF_MEMORY.\n");
      break;
    default:
      printf("UNKNOWN ERROR.\n");
    }
  exit(1);
}

#endif
