/*! \file  binaire.c
	\author Poussou Elie poussoueli@eisti.eu
	\date Wed 16 Oct 2013
	
	\brief réalise la binarisation d'une image                                  
*/

#include "binaire.h"



int binaire(char* input, char* output, int seuil)
{
	Image image;
	image=chargerImage(input);
	
	int** teinteBinaire;
	teinteBinaire=initMatrice(image.width,image.height);
	
	int i;
	int j;
	for(i = 0 ; i < image.height ; i++)
	{
		for (j = 0; j < image.width; j += 1)
		{
			if(image.teinte[i][j]> seuil)
				teinteBinaire[i][j]=1;
			else
				teinteBinaire[i][j]=0;
		}
	}	
	
	Image sortie;
	sortie=creationImage("P1",image.width,image.height, seuil, teinteBinaire);
	
	printf("Appel de la fonction binaire avec le seuil %s\n",seuil);
	save(sortie, output);
	return 0;
}

