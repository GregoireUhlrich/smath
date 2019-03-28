VERSION=1.0
STATICLIBRARY=libsmath.out
STATICLIBRARY2=libsmath.a
DYNAMICLIBRARY=libsmath.so


CC=gcc -Wall -Wextra -Wno-return-type -std=c++11 -O2 -fPIC
CCDEBUG=$(CC) -g
 
# Les différents répertoires contenant respectivement les fichiers : Sources *.c, Headers *.h, Objets *.o, l'exécutable
SRCDIR=src
HEADDIR=include
OBJDIR=obj
BINDIR=bin
PROGDIR=prog
LIBDIR=lib
PROGOBJDIR=prog/obj
LIBLOCALPATH=$(HOME)/.local/lib
INCLUDELOCALPATH=$(HOME)/.local/include/smath
 
 
# Les différentes options de compilations, soyons strictes !
CFLAGS= -I$(HEADDIR) -lm -lstdc++ -lpthread
# Les différents FrameWorks et bibliothèques pour le linkage
#GLLIBS = -ltiff -framework OPENGL -framework GLUT -framework GLUI -lobjc -lstdc++ -lm
#SFML=-L/usr/share/doc/  -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-system-s -lfreetype -lX11 -lXrandr -lxcb -lxcb-randr -lxcb-image -lGL -lFLAC -logg -lvorbis -lvorbisenc -lvorbisfile -lopenal -lpthread -ludev
# L'exécutable
 
# Où trouver les différents sources *.c qu'il faudra compiler pour créer les objets correspondants
SRC= $(wildcard $(SRCDIR)/*.cpp)
PROG= $(wildcard $(PROGDIR)/*.cpp)
OBJ= $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o) 
OBJDEBUG= $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%_debug.o) 
	
BININTERMEDIATE=$(subst $(PROGDIR)/,,$(PROG))
BIN=$(subst .cpp,.x,$(BININTERMEDIATE))
BINDEBUG=$(subst .x,_debug.x,$(BIN))

transfert_lib: 
	cp $(LIBDIR)/* $(LIBLOCALPATH)
	cp $(HEADDIR)/* $(INCLUDELOCALPATH)/

smath: $(LIBDIR)/$(STATICLIBRARY) $(LIBDIR)/$(DYNAMICLIBRARY) transfert_lib

all:  $(BIN)

release: all
debug: $(BINDEBUG)

# Création des différents *.o à partir des *.cpp
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -o $@ -c $< $(CFLAGS)
$(PROGOBJDIR)/%.o: $(PROGDIR)/%.cpp
	$(CC) -o $@ -c $< $(CFLAGS)
$(LIBDIR)/$(STATICLIBRARY): $(OBJ)
	ar rcs $@ $(OBJ)
	mv $(LIBDIR)/$(STATICLIBRARY) $(LIBDIR)/$(STATICLIBRARY2)
$(LIBDIR)/$(DYNAMICLIBRARY): $(OBJ)
	$(CC) -shared -o $@ $(OBJ)


# Version avec deboggage gdb
$(OBJDIR)/%_debug.o: $(SRCDIR)/%.cpp
	$(CCDEBUG) -o $@ -c $< $(CFLAGS)
$(PROGOBJDIR)/%_debug.o: $(PROGDIR)/%.cpp
	$(CCDEBUG) -o $@ -c $< $(CFLAGS)
 
#Création de l'exécutable
%_debug.x: $(OBJDEBUG) $(PROGOBJDIR)/%_debug.o
	$(CCDEBUG) -o $(BINDIR)/$@ $^ $(CFLAGS)
%.x: $(OBJ) $(PROGOBJDIR)/%.o
	$(CC) -o $(BINDIR)/$@ $^ $(CFLAGS)

#app: $(OBJ) appli.cpp
#	$(CC) -o app $^ -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window -lsfml-audio

# Nettoyage des objets => Tout sera recompiler !
clean:
	rm $(OBJDIR)/*.o;
	rm $(PROGOBJDIR)/*.o;
	rm $(LIBDIR)/*

clean_debug:
	rm $(OBJDIR)/*_debug.o;
	r* $(PROGOBJDIR)/*_debug.o;
 
# Nettoyage complet => clean + effacement des executables
Clean:
	rm $(OBJDIR)/*.o;
	rm $(PROGOBJDIR)/*.o;
	rm $(BINDIR)/*;
	rm $(LIBDIR)/*
