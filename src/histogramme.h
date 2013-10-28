#ifndef __HISTOGRAMME_H__
#define __HISTOGRAMME_H__

#include "header.h"
#include "gestionFichier.h"


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
int calculMax(int* tabhist);

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
int** Tracer(int* tabhist, int taille);
#endif /* __HISTOGRAMME_H__ */

