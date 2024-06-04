CFLAGS=-Wall

ifeq ($(shell uname),Linux)
	LINUX=1
	CFLAGS+= -DLINUX
	LIBS=-lglut -lGLU -lGL -L/usr/X11R6/lib
endif

ifneq ($(shell uname|grep CYGWIN),)
	WINDOWS=1
	NO_CYGWIN=1
	CFLAGS+= -DWINDOWS -DHAVE_OPENAL -Iwin32/openal/include -I../win32/openal/include
	LIBS= -lglu32 -lopengl32 -lglut32 -Lwin32/openal/lib -lalut -lopenal32
	ifeq ($(NO_CYGWIN),1)
		CFLAGS+= -mno-cygwin -DNO_CYGWIN
		LIBS+= -mno-cygwin
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
	g++ $(CFLAGS) -o $*.o -c $*.cc


