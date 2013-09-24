#commandes
CC = gcc -Wall
CP = rsync -arv
RM = rm -rf
#varaibles de localisation
SRCDIR = ./src/
BINDIR = ./bin/
DOCDIR = ./doc/
SAVDIR = ./save/
#recupération des fichiers
SRC = $(wildcard $(SRCDIR)*.c)
OBJ = $(subst $(SRCDIR),$(BINDIR),$(SRC:.c=.o))
HEAD = $(filter main.h,$(SRC:.c=.o))
PROG = panorama


all : $(PROG) 
#on compile chaque objet .o en toto
$(PROG) : $(OBJ)
	$(CC) $^ -o $@
	mv ./$(PROG) ./bin

#on compile le main ayant déja compilé les fichiers secondaires et les bibliothèques
./bin/main.o : ./src/main.c
	$(CC) -c ./src/main.c -o ./bin/main.o
#on compile chaque fichier .c avec son .h correspondant
./bin/%.o : ./src/%.c ./src/%.h
	$(CC) -c $< -o $@
#on force le clean
.PHONY : clean save

#on detruit tout les fichiers objets, les feedback et le programme compilé. Seuls les fichiers nécessaires a la compilation sont conservés
clean :
	$(RM) ./src/*.o ./src/*~ ./bin/$(PROG)

#on conserve un fichier de sauvegarde pour les plantages
save :
	$(CP) ./src/* ./save/
	
#on remet les fichiers sauvegardé dans le répertoire source
restore :
	$(CP) ./save/* ./src/
