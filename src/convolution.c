/*! \file convolution.c
 *  \author Perales Quentin <peralesque@eisti.eu>
 *  \version 0.1
 *  \date  Tue 08 Oct 2013
 *
 *  \brief realise la convolution de l image a partir d'un fichier source
 *
 *
 */
#include "convolution.h"

/*
récupérer le filtre
	la longueur
	la hauteur
	les valeurs
	
pour chaque pixels sauf à l'exterieurs, appliquer le filtre
*/

int** recupFiltre(FILE* filtre)
{
	int i;
	int j;
	int** matrice;
	int coef;
	int test;
	matrice = initMatrice(3,3);
	for (i = 0; i < 3; i += 1)
	{
		for (j = 0; j < 3; j += 1)
		{
			test = fscanf(filtre, "%d", &coef);
			if(test == 1)
				matrice[i][j] = coef;
			else
				printf("Le fichier n'est pas adapté");
		}
	}
	/*
	test de fin
	*/
	return matrice;
}

int associationPossible(int x, int y, int i, int j, int largeur, int hauteur)
{
	int hautDroit;
	int hautGauche;
	int basDroit;
	int basGauche;
	int haut;
	int bas;
	int gauche;
	int droit;
	int quelconque;
	
	quelconque = (x >= 1) && (y>=1) && (x < hauteur-1) && (y < largeur-1);
	
	hautDroit = (x==0) && (y==0) && (i >= 1) && (j >= 1);
	hautGauche = (x == 0) && (y == largeur-1) && (i >= 1) && (j >= 1);
	basDroit = (x == hauteur-1) && (y == 0) && (i <= 1) && (j >= 1);
	basGauche = (x == hauteur-1) && (y== largeur-1) && (i <= 1) && (j <= 1);
	
	droit = (x > 0) && (x < (hauteur-1)) && (y == 0) && (j >= 1);
	gauche = (x > 0) && (x < (hauteur-1)) && (y <= (largeur-1)) && (j <= 1);
	bas = (x == hauteur-1) && (y > 0) && (y < largeur-1) && (i <= 1);
	haut = (x == 0) && (y > 0) && (y < largeur-1) && (i >= 1);
	
	return quelconque || hautDroit || hautGauche || basDroit || basGauche || droit || gauche || bas || haut ;
}



int setNumber(int x, int y, int largeur, int hauteur, int** pixels, int** filtre)
{
	int i;
	int j;
	int result;
	result = 0;
	for (i = 0; i < 3; i += 1)
	{
		for (j = 0; j < 3; j += 1)
		{
			if (associationPossible(x, y, i, j, largeur, hauteur))
				result += filtre[i][j] * pixels[x-1+i][y-1+i];
		}
	}
	if (result < 0)
		return (0);
	else if (result > 255)
		return (255);
	else
		return result;
}



int** applicationFiltre(Image image, int** filtre)
{
	int** result;
	int i;
	int j;
	result = initMatrice(image.width, image.height);
	for (i = 0; i < image.height; i += 1)
	{
		for (j = 0; j < image.width; j += 1)
		{
			result[i][j] = setNumber(i, j, image.width, image.height, image.teinte, filtre);
		}
	}
	return result;
}



int applicationConvolution(Image image, int** filtre, char* output)
{
	int** apresConvolution;
	Image imageConvolution;	
	apresConvolution = applicationFiltre(image, filtre);
	imageConvolution = creationImage("P2", image.width, image.height, 255, apresConvolution);
	save(imageConvolution, output);
	libererImage(imageConvolution);
	return (0);
}

int convolution (char* input, char* output, char* nomFichier)
{
	FILE* fichierFiltre;
	int** filtre;
	Image image;
	int result;
	filtre = initMatrice(3,3);
	fichierFiltre = fopen(nomFichier, "r");
	image = chargerImage(input);
	if(fichierFiltre != NULL)
	{
		filtre = recupFiltre(fichierFiltre);
		if(!strcmp(image.type, "P2"))
		{
			result = applicationConvolution(image, filtre, output);
			libererImage(image);
		}else{
			printf("Erreur de type");
		}
	}else{
		printf("Erreur de chargement");
	}
	return result;
}
