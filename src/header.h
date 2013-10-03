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


void erreur(int numeroErreur);

void* mallocBis(size_t taille);

int** initMatrice(int largeur, int hauteur);

int largeurMatriceImage (Image image);

Image creationImage(char* tab, int largeur, int hauteur, int teinteMaximale, int** pixel);


#endif /* __HEADER_H__ */
