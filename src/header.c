/*! \file header.c
 *  \author Lamarche Ludovic <lamarchelu@eisti.eu>
 *  \version 0.1
 *  \date Mon 23 Sep 2013
 *
 *  \brief Fonctions utiles à l'ensemble du programme
 *
 *
 */
 #include <stdlib.h>
#include <stdio.h>

#define NO_INPUT_OR_OUTPUT 1
#define IMAGE_CORROMPUE 2
#define IMAGE_NO_EXISTS 3
#define NO_MEMORY 4
#define ERREUR_PARAMETRE 5


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





