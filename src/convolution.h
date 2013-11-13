/*! \file convolution.h
 *  \author Lamarche Ludovic <lamarchelu@eisti.eu>
 *  \version 0.1
 *  \date Tue 08 Oct 2013
 *
 *  \brief Converti l'input dans l'output avec une convolution
 *
 *
 */
 
#ifndef __CONVOLUTION_H__
#define __CONVOLUTION_H__

#include "header.h"
#include "gestionFichier.h"

/*!
       \fn int testFinFichierFiltre(FILE filtre)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Sat 19 Oct 2013
       \brief permet de controler les caractères en fin de fichier, si il existe des caractères autres que le saut de ligne ou que l'espace        
       \return le nombre de caractères en trop dans le fichier
       \param filtre : (FILE*) fichier d'entré      
       \remarks 

*/
int testFinFichierFiltre(FILE* filtre);


int retournerLaTaille(int taille);
int calculTailleFiltre(FILE* filtre);
void remplirFiltre(FILE* filtre, int** matrice, int taille);


/*!
       \fn int** recupFiltre(FILE* filtre)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Sat 19 Oct 2013
       \brief renvoie le filtre dans une matrice de taille 3x3, taille normale d'un filtre pour une convolution               
       \param filtre : (file*) le filtre que l'on utilise pour la convolution
       \return une matrice de taille 3x3 contenant le filtre
               
       \remarks 

*/
int** recupFiltre(FILE* filtre, int taille);

/*!
       \fn int associationPossible(int x, int y, int i, int j, int largeur, int hauteur)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Sat 19 Oct 2013
       \brief renvoie un entier qui permet de savoir si la case à laquelle on applique le filtre est dans l'image ou une case inexistante (par exemple une coordonnées de l'image négative)               
       \param x : (int) l'abscisse du pixel de l'image auquel on veut appliquer le filtre
       \param y : (int) l'ordonnée du pixel de l'image auquel on veut appliquer le filtre
       \param i : (int) l'abscisse du coefficient du filtre que l'on applique 
       \param j : (int) l'ordonnée du coefficient du filtre que l'on applique 
       \param largeur : (int) la largeur de l'image
       \param hauteur : (int) la hauteur de l'image
       \return 1 si l'association est possible, 0 sinon
               
       \remarks 

*/
int associationPossible(int x, int y, int i, int j, int largeur, int hauteur);

/*!
       \fn int setNumber(int y, int x, int largeur, int hauteur, int** pixels, int** filtre)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Sat 19 Oct 2013
       \brief applique le filtre à un pixel de l'image               
       \param y : (int) l'ordonnée du pixel
       \param x : (int) l'abscisse du pixel	
       \param largeur : (int) la largeur de l'image
       \param hauteur : (int) la hauteur de l'image
       \param pixels : (int**) le tableau de pixels de l'image
       \param filtre : (int**) le filtre de convolution a appliquer sur l'image
       \return retourne la valeur du pixel après l'application du filtre
               
       \remarks 

*/
int setNumber(int y, int x, int largeur, int hauteur, int** pixels, int** filtre, int taille, int decalage);

/*!
       \fn int** applicationFiltre(Image image, int** filtre)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Sat 19 Oct 2013
       \brief applique le filtre à l'image               
       \param image : (image) l'image à laquelle est appliquée la convolution
       \param filtre : (int**) le filtre à appliquer sur l'image
       \return une matrice de pixels qui représente l'image après l'application du filtre, ie, après l'application de la convolution
               
       \remarks 

*/
int** applicationFiltre(Image image, int** filtre, int taille);

/*!
       \fn Image applicationConvolution(Image image, FILE* fichierFiltre)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Sat 19 Oct 2013
       \brief permet d'enchainer les fonctions qui permettent d'appliquer la convolution               
       \param image : (image) Image à traiter
       \param filtre : (FILE*) fichier contenant le filtre de convolution
       \return retourne un entier qui indique 0 pour le bon déroulement des fonctions
               
       \remarks 

*/
Image applicationConvolution(Image image, FILE* fichierFiltre, int taille);



/*!
       \fn int testFiltre(FILE* filtre)
       \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
       \date mar. 22 oct. 2013
       \brief Verifie le bon chargement du filtre
       \param filtre : (FILE*) le fichier qui contient le filtre à appliquer a la convolution
       \return 1 si le chargement est correct
               
       \remarks 

*/
int testFiltre(FILE* filtre);

/*!
       \fn Image convolution (char* input, char* output, char* nomFichier, int bool_save, int* bool_erreur)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Tue 08 Oct 2013
       \brief realise la convolution d une image en fonction d'une matrice en parametre               
       \param input : (char*) fichier d'entré
       \param output : (char*) fichier de sortie
       \param fichiermatrice : (char*) fichier contenant une matrice
       \param bool_save : si vaut 1 on affiche un message de sauvegarde pour l'utilisateur
       \param bool_erreur : adresse pour stocker un int, on lui donnera 1 si il y a une erreur dans la fonction
       \return l'image modifiée si !bool_save
               
       \remarks 

*/
Image convolution (char* input, char* output, char* nomFichier, int bool_save, int* bool_erreur);

#endif /* __CONVOLUTION_H__ */

