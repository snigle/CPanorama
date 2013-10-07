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




#define IMAGE_CORROMPUE 11
#define IMAGE_NO_EXISTS 12
#define MAUVAIS_FORMAT_GRAYSCALE 13

#define NO_MEMORY 1
#define ERREUR_PARAMETRE 2
#define NO_INPUT_OR_OUTPUT 4
#define ERREUR_OUTPUT 3

#define EXIT 1
#define NO_EXIT 0

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
       \fn void erreursImage(int numeroErreur)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Mon 07 Oct 2013
       \brief spécifie l'erreur à l'utilisateur en fonction du numéro de celle ci. Toutes les erreurs sont issues d'un traitement de l'image               
       \param numeroerreur : (int) un entier qui donne le numéro de l'erreur
       
               
       \remarks 

*/

void erreursImage (int numeroErreur);


/*!
       \fn void autreErreurs(int numeroErreur)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Mon 07 Oct 2013
       \brief spécifie l'erreur à l'utilisateur en fonction du numéro de celle ci. Toutes les erreurs correspondent à une erreur autre qu'un traitement de l'image.
       \param numeroErreur : (int) le num qui renseigne l'erreur au cours du programme
       
               
       \remarks 

*/

void autreErreurs(int numeroErreur);

/*!
	\fn erreur
	\author LAMARCHE Ludovic <lamarchelu@eisti.eu>
	\date Tue 24 Sep 2013
	\brief Coupe le programme et affiche une erreur
	
	\param	
		int numeroerreur : entier correspondant à un nombre d'erreur
	
		
		\remarks ras

*/
void erreur(int numeroErreur, int sortir);


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

/*!
       \fn int** initMatrice(int largeur, int hauteur)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Mon 07 Oct 2013
       \brief initialise une matrice correspondant à la taille de l'image à traiter               
       \param largeur : (int) la largeur de l'image
       \param hauteur : (int) la hauteur de l'image
       \return une matrice d'entiers à compléter
               
       \remarks 

*/

int** initMatrice(int largeur, int hauteur);

/*!
       \fn int largeurMatriceImage(Image image)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Mon 07 Oct 2013
       \brief permet de connaitre la largeur à parcourir en fonction u type de l'image               
       \param image : (image) 
       \return un entier correspondant au nombre de chiffres à parcourir par ligne de matrice en fonction du type de l'image
               
       \remarks 

*/

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
int libererImage(Image image);

#endif /* __HEADER_H__ */
