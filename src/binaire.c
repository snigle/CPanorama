/*! \file  binaire.c
	\author Poussou Elie poussoueli@eisti.eu
	\date Wed 16 Oct 2013
	
	\brief réalise la binarisation d'une image                                  
*/

#include "binaire.h"

int** remplirMatriceBinaire (Image image, int seuil)
{
	int** teinteBinaire;
	int i;
	int j;
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
	
	return teinteBinaire;
}

Image binaire(char* input, char* output, char* valeurDeBascule, int bool_save, int* bool_erreur)
{
	Image image;
	Image sortie;	
	int** teinteBinaire;
	int seuil;
	printf("**%s -b %s**\n",input,output);
	seuil = atoi(valeurDeBascule);
	image=chargerImage(input,bool_erreur);
	if(testType(image, "P2") && !*bool_erreur)
	{
		teinteBinaire = remplirMatriceBinaire(image, seuil);
		sortie = creationImage("P1",image.width,image.height, seuil, teinteBinaire);
		if(bool_save)
		{
			save(sortie, output, bool_erreur);
			if(!*bool_erreur) printf("\tLa conversion en noir et blanc du fichier %s a été effectuée avec succés. Le fichier de sortie est : %s \n", input, output);
		}
		
	}
	else
		*bool_erreur = 1;

	libererImage(image);
	return sortie;
}
