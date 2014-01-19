/*! \file  histogramme.h
	\author Poussou Elie poussoueli@eisti.eu
	\date Tue 22 Oct 2013
	
	\brief Permet d'avoir l'histogramme d'une image en niveaux de gris                                 
	

*/

#ifndef __HISTOGRAMME_H__
#define __HISTOGRAMME_H__

#include "header.h"
#include "gestionFichier.h"


/*!
       \fn Image histogrammeBis(char* str_input, char* str_output, int bool_save, int* bool_erreur, int* hist, Image image)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Wed 20 Nov 2013
       \brief réalise l'histogramme dans un fichier .pbm               
       \param str_input : (char*) le nom du fichier input
       \param str_output : (char*) le nom du fichier output
       \param bool_save : (int) un booleen pour savoir s'il faut sauvegarder
       \param bool_erreur : (int*) un booleen qui dit s'il y a une erreur
       \param hist : (int*) le tableau de l histogramme
       \param image : (image) l'image en input
       \return 
               
       \remarks 

*/
Image histogrammeBis (char* char_str_input, char* char_str_output, int int_bool_save, int* int_bool_erreur, int* int_hist, Image im_image);
/*!
       \fn int histogramme(char* input, char* output)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Tue 08 Oct 2013
       \brief réalise l'histogramme dans un fichier .pbm               
       \param input : (char*) : le nom de l'image en entrée
       \param output : (char*) : le nom de l'image en sortie
       \return un entier qui confirme le bon fonctionnement de la fonction
               
       \remarks 

*/
Image histogramme (char* char_input, char* char_output, int int_bool_save, int* int_bool_erreur);

/*!
       \fn int* remplirTableauHist(Image image)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Mon 28 Oct 2013
       \brief rempli un tableau de 1 à 256 avec le nombre de pixels pour chaque teinte               
       \param image : (image) : l'image avec laqulle on travaille
       \return un tableau
               
       \remarks 

*/
int* remplirTableauHist(Image im_image, int* int_bool_erreur);

/*!
       \fn int calculMax(int* tabhist)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Mon 28 Oct 2013
       \brief retourne le maximum de tabhist cad le nombre de pixels maximum pour une teinte               
       \param tabhist : (int*) 
       \return un entier
               
       \remarks 

*/
int calculMax(int* int_tabhist, int int_teinteMax);

/*!
       \fn int** Tracer(Image image, int taille)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Mon 28 Oct 2013
       \brief permet de tracer l'histogramme               
       \param image : (image) : l'image dont on veut obtenir l'histogramme
       \param taille : (int) : largeur de la matrice
       \return 
               
       \remarks 

*/
int** Tracer(int* int_tabhist, int int_taille, int int_teinteMax);

/*!
       \fn void remplirNouvellesTeintes(Image image, int decalage)
       \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
       \date dim. 19 janv. 2014
       \brief remplie des teintes de l'image               
       \param image : (image) image à modifier
       \param decalage : (int) décalage utilisé
       
               
       \remarks 

*/
void remplirNouvellesTeintes (Image image, int decalage);

/*!
       \fn int calculMediane(int iterationMediane, int* histogramme)
       \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
       \date dim. 19 janv. 2014
       \brief Calcul la médiane en fonction de l'histogramme               
       \param iterationmediane : (int) iteration de récursivité à 0
       \param histogramme : (int*) histogramme ( tableau de int)
       \return retourne la médiane
               
       \remarks 

*/
int calculMediane(int iterationMediane,int* histogramme);

/*!
       \fn int calculDecalage(Image im_image1, Image im_image2, int* m1supm2, int* int_bool_erreur)
       \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
       \date dim. 19 janv. 2014
       \brief Calcul le décalage               
       \param im_image1 : (image) Image 1
       \param im_image2 : (image) image 2
       \param m1supm2 : (int*) 
       \param int_bool_erreur : (int*) boolean d'erreur, (ne rien faire si vaut 1)	
       \return retourne un décalage
               
       \remarks 

*/
int calculDecalage(Image im_image1, Image im_image2, int* m1supm2, int* int_bool_erreur);

/*!
       \fn int* abPourcent(int* hist, int max)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Thu 31 Oct 2013
       \brief Description               
       \param hist : (int*) 
       \param max : (int) 
       \return 
               
       \remarks 

*/
int* tabPourcent(int* int_hist, int int_max, int int_h, int int_teinteMax);
#endif /* __HISTOGRAMME_H__ */

