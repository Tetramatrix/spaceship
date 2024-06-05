OBJECTS=\
engine\
spaceship\
sound\
shot\
sprite\
explosion\


include ../Config.mak

THISLIB=engine.lib

$(THISLIB): $(OFILES)
	ar rcs $(THISLIB) $(OFILES)

clean:
	rm -f *~ *.o $(THISLIB)
	chmod 600 $(CFILES) $(HFILES) Makefile allincludes.h
