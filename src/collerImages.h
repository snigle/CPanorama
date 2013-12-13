/*! \file  collerImages.h
	\author Poussou Elie poussoueli@eisti.eu
	\date Thu 12 Dec 2013
	
	\brief Permet la fusion de deux images en fonction de points en commun                                
	

*/
	
	
	
#ifndef __COLLERIMAGES_H__
#define __COLLERIMAGES_H__

#include <stdlib.h>
#include <time.h>
#include <math.h>


#include "header.h"
#include "gestionFichier.h"
#include "gestionListeCoordonnees.h"
#include "harris.h"

/*!
       \fn int* taille(ListePoints* liste1, ListePoints* liste2, int himage1, int himage2, int limage1, int limage2)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Thu 12 Dec 2013
       \brief retourne la hauteur et la largeur de l'image finale               
       \param liste1 : (listepoints*) : liste des points de Harris de la première image
       \param liste2 : (listepoints*) : liste des points de Harris de la deuxième image
       \param himage1 : (int) : hauteur de la première image
       \param himage2 : (int) : hauteur de la deuxième image
       \param limage1 : (int) : largeur de la première image
       \param limage2 : (int) : largeur de la deuxième image
       \return hauteur et largeur dans un tableau
               
       \remarks 

*/
int* taille(ListePoints* liste1, ListePoints* liste2, int hImage1, int hImage2, int  lImage1, int lImage2);

int** fusionCas1(int hauteur, int largeur, ListePoints* liste1, ListePoints* liste2, Image image1, Image image2);

int** fusionCas2(int hauteur, int largeur, ListePoints* liste1, ListePoints* liste2, Image image1, Image image2);

int** fusionFinale(int hauteur, int largeur, ListePoints* liste1, ListePoints* liste2, Image image1, Image image2);

Image imageFinale(char* char_str_input1, char* char_str_input2, char* char_str_output, int int_bool_save, int* int_bool_erreur);


#endif /* __COLLERIMAGES_H__ */
