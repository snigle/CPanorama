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

int retournerLaTaille(int taille)
{
	int i;
	i = 1;
	while (i*i < taille)
	{
		i++;
	}
	if ((i != 1) && (i*i == taille) && (i%2 == 1))
	{
		return (i);
	}else{
		return (1);
	}	
}

int calculTailleFiltre(FILE* filtre)
{
	int i;
	int taille;
	int test; /*vérifie si le scanf se déroule bien*/
	taille = 0;
	test = 1;
	i = 0;
	while (test == 1)
	{
		test = fscanf(filtre, "%d", &i);
		if (test == 1)
		{
			taille++;
		}
	}
	return retournerLaTaille(taille);
}

void remplirFiltre(FILE* filtre, int** matrice, int taille)
{
	int i;
	int j;
	int coef;
	int test;
	for (i = 0; i < taille; i += 1)
	{
		for (j = 0; j < taille; j += 1)
		{
			test = fscanf(filtre, "%d", &coef);
			if(test == 1)
				matrice[i][j] = coef;
			else
				erreur(ERREUR_FILTRE, 1);
		}
	}
}

int** recupFiltre(FILE* filtre, int taille)
{

	int** matrice;
	int testFichier;
	if (taille != 1)
	{
		rewind(filtre);
		matrice = initMatrice(taille,taille);
		remplirFiltre(filtre, matrice, taille);
		testFichier = testFinFichierFiltre(filtre);
		if (testFichier != 0)
			erreur(ERREUR_FILTRE, 1);
	}else{
		erreur(ERREUR_FILTRE, 1);
	}
	return (matrice);
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




int setNumber(int x, int y, int largeur, int hauteur, int** pixels, int** filtre, int taille, int decalage)
{
	int i;
	int j;
	int result;
	result = 0;
	for (i = 0; i < taille; i += 1)
	{
		for (j = 0; j < taille; j += 1)
		{
				result += filtre[i][j] * pixels[x-decalage+i][y-decalage+i];
		}
	}
	if (result < 0)
		return (0);
	else if (result > 255)
		return (255);
	else
		return result;
}



int** applicationFiltre(Image image, int** filtre, int taille)
{
	int** result;
	int i;
	int j;
	int decalage;
	decalage = (taille - 1) / 2;
	result = initMatrice(image.width, image.height);
	for (i = 0; i < image.height; i += 1)
	{
		for (j = 0; j < image.width; j += 1)
		{
			if ((i < decalage) || (j < decalage) || (i >= (image.height - decalage)) || (j >= (image.width - decalage)))
				result[i][j] = image.teinte[i][j];
			else
				result[i][j] = setNumber(i, j, image.width, image.height, image.teinte, filtre, taille, decalage);
		}
	}
	return result;
}



Image applicationConvolution(Image image, FILE* fichierFiltre, int taille)
{
	int** apresConvolution;
	int** filtre;
	Image imageConvolution;	
	filtre = recupFiltre(fichierFiltre, taille);

	apresConvolution = applicationFiltre(image, filtre, taille);
	imageConvolution = creationImage("P2", image.width, image.height, 255, apresConvolution);
	
	return imageConvolution;

}


int testFiltre(FILE* filtre)
{
	int result;
	if (filtre == NULL)
	{
		erreur(ERREUR_FILTRE, NO_EXIT);
		result = 0;
	}else
		result = 1;
		
	return(result);
}

Image convolution (char* input, char* output, char* nomFichier, int bool_save, int* bool_erreur){
	FILE* fichierFiltre;
	Image image;
	Image result;
	int taille;
	printf("**%s -c %s, filtre : %s**\n",input,output,nomFichier);
	fichierFiltre = fopen(nomFichier, "r");
	image = chargerImage(input, bool_erreur);
	if(!*bool_erreur){
		if(testFiltre(fichierFiltre) && testType(image, "P2"))
		{
			taille = calculTailleFiltre(fichierFiltre);
			result = applicationConvolution(image, fichierFiltre, taille);
			if(bool_save)
			{
				save(result, output, bool_erreur);
				if(!*bool_erreur) printf("\tLa convolution sur le fichier %s a été effectuée avec succés. Le fichier de sortie est : %s \n", input, output);
			}
			fclose(fichierFiltre);
		}
		else
			*bool_erreur = 1;
		libererImage(image);
	}
	return (result);
}
