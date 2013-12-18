

#ifndef __EGALISER_HISTOGRAMME_H__
#define __EGALISER_HISTOGRAMME_H__

#include "header.h"
#include "gestionFichier.h"
#include "histogramme.h"

/*!
       \fn int getMax(int** tab, int int_longueur, int int_largeur)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Wed 27 Nov 2013
       \brief Description Renvoie le max d'une matrice               
       \param tab : (int**) une matrice des pixels d'entiers
       \param int_longueur : (int) la longueur de l image
       \param int_largeur : (int) la largeur de l image
       \return un entier
               
       \remarks 

*/
int getMax (int** tab, int int_longueur, int int_largeur);

/*!
       \fn int getMin(int** tab, int int_longueur, int int_largeur)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Wed 27 Nov 2013
       \brief Renvoie le min d'une matrice               
       \param tab : (int**) une matrice des pixels d'entiers
       \param int_longueur : (int) la longueur de l image
       \param int_largeur : (int) la largeur de l image
       \return un entier
               
       \remarks 
1770 1945
*/
int getMin (int** tab, int int_longueur, int int_largeur);

/*!
       \fn int** egalisation (int** teinte, int int_longueur, int int_largeur)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Wed 27 Nov 2013
       \brief Egalise une image : le minimum de l'image est mis a 0, le max a 255.      
       \param teinte : (int**) le tableau de pixel (l'image a egaliser
       \param int_longueur : (int) la longueur de l image
       \param int_largeur : (int) la largeur de l image
       \return 
               
       \remarks 

*/
/*int** egalisation (int** teinte, int int_longueur, int int_largeur);*/

/*void decalerImages (Image im_image1, Image im_image2, int** newTeinte1, int** newTeinte2, int decalage);
void egalisation(Image im_image1,Image im_image2, int** newTeinte1, int** newTeinte2, int* int_bool_erreur);*/
/*!
       \fn Image egaliserHistogramme(char* char_str_input, char* char_str_output, int int_bool_save, int* int_bool_erreur)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Wed 27 Nov 2013
       \brief renvoie une image où les differences de teintes               
       \param char_str_input : (char*) le fichier en entrée
       \param char_str_output : (char*) le fichier en sortie
       \param int_bool_save : (int) booleen pour savoir si on sauvegarde l image
       \param int_bool_erreur : (int*) verifie s'il y a une erreur
       \return 
               
       \remarks 

*/
/*
Image egaliserHistogramme (char* char_str_input, char* char_str_output, int int_bool_save, int* int_bool_erreur);
*/
#endif
