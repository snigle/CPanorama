#Variables
dirsrc = src/
dirbin = bin/
dirsave = save/
dirdoc = doc/

CC = gcc -Wall
RM = rm -rf

SRC = $(wildcard $(dirsrc)*.c)
HEAD = $(filter main.o,$(SRC:.c=.h))
OBJ = $(subst $(dirsrc), $(dirbin), $(SRC:.c=.o))

AUTEUR = lamarche_ludovic
PROG = panorama

#Sous directory
DIR = $(shell find $(dirsrc) -maxdepth 5 -type d -print)

all: $(PROG)


$(PROG): $(dirbin) $(OBJ)
	$(CC) $(OBJ) -o $(dirbin)$@
	@echo "Compilation terminée"
$(dirbin) :
	@mkdir $(dirbin)
#$< est la premiere dependance
#$@ est la cible
$(dirbin)main.o: $(dirsrc)main.c
	$(CC) -c $< -o $@
$(dirbin)%.o: $(dirsrc)%.c $(dirsrc)%.h
	$(CC) -c $< -o $@


.PHONY: clean save restore test
clean:
	rm -f $(dirsrc)*~ $(dirsrc)\#*\# $(dirbin)*.o
	
#$(dirsave):
#	@mkdir $(dirsave)

save:
	mkdir save/
	@cp -r $(dirsrc)* $(dirsave)
	@echo "Sauvegarde effectuée dans le dossier "$(dirsave)
	
restore: $(dirsave) $(dirsrc)
	@rm -rf $(dirsrc)*
	@cp -r $(dirsave)* $(dirsrc)
	@echo "Restoration de la sauvegarde effectuée"

give: $(dirsrc)
	@rm -rf $(AUTEUR)
	@mkdir $(AUTEUR)
	@mkdir $(AUTEUR)/bin
	@mkdir $(AUTEUR)/save
	@mkdir $(AUTEUR)/doc
	@mkdir $(AUTEUR)/src
	@cp Makefile $(AUTEUR)/Makefile
	@cp -r $(dirsrc)* $(AUTEUR)/src/
	@cp -r $(dirdoc)* $(AUTEUR)/doc/
	tar cvzf $(AUTEUR)-$(PROG).tar.gz $(AUTEUR)/
	@rm -rf $(AUTEUR)
	@tar xvzf $(AUTEUR)-$(PROG).tar.gz
	make -C $(AUTEUR)
	./$(AUTEUR)/bin/$(PROG)
	
$(dirsrc):
	@mkdir $(dirsrc)
	
test:
	@echo "***********TEST normal grayScale****************"
	#./bin/panorama -i ./src/poivron.ppm -o ./src/poivron.pgm -g
	"***********TEST image déjà pgm grayScale****************"
	#./bin/panorama -i ./src/image_P2.pgm -o ./src/image_P3_rtg.pgm -g
	#./bin/panorama -i ./src/image_P1.pbm -o ./src/image_P3_rtg.pgm -g
	"***********TEST plusieurs images grayScale****************"
	./bin/panorama -li ./src/image_P3.ppm ./src/poivron.ppm -lo ./src/image_P3_rtg.pgm ./src/poivron_rtg.pgm -g
	"***********TEST image corrompue grayScale****************"
	./bin/panorama -i ./src/poivron_corrompu.ppm -o ./src/poivron_corrompu.pgm -g
	"***********TEST avec un répertoire grayScale****************"
	
	 #faire tout les cas possibles avec tout les cas d\images en input et output (images corrompues)
	 #P1 pbm, P2 pgm, P3 ppm
	

