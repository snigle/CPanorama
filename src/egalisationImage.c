#include "egalisationImage.h"


int getMax (int** tab, int int_longueur, int int_largeur)
{
	int resultat;
	int i;
	int j;
	resultat = tab[0][0];
	for (i = 0; i < int_largeur; i += 1)
	{
		for (j = 0; j < int_longueur; j += 1)
		{
			if (tab[i][j] > resultat)
				resultat = tab[i][j];
		}
	}
	return (resultat);
}

int getMin (int** tab, int int_longueur, int int_largeur)
{
	int resultat;
	int i;
	int j;
	resultat = tab[0][0];
	for (i = 0; i < int_largeur; i += 1)
	{
		for (j = 0; j < int_longueur; j += 1)
		{
			if (tab[i][j] < resultat)
				resultat = tab[i][j];
		}
	}
	return (resultat);
}





/*int** egalisation (int** teinte, int int_longueur, int int_largeur)*/
/*{*/
/*	int int_max;*/
/*	int int_min;*/
/*	int** newTeinte;*/
/*	int i;*/
/*	int j;*/
/*	int_max = getMax (teinte, int_longueur, int_largeur);*/
/*	int_min = getMin (teinte, int_longueur, int_largeur);*/
/*	newTeinte = initMatrice(0,int_longueur, int_largeur);*/
/*	if (int_max > int_min)*/
/*	{*/
/*		for (i = 0; i < int_largeur; i += 1)*/
/*		{*/
/*			for (j = 0; j < int_longueur; j += 1)*/
/*			{*/
/*				newTeinte[i][j] = ((teinte[i][j] - int_min) * 255) / (int_max - int_min);*/
/*			}*/
/*		}*/
/*		return (newTeinte);*/
/*	}else*/
/*		return (teinte);*/
/*}*/

/*void decalerImages (Image im_image1, Image im_image2, int** newTeinte1, int** newTeinte2, int decalage)*/
/*{*/
/*	int i;*/
/*	int j;*/
/*	for (i = 0; i < im_image1.height; i += 1)*/
/*	{*/
/*		for (j = 0; j < im_image2.width; j += 1)*/
/*		{*/
/*			if ((im_image1.teinte[i][j] - decalage) > 0)*/
/*				newTeinte1[i][j] = im_image1.teinte[i][j] - decalage;*/
/*			else*/
/*				newTeinte1[i][j] = 0;*/
/*		}*/
/*	}*/
/*	for (i = 0; i < im_image1.height; i += 1)*/
/*	{*/
/*		for (j = 0; j < im_image2.width; j += 1)*/
/*		{*/
/*			if ((im_image2.teinte[i][j] - decalage) < 256)*/
/*				newTeinte2[i][j] = im_image2.teinte[i][j] + decalage;*/
/*			else*/
/*				newTeinte2[i][j] = 255;*/
/*		}*/
/*	}*/
/*}*/


/*void egalisation(Image im_image1,Image im_image2, int** newTeinte1, int** newTeinte2, int* int_bool_erreur)*/
/*{*/
/*	int iterationMediane1;*/
/*	int iterationMediane2;*/
/*	int* hist1;*/
/*	int* hist2;*/
/*	int mediane1;*/
/*	int mediane2;*/
/*	int i;*/
/*	int j;*/
/*	i = 0;*/
/*	j = 0;*/
/*	*/
/*	*/
/*	hist1 = remplirTableauHist(im_image1, int_bool_erreur);*/
/*	hist2 = remplirTableauHist(im_image2, int_bool_erreur);*/
/*	*/
/*	*/
/*	iterationMediane1 = im_image1.width * im_image1.height / 2;*/
/*	iterationMediane2 = im_image2.width * im_image2.height / 2;*/
/*	*/
/*	while (iterationMediane1 > 0)*/
/*	{*/
/*		iterationMediane1 -= hist1[i];*/
/*		i++;*/
/*	}*/
/*	mediane1 = hist1[i-1];*/
/*	while (iterationMediane1 > 0)*/
/*	{*/
/*		iterationMediane2 -= hist2[i];*/
/*		j++;*/
/*	}*/
/*	mediane2 = hist2[i-1];*/
/*	*/
/*	if (mediane1 > mediane2)*/
/*		decalerImages(im_image1, im_image2, newTeinte1, newTeinte2, (mediane1 - mediane2)/2);*/
/*	else if (mediane2 > mediane2)*/
/*		decalerImages(im_image1, im_image2, newTeinte1, newTeinte2, (mediane2 - mediane1)/2);*/
/*}*/

/*Image egaliserHistogramme (char* char_str_input, char* char_str_output, int int_bool_save, int* int_bool_erreur)
{
	Image im_image1;
	Image im_image2;
	Image im_sortie1;
	Image im_sortie2;
	int** newTeinte1;
	int** newTeinte2;

	im_image1 = chargerImage(char_str_input[0], int_bool_erreur);
	im_image2 = chargerImage(char_str_input[1], int_bool_erreur);
	
	newTeinte1 = initMatrice(0,im_image1.width, im_image1.height);
	newTeinte2 = initMatrice(0,im_image2.width, im_image2.height);
	
	if(!*int_bool_erreur)
	{
		newTeinte = egalisation(im_image1, im_image2, newTeinte1, newTeinte2, int_bool_erreur);
		im_sortie = creationImage("P2", im_image.width, im_image.height, im_image.teinteMax, newTeinte);
		libererImage(im_image);
		if (int_bool_save)	
			save(im_sortie, char_str_output, int_bool_erreur);
	}
	return (im_sortie);
}*/
