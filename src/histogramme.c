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
	TabHisto = mallocBis(image.teinteMax * sizeof(int));
	if(testType(image, "P2"))
	{
		for (i=0; i<image.teinteMax;i++)
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
		*bool_erreur =1;
	return TabHisto;
}

int calculMax(int* tabhist, int teinteMax)
{
	int max;
	int i;
	max=0;
	
	for(i=0 ; i<teinteMax ; i++)
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
	
	
	tabPourcent=mallocBis(max*sizeof(int));
	for(i=0;i<teinteMax;i++)
	{
		
		tabPourcent[i]=taille*hist[i]/max;
	}
	
	return(tabPourcent);
}


int** Tracer(int* tabhist, int taille, int teinteMax)
{
	int i;
	int j;
	int k;
	int** trace;

	trace=initMatrice(teinteMax,taille);
	
	for (i = 0; i < teinteMax; i += 1)
	{
		for (j = 0; j < taille; j += 1)
		{
			trace[j][i]=0;
		}
	}
	for(i=0 ; i<teinteMax ; i++)
	{
		for (k = taille - tabhist[i] ; k < taille ; k += 1)
		{
			trace[k][i]=1;
		}	
	}return(trace);
}

Image histogramme (char* input, char* output, int bool_save, int* bool_erreur)
{
	Image image;
	Image sortie;
	int* hist;
	int** trace;
	int* percent;
	int max;
	int i;
	
	image = chargerImage(input, bool_erreur);
	if(!*bool_erreur) hist=remplirTableauHist(image, bool_erreur);
	
	max=calculMax(hist, image.teinteMax);
	percent=tabPourcent(hist,max, 500, image.teinteMax);
	trace=Tracer(percent, 500, image.teinteMax);
	sortie = creationImage("P1",image.teinteMax,500, 0, trace);

	save(sortie,output,bool_erreur);
	libererImage(image);
	free(hist);
	for(i=1;i<image.teinteMax+1;i++)
	{printf("Appel de la fonction histogramme\n,%d-%d, \n", i, sortie.teinte[i]);}
	return sortie;
}
