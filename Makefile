#Variables
dirsrc = src/
dirbin = bin/
dirsave = save/
dirdoc = doc/
dirrapport = rapport/

CC = gcc -pg -Wall -pedantic -Wmissing-prototypes -Wunused-variable
RM = rm -rf

SRC = $(wildcard $(dirsrc)*.c)
HEAD = $(filter main.o,$(SRC:.c=.h))
OBJ = $(subst $(dirsrc), $(dirbin), $(SRC:.c=.o))

AUTEUR = lamarche-perales-poussou
PROG = panorama

#Sous directory
DIR = $(shell find $(dirsrc) -maxdepth 5 -type d -print)

all: $(PROG)


$(PROG): $(dirbin) $(OBJ) 
	$(CC) $(OBJ) -o $(dirbin)$@ -lm
	@echo "Compilation terminée"
$(dirbin) :
	@mkdir $(dirbin)
#$< est la premiere dependance
#$@ est la cible
$(dirbin)main.o: $(dirsrc)main.c
	$(CC) -c $< -o $@
$(dirbin)%.o: $(dirsrc)%.c $(dirsrc)%.h
	$(CC) -c $< -o $@


.PHONY: clean save restore test doc
clean:
	rm -f $(dirsrc)*~ $(dirsrc)\#*\# $(dirbin)*.o
	
#$(dirsave):
#	@mkdir $(dirsave)

save:
	@cp -r $(dirsrc)* $(dirsave)
	@echo "Sauvegarde effectuée dans le dossier "$(dirsave)
	
restore: $(dirsave) $(dirsrc)
	@rm -rf $(dirsrc)*
	@cp -r $(dirsave)* $(dirsrc)
	@echo "Restoration de la sauvegarde effectuée"

doc:
	doxygen Doxyfile

give: $(dirsrc)
	@rm -rf $(AUTEUR)
	@mkdir $(AUTEUR)
	@mkdir $(AUTEUR)/$(dirsrc)
	@mkdir $(AUTEUR)/$(dirbin)
	@mkdir $(AUTEUR)/$(dirrapport)
	@cp Makefile $(AUTEUR)/Makefile
	@cp Doxyfile $(AUTEUR)/Doxyfile
	@cp README $(AUTEUR)/README
	@cp -r $(dirsrc)* $(AUTEUR)/$(dirsrc)
	@cp -r $(dirrapport)rapport.pdf $(AUTEUR)/$(dirrapport)
	tar cvzf $(AUTEUR)-$(PROG).tar.gz $(AUTEUR)/
	@rm -rf $(AUTEUR)
	@tar xvzf $(AUTEUR)-$(PROG).tar.gz
	make -C $(AUTEUR)
	./$(AUTEUR)/$(dirbin)$(PROG) --help
	
$(dirsrc):
	@mkdir $(dirsrc)
	
.IGNORE: test dilate erode binaire convolution grayscale histogramme enregistrer

test: dilate erode binaire convolution grayscale histogramme enregistrer
	@echo "**************Test de toutes les options***********"
	
dilate:
	@echo "************TEST Dilate*********"
	./bin/panorama -r src/images/ -d

erode:
	@echo "************TEST Erode**********"
	./bin/panorama -r src/images/ -e
	
binaire:
	@echo "************TEST Binaire**********"
	./bin/panorama -r src/images/ -b 150
convolution:
	@echo "************TEST Convolution**********"
	./bin/panorama -r src/images/ -c src/filtre.txt
grayscale:
	@echo "************TEST Grayscale**********"
	./bin/panorama -r src/images/ -g
histogramme:
	@echo "************TEST Histogramme**********"
	./bin/panorama -r src/images/ -h
enregistrer:
	@echo "************TEST Enregistrer**********"
	./bin/panorama -r src/images/
