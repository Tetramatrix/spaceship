CFLAGS=-Wall

CC=i686-w64-mingw32-g++
ar=i686-w64-mingw32-ar

#CC=g++
#ar=ar

ifeq ($(shell uname),Linux)
	LINUX=1
	CFLAGS+= -DLINUX
	LIBS=-lglut -lGLU -lGL -L/usr/X11R6/lib
endif

ifneq ($(shell uname|grep CYGWIN),)
	WINDOWS=1
	NO_CYGWIN=1
	CFLAGS+= -m32 -DWINDOWS -D_WIN32 -DGLUT_DISABLE_ATEXIT_HACK -DHAVE_OPENAL -Iwin32/openal/include -I../win32/openal/include 
#	LIBS+= -L/usr/i686-w64-mingw32/sys-root/mingw/lib/../lib -lglu32 -lglut32 -lopengl32 -lglu32 -lglut32 -lopengl32  -lGL -lglut -lGLU  -Lwin32/openal/lib -lalut -lopenal32 -Wl,--verbose
# LIBS+= -lGL -lglut32 -lGLU -lGL -lglut32 -lGLU -Lwin32/openal/lib -lalut -lopenal32 -Wl,--verbose
   LIBS+= -L/usr/i686-w64-mingw32/sys-root/mingw/lib/../lib -lglu32 -lglut32 -lopengl32 -lglu32 -lglut32 -lopengl32  -Lwin32/openal/lib -lalut -lopenal32 -Wl,--verbose -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic
	ifeq ($(NO_CYGWIN),1)
		CFLAGS+= -DNO_CYGWIN
		LIBS+= 
	endif
endif

ifeq ($(shell uname),Darwin)
	OSX=1
	CFLAGS+= -DOSX -I/System/Library/Frameworks/GLUT.framework/Headers
	LIBS=-framework OpenGL -framework GLUT -lobjc
endif

CFILES=$(addsuffix .cc, $(OBJECTS))
OFILES=$(addsuffix .o, $(OBJECTS))
HFILES=$(addsuffix .h, $(OBJECTS))

%.o: %.cc $(HFILES) allincludes.h
	$(CC) $(CFLAGS) -o $*.o -c $*.cc

