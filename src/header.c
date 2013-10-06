/*! \file header.c
 *  \author Lamarche Ludovic <lamarchelu@eisti.eu>
 *  \version 0.1
 *  \date Mon 23 Sep 2013
 *
 *  \brief Fonctions utiles à l'ensemble du programme
 *
 *
 */


#include "header.h"


void erreursImage (int numeroErreur){
	switch(numeroErreur)
	{
		case IMAGE_CORROMPUE:
			fprintf(stderr,"Le fichier image est corrompu\n");
		break;
		case IMAGE_NO_EXISTS:
			fprintf(stderr,"Le fichier image n'existe pas\n");
		break;
		case MAUVAIS_FORMAT_GRAYSCALE:
			fprintf(stderr,"L'image n'est pas adaptée. Vous devez utiliser une image en .ppm pour réaliser une image en échelle de gris\n");
		break;
		default :
			fprintf(stderr,"Erreur non répertoriée\n");
		break;
	}
}

void autreErreurs(int numeroErreur){
switch(numeroErreur)
	{
		case NO_INPUT_OR_OUTPUT:
			fprintf(stderr,"Il n'y a aucun fichier en input ou en output\n");
		break;
		case NO_MEMORY:
			fprintf(stderr,"Il manque de l'espace mémoire pour faire un malloc\n");
		break;
		case ERREUR_PARAMETRE:
			fprintf(stderr,"Les paramètres ne sont pas entrés correctement, entrez panorama -h pour plus d'informations\n");
		break;
		case ERREUR_OUTPUT:
			fprintf(stderr,"Le programme n'a pas la permission d'écrire dans le fichier en output\n");
		break;
		default :
			fprintf(stderr,"Erreur non répertoriée\n");
		break;
	}
}



void erreur(int numeroErreur)//ajouter un parametre pour savoir si on doit exit ou pas. Pour limiter la taille, associer les erreurs des images dans une fonction, et les autres dans une autre. Ne pas envoyer dans printf mais dans fprintf(stderr, );
{
	int result;
	result = 1;
	if (numeroErreur == NO_INPUT_OR_OUTPUT || numeroErreur == NO_MEMORY || numeroErreur == ERREUR_OUTPUT || numeroErreur == ERREUR_PARAMETRE)
	{
		autreErreurs(numeroErreur);
		exit(result);
	}else if (numeroErreur == IMAGE_CORROMPUE || numeroErreur == IMAGE_NO_EXISTS || numeroErreur == MAUVAIS_FORMAT_GRAYSCALE)
			{
				erreursImage(numeroErreur);
				exit(result);
			}else if (numeroErreur == 0){
						printf("Le programme s'est terminé correctement\n");
					}else{
							fprintf(stderr,"Une erreur est survenue\n");
							exit(result);
						}
}



void* mallocBis(size_t taille)
 {
 	void* result;
 	
	result = malloc(taille);
	if(result == NULL)
		erreur(NO_MEMORY);
	return result;
 }


int** initMatrice(int largeur, int hauteur)
{
	int** tab;
	int i;
	tab = mallocBis(hauteur * sizeof(int*));
	for (i = 0; i < hauteur; i += 1)
		tab[i] = mallocBis(largeur * sizeof(int));
	return tab;
}

int largeurMatriceImage (Image image)
{
	int largeur;
	if(!strcmp(image.type, "P3"))
		largeur = 3 * image.width;
	else
		largeur = image.width;
	return largeur;
}


Image creationImage(char* type, int largeur, int hauteur, int teinteMaximale, int** pixel)
{
	Image newImage;
	newImage.type = strdup(type);
	newImage.width = largeur;
	newImage.height = hauteur;
	newImage.teinteMax = teinteMaximale;
	newImage.teinte = pixel;
	return newImage;
}

int libererImage(Image image)
{
	int largeur;
	largeur = largeurMatriceImage(image);
	int i;
	
	free(image.type);
	
	for(i=0;i<largeur;i++)
	{
		free(image.teinte[i]);	
	}
	return 0 ;
}

