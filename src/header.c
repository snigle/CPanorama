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




/*!
	\fn erreur
	\author LAMARCHE Ludovic <lamarchelu@eisti.eu>
	\date Tue 24 Sep 2013
	\brief Coupe le programme et affiche une erreur
	
	\param	
		int numeroerreur : entier correspondant à un nombre d'erreur
	
		
		\remarks ras

*/
void erreur(int numeroErreur)
{
	int result;
	result = 1;
	switch(numeroErreur)
	{
		case 0:
			printf("Le programme s'est terminé correctement\n");
			result = 0;
		break;
		case NO_INPUT_OR_OUTPUT:
			printf("Il n'y a aucun fichier en input ou en output\n");
		break;
		case IMAGE_CORROMPUE:
			printf("Le fichier image est corrompu\n");
		break;
		case IMAGE_NO_EXISTS:
			printf("Le fichier image n'existe pas\n");
		break;
		case NO_MEMORY:
			printf("Il manque de l'espace mémoire pour faire un malloc\n");
		break;
		case MAUVAIS_FORMAT_GRAYSCALE:
			printf("L'image n'est pas adaptée. Vous devez utiliser une image en .ppm pour réaliser une image en échelle de gris\n");
		break;
		case ERREUR_PARAMETRE:
			printf("Les paramètres ne sont pas entrés correctement, entrez panorama -h pour plus d'informations\n");
		break;
		case ERREUR_OUTPUT:
			printf("Le programme n'a pas la permission d'écrire dans le fichier en output\n");
		break;
		default :
			printf("Une erreur est survenue\n");
		break;
	}
	exit(result);
}



 /*!
 	\fn mallocBis
 	\author LAMARCHE Ludovic <lamarchelu@eisti.eu>
 	\date Mon 23 Sep 2013
 	\brief Description
 	
 	\param 	
 		size_t taille : mémoire à allouer
 	\return 
 		
 		\remarks a tester
 
 */
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


/*!
       \fn creationImage
       \author Perales Quentin <peralesque@eisti.eu>
	\date Tue 24 Sep 2013
	\brief permet de créer une image pixmap avec toutes les informations en paramètres
       
       \param       
       	char tab[3] : le type de pixmap
       	int largeur : la largeur de l'image
       	int hauteur : la hauteur de l'image
       	int teintemaximale : la teinte maximale
       	int* pixel : un tableau d'entier qui correspondent aux pixels de l'image
       \return 
               retourne un type image
               \remarks 

*/
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

