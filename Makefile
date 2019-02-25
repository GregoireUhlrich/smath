CC=gcc -Wall -Wextra -std=c++11 -O2 -g
 
# Les différents répertoires contenant respectivement les fichiers : Sources *.c, Headers *.h, Objets *.o, l'exécutable
SRCDIR=src
HEADDIR=include
LIBDIR=obj
BINDIR=bin
PROGDIR=prog
PROGLIBDIR=prog/obj
 
 
# Les différentes options de compilations, soyons strictes !
CFLAGS= -I$(HEADDIR) -lm -lstdc++ -lpthread
# Les différents FrameWorks et bibliothèques pour le linkage
#GLLIBS = -ltiff -framework OPENGL -framework GLUT -framework GLUI -lobjc -lstdc++ -lm
#SFML=-L/usr/share/doc/  -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-system-s -lfreetype -lX11 -lXrandr -lxcb -lxcb-randr -lxcb-image -lGL -lFLAC -logg -lvorbis -lvorbisenc -lvorbisfile -lopenal -lpthread -ludev
# L'exécutable
 
# Où trouver les différents sources *.c qu'il faudra compiler pour créer les objets correspondants
SRC= $(wildcard $(SRCDIR)/*.cpp)
PROG= $(wildcard $(PROGDIR)/*.cpp)
OBJ= $(SRC:$(SRCDIR)/%.cpp=$(LIBDIR)/%.o) 
	
BIN=diagnostic.x pi.x old.x
all: $(BIN)
 
# Création des différents *.o à partir des *.cpp
$(LIBDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -o $@ -c $< $(CFLAGS)
$(PROGLIBDIR)/%.o: $(PROGDIR)/%.cpp
	$(CC) -o $@ -c $< $(CFLAGS)
 
#Création de l'exécutable
diagnostic.x: $(OBJ) $(PROGLIBDIR)/diagnostic.o
	$(CC) -o $(BINDIR)/$@ $^ $(CFLAGS)
old.x: $(OBJ) $(PROGLIBDIR)/old.o
	$(CC) -o $(BINDIR)/$@ $^ $(CFLAGS)
pi.x: $(OBJ) $(PROGLIBDIR)/pi.o
	$(CC) -o $(BINDIR)/$@ $^ $(CFLAGS)

app: $(OBJ) appli.cpp
	$(CC) -o app $^ -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window -lsfml-audio

# Nettoyage des objets => Tout sera recompiler !
clean:
	rm $(LIBDIR)/*.o
	rm $(PROGLIBDIR)/*.o
 
# Nettoyage complet => clean + effacement du l'exécutable
Clean: clean
	rm $(BINDIR)/*
