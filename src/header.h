/*! \file header.h
 *  \author Perales Quentin <peralesque@eisti.eu>
 *  \version 0.1
 *  \date  Mon 23 Sep 2013
 *
 *  \brief structure et librairie utile pour l'ensemble du programme
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


/*! \struct Image  
	\author Perales Quentin <peralesque@eisti.eu>
 *  \version 0.1
 *  \date  Mon 23 Sep 2013
 *
 *  \brief structure d'un fichier image en pixmap
 	
 	width : la largeur de l'image
 	height : la hauteur de l'image
 	teinte un tableau d'entier définissant les teintes de pixels
 *
 *
 */
typedef struct Image Image;
struct Image {
	char type[2];/*!< type P1 P2 ou P3 */
	int width;/*!<width : la largeur de l'image*/
	int height;/*!<height : la hauteur de l'image*/
	int teinteMax;/*!<indique le teinte maximale*/
	int* teinte;/*!< 	teinte un tableau d'entier définissant les teintes de pixels*/
};

/*! \struct ListeStr
	\author Lamarche Ludovic <lamarchelu@eisti.eu>
 *  \version 0.1
 *  \date  Mon 23 Sep 2013
 *
 *  \brief Structure de liste chainée de chaine de caractères
 *
 */
typedef struct ListeStr ListeStr;
struct ListeStr {
	char* chaine;/*!<chaine de caractères*/
	char** suivant;/*!< adresse de la chaine suivante*/
};

void erreur(int numeroErreur);

void* mallocBis(size_t taille);

