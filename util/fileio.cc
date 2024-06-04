#include "allincludes.h"

File::File(char * filename)
{
  this->filename = strdup(filename);
}

File::~File()
{
  free(filename);
}

#ifdef NO_CYGWIN

#include <windows.h>

int File::size()
{
  HANDLE h = CreateFile(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL, NULL);

  DWORD size = GetFileSize(h, NULL);

  CloseHandle(h);

  return size;
}

void File::read(void * buf)
{
  HANDLE h = CreateFile(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL, NULL);

  DWORD size = GetFileSize(h, NULL);
  DWORD foobar;

  ReadFile(h, buf, size, &foobar, NULL);

  CloseHandle(h);
}

void File::write(void * buf, int bufSize)
{
  HANDLE h = CreateFile(filename, GENERIC_WRITE, 0, NULL, OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL, NULL);

  
  DWORD size = bufSize;
  DWORD foobar;

  WriteFile(h, buf, size, &foobar, NULL);

  CloseHandle(h);
}

#else

#include <sys/types.h>
#include <sys/stat.h>

int File::size()
{
  struct stat statBuf;

  if (stat(filename, &statBuf) < 0)
    return -1;

  return statBuf.st_size;
}

void File::read(void * buf)
{
  FILE * file = fopen(filename, "r");
  if (file == NULL)
    {
      printf("Could not open '%s'\n", filename);
      exit(1);
    }

  int s = size();

  fread(buf, 1, s, file);
  fclose(file);

  printf("Read '%s', size %d.\n", filename, s);
}
#endif
