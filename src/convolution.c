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

int testFinFichierFiltre(FILE* filtre)
{
	int k;
	int test;
	char caractere;
	k = 0;
	test = 1;
	caractere = ' ';
	while (caractere != EOF && test == 1)
	{
		test = fscanf(filtre, "%c", &caractere);
		if (caractere != '\n' && caractere != ' ')
			k++;
	}
	return k;
}

int** recupFiltre(FILE* filtre)
{
	int i;
	int j;
	int** matrice;
	int coef;
	int test;
	int testFichier;
	matrice = initMatrice(3,3);
	for (i = 0; i < 3; i += 1)
	{
		for (j = 0; j < 3; j += 1)
		{
			test = fscanf(filtre, "%d", &coef);
			if(test == 1)
				matrice[i][j] = coef;
			else
				erreur(ERREUR_FILTRE, 1);
		}
	}
	testFichier = testFinFichierFiltre(filtre);
	if (testFichier != 0)
		erreur(ERREUR_FILTRE, 1);
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



int** applicationConvolution(Image image, FILE* filtre)
{
	int** apresConvolution;
	int** filtre;
	filtre = recupFiltre(fichierFiltre);
	Image imageConvolution;	
	apresConvolution = applicationFiltre(image, filtre);
	imageConvolution = creationImage("P2", image.width, image.height, 255, apresConvolution);
	return apresConvolution;

}

/*
	changer tous les types de sortie des fonctions
*/
Image convolution (char* input, char* output, char* nomFichier, int bool_save, int* bool_erreur)
{
	FILE* fichierFiltre;
	Image image;
	int** result;
	printf("**%s -c %s, filtre : %s**\n",input,output,nomFichier);
	fichierFiltre = fopen(nomFichier, "r");
	image = chargerImage(input, bool_erreur);
	if(testFiltre(fichierFiltre) && testType(image, "P2") && !*bool_erreur)
	{
		result = applicationConvolution(image, fichierFiltre);
		if(bool_save)
		{
			save(imageConvolution, output, bool_erreur);
			if(!*bool_erreur) printf("\tLa convolution sur le fichier %s a été effectuée avec succés. Le fichier de sortie est : %s \n", input, output);
		}
	}
	else
		*bool_erreur = 1;
	libererImage(image);
	fclose(fichierFiltre);
	return result;
}
