OBJECTS=\
targa\
fileio\
atarifnt\
fastmath\
logo\
util\
farbbalken\
farbpfeile\
highscore\


include ../Config.mak

THISLIB=util.lib

$(THISLIB): $(OFILES)
	ar rcs $(THISLIB) $(OFILES)

clean:
	rm -f *~ *.o $(THISLIB)
	chmod 600 $(CFILES) $(HFILES) Makefile allincludes.h
