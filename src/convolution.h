/*! \file convolution.h
 *  \author Perales Quentin <peralesque@eisti.eu>
 *  \version 0.1
 *  \date  Tue 08 Oct 2013
 *
 *  \brief realise la convolution de l image a partir d'un fichier source
 *
 *
 */

#ifndef __CONVOLUTION_H__
#define __CONVOLUTION_H__

#include "header.h"
#include "gestionFichier.h"

/*!
       \fn int testFinFichierFiltre(FILE* file_filtre)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Sat 19 Oct 2013
       \brief permet de controler les caractères en fin de fichier, si il existe des caractères autres que le saut de ligne ou que l'espace        
       \return le nombre de caractères en trop dans le fichier
       \param file_filtre : (FILE*) fichier d'entré      
       \remarks 

*/
int testFinFichierFiltre(FILE* file_filtre);

/*!
       \fn int retournerLaTaille(int int_taille)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Wed 13 Nov 2013
       \brief permet de retourner la taille du filtre en supposant qu'il soit saisi sans erreur               
       \param int_taille : (int) la taille du filtre, elle sera calculée
       \return un entier qui correspond a la taille et renvoie 1 sinon
               
       \remarks 

*/
int retournerLaTaille(int int_taille);

/*!
       \fn int calculTailleFiltre(FILE* file_filtre)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Wed 13 Nov 2013
       \brief permet de calculer la taille du filtre               
       \param file_filtre : (file*) le filtre dans un fichier
       \return 
               
       \remarks 

*/
int calculTailleFiltre(FILE* file_filtre);

/*!
       \fn void remplirFiltre(FILE filtre, int** matrice, int taille)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Wed 13 Nov 2013
       \brief remplit le filtre des chiffres indiqués dans le fichier               
       \param file_filtre : (file) 
       \param int_matrice : (int**) 
       \param int_taille : (int) 
       
               
       \remarks 

*/
void remplirFiltre(FILE* file_filtre, int** int_matrice, int int_taille);


/*!
       \fn int** recupFiltre(FILE* file_filtre, int int_taille)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Sat 19 Oct 2013
       \brief renvoie le filtre dans une matrice de taille 3x3, taille normale d'un filtre pour une convolution               
       \param file_filtre : (file*) le filtre que l'on utilise pour la convolution
       \param int_taille : (int) la taille du filtre
       \return une matrice de taille 3x3 contenant le filtre
               
       \remarks 

*/
int** recupFiltre(FILE* file_filtre, int int_taille);


/*!
       \fn int setNumber(int int_x, int int_y, int int_largeur, int int_hauteur, int** int_pixels, int** mat_filtre, int int_taille, int int_decalage)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Sat 19 Oct 2013
       \brief applique le filtre à un pixel de l'image               
       \param int_y : (int) l'ordonnée du pixel
       \param int_x : (int) l'abscisse du pixel	
       \param int_largeur : (int) la largeur de l'image
       \param int_hauteur : (int) la hauteur de l'image
       \param int_pixels : (int**) le tableau de pixels de l'image
       \param mat_filtre : (int**) le filtre de convolution a appliquer sur l'image
       \param int_taille : (int) la taille du filtre
       \param int_decalage : (int) le decalage
       \return retourne la valeur du pixel après l'application du filtre
               
       \remarks 

*/
int setNumber(int int_x, int int_y, int int_largeur, int int_hauteur, int** int_pixels, int** mat_filtre, int int_taille, int int_decalage);

/*!
       \fn int** applicationFiltre(Image im_image, int** int_filtre, int int_taille)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Sat 19 Oct 2013
       \brief applique le filtre à l'image               
       \param im_image : (image) l'image à laquelle est appliquée la convolution
       \param file_filtre : (int**) le filtre à appliquer sur l'image
       \param int_taille : (int) la taille du filtre
       \param int_decalage : (int) le decalage de départ dû à la taille du filre
       \return une matrice de pixels qui représente l'image après l'application du filtre, ie, après l'application de la convolution
               
       \remarks 

*/
int** applicationFiltre(Image im_image, int** mat_filtre, int int_taille);

/*!
       \fn Image applicationConvolution(Image im_image, FILE* file_fichierFiltre, int int_taille)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Sat 19 Oct 2013
       \brief permet d'enchainer les fonctions qui permettent d'appliquer la convolution               
       \param im_image : (image) Image à traiter
       \param mat_filtre : (FILE*) fichier contenant le filtre de convolution
       \param int_taille : (int) la taille du filtre
       \return retourne un entier qui indique 0 pour le bon déroulement des fonctions
               
       \remarks 

*/
Image applicationConvolution(Image im_image, FILE* file_fichierFiltre, int int_taille);



/*!
       \fn int testFiltre(FILE* file_filtre)
       \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
       \date mar. 22 oct. 2013
       \brief Verifie le bon chargement du filtre
       \param file_filtre : (FILE*) le fichier qui contient le filtre à appliquer a la convolution
       \return 1 si le chargement est correct
               
       \remarks 

*/
int testFiltre(FILE* filtre);

/*!
       \fn Image convolution (char* str_input, char* str_output, char* str_nomFichier, int int_bool_save, int* int_bool_erreur)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Tue 08 Oct 2013
       \brief realise la convolution d une image en fonction d'une matrice en parametre               
       \param str_input : (char*) fichier d'entré
       \param str_output : (char*) fichier de sortie
       \param str_fichiermatrice : (char*) fichier contenant une matrice
       \param int_bool_save : si vaut 1 on affiche un message de sauvegarde pour l'utilisateur
       \param int_bool_erreur : adresse pour stocker un int, on lui donnera 1 si il y a une erreur dans la fonction
       \return l'image modifiée si !bool_save
               
       \remarks 

*/
Image convolution (char* input, char* output, char* nomFichier, int bool_save, int* bool_erreur);

#endif /* __CONVOLUTION_H__ */

