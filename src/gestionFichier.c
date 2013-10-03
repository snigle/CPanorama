/*! \file recuperationFichier.c
 *  \author Perales Quentin <peralesque@eisti.eu>
 *  \version 0.1
 *  \date  Mon 23 Sep 2013
 *
 *  \brief chargement d'une image
 *
 *
 */


#include "header.h"




void allerAlaLigne (FILE* fichier){
	char carac;//un caractere quelconque
    do 
    {
    	fscanf(fichier, "%c", &carac);
    } while (carac != '\n');
}

void sauterCommentaire(FILE* fichier)
{
	char carac;//un caractere quelconque
	fscanf(fichier, "%c", &carac);
	if (carac == '\n' || carac == ' ' || carac == '\t')
	{
		sauterCommentaire(fichier);
	}else if (carac == '#' )
		{
			allerAlaLigne(fichier);
			sauterCommentaire(fichier);
		}else{
	   		fseek(fichier, -1, SEEK_CUR);
			 }
}

void recupType(char* tab, FILE* image) 
{
	sauterCommentaire(image);
	fscanf(image, "%c", &tab[0]);
	fscanf(image, "%c", &tab[1]);
	tab[2] = '\0';
}



int parametrage(FILE* image)
{
	int result;//le resultat de la fonction (largeur de l'image)
	int test; // permet de savoir si le scanf ne génère pas d'erreur
	result = 0;
	sauterCommentaire(image);
	test = fscanf(image, "%d", &result);
	if (test != 1)
		erreur(IMAGE_CORROMPUE);
    
    return result;
}


int teinteMax(char type[3], FILE* image)
{
    int result;
    result = 0;
    if (!strcmp(type, "P2") || !strcmp(type, "P3"))
	{
		result = parametrage(image);
	}else{
		result = 0;
	}
	return result;
}


void recuperationPixels(FILE* fichier, int** tab, int largeur, int hauteur)
{
	int i;
	int j;
	int pixel;
	int test; // permet de savoir si le scanf ne génère pas d'erreur
	pixel = 0;
	for (i = 0 ; i < hauteur ; i++)
	{
		for (j = 0; j < largeur; j += 1)
		{
			sauterCommentaire(fichier);
			test = fscanf(fichier, "%d", &pixel);
			if (test == 1)
				tab[i][j] = pixel;
			else
				erreur(IMAGE_CORROMPUE);
	
		}
	}
}


int** recupPixel(FILE* fichier, int largeur, int hauteur, char* type)
{
	int** tab;
	if (!strcmp(type, "P3"))
		largeur *= 3;
	tab = initMatrice(largeur,hauteur);	
	recuperationPixels(fichier, tab, largeur, hauteur);
	return tab;
}



Image chargerImage(char* nomImage){
	Image imageCharge;
	FILE* image;
	char type[3];
	int largeur;
	int hauteur;
	int teinteMaximale;
	int** teinte;
	image = fopen(nomImage, "r");
	if (image != NULL)
	{
		recupType(type, image);
		largeur = parametrage(image);
		hauteur = parametrage(image);
		teinteMaximale = teinteMax(type, image);
		teinte = recupPixel(image, largeur, hauteur, type);
		imageCharge = creationImage(type, largeur, hauteur, teinteMaximale, teinte);//création de l image
	}else
		erreur(IMAGE_NO_EXISTS);
	fclose(image);

	return imageCharge;	
}


void ecritureFichier(Image fichier){
	int i;
	int j;
	int largeur;
	largeur = largeurMatriceImage (image);
	fprintf(fich,"P%d\n",image.type);
	fprintf(fich,"%d\t",image.width);
	fprintf(fich,"%d\n",image.height);
	if (image.type != 1){
		fprintf(fich,"%d\n",image.teinteMax);
	}
	for(i=0;i<image.height;i++)
	{
		for (j = 0; j < largeur; j += 1)
		{
			fprintf(fich,"%d\n",image.teinte[i][j]);
		}
	}
}



int save(Image image, char* output)
{
	FILE* fich;
	fich=fopen(output, "w");
	if(fich != NULL)
	{
		ecritureFichier(image);
		fclose(fich);
		return 0;
	}
	else{
		return ERREUR_OUTPUT;
		}
}
