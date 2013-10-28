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
#define ERREUR_TYPE 14


#define NO_INPUT_OR_OUTPUT 21
#define ERREUR_OUTPUT 22
#define PAS_ASSEZ_D_INPUTS 23

#define NO_DOSSIER 31
#define ERREUR_PARAMETRE 32
#define TROP_D_OPTIONS 33
#define	ERREUR_FILTRE 34

#define NO_MEMORY 1


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
       \param numeroErreur : (int) un entier qui donne le numéro de l'erreur
       
               
       \remarks 

*/

void erreursImage (int numeroErreur);

/*!
       \fn void erreurInputOutput(int numeroErreur)
       \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
       \date mer. 16 oct. 2013
       \brief Affiche les erreurs en rapport avec les inputs et les outputs               
       \param numeroerreur : (int) numéro de l'erreur
       
               
       \remarks 

*/
void erreurInputOutput(int numeroErreur);

/*!
       \fn void erreurParametre(int numeroErreur)
       \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
       \date mer. 16 oct. 2013
       \brief Affiche les erreurs en rapport avec les paramètres               
       \param numeroerreur : (int) numéro de l'erreur
       
               
       \remarks 

*/
void erreurParametre(int numeroErreur);

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
	
	\param int numeroerreur : entier correspondant à un nombre d'erreur
	\param int sortir : entier qui precise s'il faut arreter le programme
		
		\remarks ras

*/
void erreur(int numeroErreur, int sortir);


 /*!
 	\fn mallocBis
 	\author LAMARCHE Ludovic <lamarchelu@eisti.eu>
 	\date Mon 23 Sep 2013
 	\brief Description
 	
 	\param taille : (size_t) mémoire à allouer
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
       \param image : (image) l'image utilisée
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
       \param tab : (char*) : le type de l'image
       \param largeur : (int) : la largeur de l'image
       \param hauteur : (int) : la hauteur de l'image
       \param teinteMax : (int) : la teinte maximale (pour le type P2 et P3)
       \param pixel : (int**) : matrice de pixels
       \return 
               retourne un type image
               \remarks 

*/
Image creationImage(char* tab, int largeur, int hauteur, int teinteMaximale, int** pixel);

/*!
	\fn void libererMatrice(void** mat, int largeur)
	\author LAMARCHE Ludovic <lamarchelu@eisti.eu>
	\date Mon 07 Oct 2013
	\brief Libère une matrice		
	\param mat : (void**) Matrice à libérer
	\param largeur : (int) Longueur de la première composante de la matrice
	
		
	\remarks 

*/
void libererMatrice(void** mat, int largeur);

/*!
       \fn void libererImage(Image image)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Sat 05 Oct 2013
       \brief libère la mémoire utilisée par l'image chargée               
       \param image : (image) : l'image chargée
       \return 
               
       \remarks 

*/

void libererImage(Image image);


/*!
       \fn void verifType(char* type)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Mon 07 Oct 2013
       \brief Envoie une erreur si le type n'est pas P1 ou P2 ou P3        
       \return 
               
       \remarks 

*/
int verifType(char* type);

/*!
       \fn int testType(Image image, char* type)
       \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
       \date mar. 22 oct. 2013
       \brief Verifie si le type est correct pour appliquer une convolution 
       \param image : image à tester
       \param type : type à tester
       \return 1 si le type de l'image correspond au paramètre, 0 sinon
               
       \remarks 

*/
int testType(Image image, char* type);

#endif /* __HEADER_H__ */
