#include "histogramme.h"

int* remplirTableauHist(Image im_image, int* int_bool_erreur)
{
	int* int_TabHisto;
	int int_i;
	int int_j;
	int_TabHisto = mallocBis((im_image.teinteMax+1) * sizeof(int));
	if(testType(im_image, "P2"))
	{
		for (int_i=0; int_i <( im_image.teinteMax+1);int_i++)
		{
			int_TabHisto[int_i]=0;
		}
		
		for(int_i = 0 ; int_i < im_image.height ; int_i++)
		{
			for (int_j = 0; int_j < im_image.width; int_j++)
			{
				int_TabHisto[im_image.teinte[int_i][int_j]]++;
			}
		}	
	}
	else
		*int_bool_erreur = 1;
	return (int_TabHisto);
}

int calculMax(int* int_tabhist, int int_teinteMax)
{
	int int_max;
	int int_i;
	int_max=0;
	
	for(int_i=0 ; int_i<int_teinteMax+1 ; int_i++)
	{
		if(int_tabhist[int_i]>int_max)
			int_max=int_tabhist[int_i];
	}
	
	return(int_max);
}

int* tabPourcent(int* int_hist, int int_max, int int_taille, int int_teinteMax)
{
	int* int_tabPourcent;
	int int_i;
	
	int_tabPourcent=mallocBis((int_teinteMax+1)*sizeof(int));
	
	for(int_i=0;int_i<(int_teinteMax+1);int_i++)
	{
		int_tabPourcent[int_i]= int_max==0? 0 : int_taille*int_hist[int_i]/int_max;
	}
	
	return(int_tabPourcent);
}


int** Tracer(int* int_tabhist, int int_taille, int int_teinteMax)
{
	int int_i;
	int int_j;
	int int_k;
	int** int_trace;

	int_trace=initMatrice(int_teinteMax+1,int_taille);
	
	for (int_i = 0; int_i < int_teinteMax+1; int_i += 1)
	{
		for (int_j = 0; int_j < int_taille; int_j += 1)
		{
			int_trace[int_j][int_i]=0;
		}
	}
	for(int_i=0 ; int_i < int_teinteMax+1 ; int_i++)
	{
		for (int_k = (int_taille - int_tabhist[int_i]) ; int_k < int_taille ; int_k += 1)
		{
			int_trace[int_k][int_i]=1;
		}	
	}
	return(int_trace);
}



void remplirNouvellesTeintes (Image image, int decalage)
{
	int i;
	int j;
	for (i = 0; i < image.height; i += 1)
	{
		for (j = 0; j < image.width; j += 1)
		{
			image.teinte[i][j] = image.teinte[i][j] - decalage;
			if ( image.teinte[i][j] < 0)
				 image.teinte[i][j] = 0;
			else if ( image.teinte[i][j]>255)
				 image.teinte[i][j] = 255;
		}
	}
}

int calculMediane(int iterationMediane,int* histogramme)
{
	int i;
	i = 0;
	while (iterationMediane > 0)
	{
		iterationMediane -= histogramme[i];
		i++;
	}
	return(i);
}

int calculDecalage(Image im_image1, Image im_image2, int* m1supm2, int* int_bool_erreur)
{
	int i;
	int j;
	i = calculMediane(im_image1.width * im_image1.height / 2, remplirTableauHist(im_image1, int_bool_erreur));
	j = calculMediane(im_image2.width * im_image2.height / 2, remplirTableauHist(im_image2, int_bool_erreur));
	if (i>j)
		*m1supm2 = 1;
	else
		*m1supm2 = -1;
	if (!i)
	{
		if (!j)
			return (0);
		else
			return ((j - 1)/2);
	}else if (!j)
			return ((i - 1)/2);
		else
			return ((j + i - 2)/2 - (i<=j?i:j));
}


Image histogrammeBis(char* char_str_input, char* char_str_output, int int_bool_save, int* int_bool_erreur, int* int_hist, Image im_image)
{
	int** int_trace;
	int* int_percent;
	int int_max;
	Image im_sortie;
	int_max = 0;
	int_max = calculMax(int_hist, im_image.teinteMax);
	int_percent = tabPourcent(int_hist, int_max, 500, im_image.teinteMax);
	int_trace = Tracer(int_percent, 500, im_image.teinteMax);
	im_sortie = creationImage("P1", im_image.teinteMax, 500, 0, int_trace);
	if (int_bool_save)
		save(im_sortie, char_str_output, int_bool_erreur);
	printf("\t L'histogramme de l'image %s a été effectuée avec succés. Il est tracé dans le fichier %s \n", char_str_input, char_str_output);
	return (im_sortie);
}


Image histogramme (char* char_str_input, char* char_str_output, int int_bool_save, int* int_bool_erreur)
{
	Image im_image;
	Image im_sortie;
	int* int_hist;
	printf("**%s -h %s**\n", char_str_input, char_str_output);
	im_image = chargerImage(char_str_input, int_bool_erreur);
	if(!*int_bool_erreur)
	{
		int_hist = remplirTableauHist(im_image, int_bool_erreur);
		if (!*int_bool_erreur)
		{
			im_sortie = histogrammeBis(char_str_input, char_str_output, int_bool_save, int_bool_erreur, int_hist, im_image);
			libererImage(im_image);
			free(int_hist);
		}
	}
	return (im_sortie);
}


