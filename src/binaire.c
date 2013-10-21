/*! \file  binaire.c
	\author Poussou Elie poussoueli@eisti.eu
	\date Wed 16 Oct 2013
	
	\brief réalise la binarisation d'une image                                  
*/

#include "binaire.h"



int binaire(char* input, char* output, char* valeurDeBascule)
{
	Image image;
	Image sortie;	
	int** teinteBinaire;
	int i;
	int j;
	int seuil;
	seuil = atoi(valeurDeBascule);
	image=chargerImage(input);
	teinteBinaire=initMatrice(image.width,image.height);
	
	for(i = 0 ; i < image.height ; i++)
	{
		for (j = 0; j < image.width; j += 1)
		{
			if(image.teinte[i][j]> seuil)
				teinteBinaire[i][j]=0;
			else
				teinteBinaire[i][j]=1;
		}
	}	
	sortie = creationImage("P1",image.width,image.height, seuil, teinteBinaire);
	save(sortie, output);
	return 0;
}
