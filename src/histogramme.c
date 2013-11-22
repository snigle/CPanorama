/*! \file  histogramme.c
	\author Poussou Elie poussoueli@eisti.eu
	\date Tue 22 Oct 2013
	
	\brief Permet d'avoir l'histogramme d'une image en niveaux de gris                                 
	

*/
#include "histogramme.h"

int* remplirTableauHist(Image image, int* bool_erreur)
{
	int* TabHisto;
	int i;
	int j;
	TabHisto = mallocBis((image.teinteMax+1) * sizeof(int));
	if(testType(image, "P2"))
	{
		for (i=0; i <( image.teinteMax+1);i++)
		{
			TabHisto[i]=0;
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
		*bool_erreur = 1;
	return (TabHisto);
}

int calculMax(int* tabhist, int teinteMax)
{
	int max;
	int i;
	max=0;
	
	for(i=0 ; i<teinteMax+1 ; i++)
	{
		if(tabhist[i]>max)
			max=tabhist[i];
	}
	
	return(max);
}

int* tabPourcent(int* hist, int max, int taille, int teinteMax)
{
	int* tabPourcent;
	int i;
	
	tabPourcent=mallocBis((teinteMax+1)*sizeof(int));
	
	for(i=0;i<(teinteMax+1);i++)
	{
		tabPourcent[i]= max==0? 0 : taille*hist[i]/max;
	}
	
	return(tabPourcent);
}


int** Tracer(int* tabhist, int taille, int teinteMax)
{
	int i;
	int j;
	int k;
	int** trace;

	trace=initMatrice(teinteMax+1,taille);
	
	for (i = 0; i < teinteMax+1; i += 1)
	{
		for (j = 0; j < taille; j += 1)
		{
			trace[j][i]=0;
		}
	}
	for(i=0 ; i < teinteMax+1 ; i++)
	{
		for (k = (taille - tabhist[i]) ; k < taille ; k += 1)
		{
			trace[k][i]=1;
		}	
	}
	return(trace);
}

Image histogrammeBis(char* str_input, char* str_output, int bool_save, int* bool_erreur, int* hist, Image image)
{
	int** trace;
	int* percent;
	int max;
	Image sortie;
	max = 0;
	max = calculMax(hist, image.teinteMax);
	percent = tabPourcent(hist, max, 500, image.teinteMax);
	trace = Tracer(percent, 500, image.teinteMax);
	sortie = creationImage("P1", image.teinteMax, 500, 0, trace);
	if (bool_save)
		save(sortie, str_output, bool_erreur);
	printf("\t L'histogramme de l'image %s a été effectuée avec succés. Il est tracé dans le fichier %s \n", str_input, str_output);
	return (sortie);
}


Image histogramme (char* str_input, char* str_output, int bool_save, int* bool_erreur)
{
	Image image;
	Image sortie;
	int* hist;
	printf("**%s -h %s**\n", str_input, str_output);
	image = chargerImage(str_input, bool_erreur);
	if(!*bool_erreur)
	{
		hist = remplirTableauHist(image, bool_erreur);
		if (!*bool_erreur)
		{
			sortie = histogrammeBis(str_input, str_output, bool_save, bool_erreur, hist, image);
			libererImage(image);
			free(hist);
		}
	}
	return (sortie);

}
