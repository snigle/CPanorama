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



int getType(char* tab)
{
	int result;
	char car[2];
	car[0]=tab[1];
	car[1]='\0';
	result = atoi(car);
	return result;
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
Image creationImage(char* tab, int largeur, int hauteur, int teinteMaximale, int* pixel)
{
	Image newImage;
	newImage.type = getType(tab);
	newImage.width = largeur;
	newImage.height = hauteur;
	newImage.teinteMax = teinteMaximale;
	newImage.teinte = pixel;
	return newImage;
}

