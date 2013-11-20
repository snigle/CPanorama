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
Image histogrammeBis (char* str_input, char* str_output, int bool_save, int* bool_erreur, int* hist, Image image);
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
Image histogramme (char* input, char* output, int bool_save, int* bool_erreur);

/*!
       \fn int* remplirTableauHist(Image image)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Mon 28 Oct 2013
       \brief rempli un tableau de 1 à 256 avec le nombre de pixels pour chaque teinte               
       \param image : (image) : l'image avec laqulle on travaille
       \return un tableau
               
       \remarks 

*/
int* remplirTableauHist(Image image, int* bool_erreur);

/*!
       \fn int calculMax(int* tabhist)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Mon 28 Oct 2013
       \brief retourne le maximum de tabhist cad le nombre de pixels maximum pour une teinte               
       \param tabhist : (int*) 
       \return un entier
               
       \remarks 

*/
int calculMax(int* tabhist, int teinteMax);

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
int** Tracer(int* tabhist, int taille, int teinteMax);

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
int* tabPourcent(int* hist, int max, int h, int teinteMax);
#endif /* __HISTOGRAMME_H__ */

