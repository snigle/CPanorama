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





int** egalisation (int** teinte, int int_longueur, int int_largeur)
{
	int int_max;
	int int_min;
	int** newTeinte;
	int i;
	int j;
	int_max = getMax (teinte, int_longueur, int_largeur);
	int_min = getMin (teinte, int_longueur, int_largeur);
	newTeinte = initMatrice(int_longueur, int_largeur);
	if (int_max > int_min)
	{
		for (i = 0; i < int_largeur; i += 1)
		{
			for (j = 0; j < int_longueur; j += 1)
			{
				newTeinte[i][j] = ((teinte[i][j] - int_min) * 255) / (int_max - int_min);
			}
		}
		return (newTeinte);
	}else
		return (teinte);
}

Image egaliserHistogramme (char* char_str_input, char* char_str_output, int int_bool_save, int* int_bool_erreur)
{
	Image im_image;
	Image im_sortie;
	int** newTeinte;

	printf("**%s -h %s**\n", char_str_input, char_str_output);
	im_image = chargerImage(char_str_input, int_bool_erreur);
	if(!*int_bool_erreur)
	{
		newTeinte = egalisation(im_image.teinte, im_image.width, im_image.height);
		im_sortie = creationImage("P2", im_image.width, im_image.height, im_image.teinteMax, newTeinte);
		libererImage(im_image);
		if (int_bool_save)	
			save(im_sortie, char_str_output, int_bool_erreur);
	}
	return (im_sortie);
}
