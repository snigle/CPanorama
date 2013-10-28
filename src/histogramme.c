/*! \file  histogramme.c
	\author Poussou Elie poussoueli@eisti.eu
	\date Tue 22 Oct 2013
	
	\brief Permet d'avoir l'histogramme d'une image en niveaux de gris                                 
	

*/

/*
Pour chaque intensité, compter le nombre de pixels pour chaque intensité

tests sur si l'image est en images de gris et si 
l'image n'est pas nulle
*/
#include "histogramme.h"

int* remplirTableauHist(Image image, int* bool_erreur)
{
	int* TabHisto;
	int i;
	int j;
	int n;
	n=256;
	TabHisto = mallocBis(n * sizeof(int));
	if(testType(image, "P2"))
	{
		for(i=0; i<n ; i++)
		{
			TabHisto[i] = 0;
		}
	
		for(i = 0 ; i < image.height ; i++)
		{
			for (j = 0; j < image.width; j++)
			{
				TabHisto[image.teinte[i][j]]++;
			}
		}	
	}
	else
		*bool_erreur =1;
	return TabHisto;
}

int calculMax(int* tabhist)
{
	int max;
	int i;
	max=0;
	
	for(i=0 ; i<256 ; i++)
	{
		if(tabhist[i]>max)
			max=tabhist[i];
	}
	
	return(max);
}

int** Tracer(int* tabhist, int taille)
{
	int i;
	int j;
	int k;
	int max;
	int** trace;

	max=calculMax(tabhist)/500;
	trace=initMatrice(taille,max);
	
	for (i = 0; i < taille; i += 1)
	{
		for (j = 0; j < max; j += 1)
		{
			trace[j][i]=0;
		}
	}
	for(i=0 ; i<taille ; i++)
	{
		for(j=0; j<max ; j++)
		{
			if(j==tabhist[i])
			{
				for (k = max-1; k >= 0; k -= 1)
				{
					trace[k][i]=1;
				}
				
			}
		}
	}
	return(trace);
}

Image histogramme (char* input, char* output, int bool_save, int* bool_erreur)
{
	Image image;
	Image sortie;
	int* hist;
	int** trace;
	int max;
	image = chargerImage(input, bool_erreur);
	
	if(!*bool_erreur) hist=remplirTableauHist(image, bool_erreur);
	max=calculMax(hist);
	
	trace=Tracer(hist, 256);
	
	sortie = creationImage("P1",256,max/500, 0, trace);
	save(sortie,output,bool_erreur);

	libererImage(image);
	printf("Appel de la fonction histogramme\n");
	return sortie;
}
