/*! \file header.h
 *  \author Perales Quentin <peralesque@eisti.eu>
 *  \version 0.1
 *  \date  Mon 23 Sep 2013
 *
 *  \brief structure et librairie utile pour l'ensemble du programme
 *
 *
 */
#ifndef __HEADER_H__
#define __HEADER_H__



#include <stdlib.h>
#include <stdio.h>
#include <string.h>



#define NO_INPUT_OR_OUTPUT 1
#define IMAGE_CORROMPUE 2
#define IMAGE_NO_EXISTS 3
#define NO_MEMORY 4
#define ERREUR_PARAMETRE 5
#define MAUVAIS_FORMAT_GRAYSCALE 6
#define ERREUR_OUTPUT 7

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
typedef struct Image
{
	char* type;/*!< type P1 P2 ou P3 */
	int width;/*!<width : la largeur de l'image*/
	int height;/*!<height : la hauteur de l'image*/
	int teinteMax;/*!<indique le teinte maximale*/
	int** teinte;/*!< 	teinte un tableau d'entier définissant les teintes de pixels*/
}Image;

/*!
	\fn erreur
	\author LAMARCHE Ludovic <lamarchelu@eisti.eu>
	\date Tue 24 Sep 2013
	\brief Coupe le programme et affiche une erreur
	
	\param	
		int numeroerreur : entier correspondant à un nombre d'erreur
	
		
		\remarks ras

*/
void erreur(int numeroErreur);


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
void* mallocBis(size_t taille);

int** initMatrice(int largeur, int hauteur);

int largeurMatriceImage (Image image);


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
Image creationImage(char* tab, int largeur, int hauteur, int teinteMaximale, int** pixel);
/*!
       \fn int libererImage(Image image)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Sat 05 Oct 2013
       \brief libère la mémoire utilisée par l'image chargée               
       \param image : (image) : l'image chargée
       \return 
               
       \remarks 

*/
int libererImage(Image image)

#endif /* __HEADER_H__ */
