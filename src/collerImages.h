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

int* taille(ListePoints* decalage, int hImage1, int hImage2, int  lImage1, int lImage2);

int** fusion(ListePoints* decalage, int largeur, int hauteur, Image image1, Image image2);

Image imageFinale(Image image1, Image image2, ListePoints* decalage);
/*

int** fusionCas1(int hauteur, int largeur, ListePoints* liste1, ListePoints* liste2, Image image1, Image image2);

int** fusionCas2(int hauteur, int largeur, ListePoints* liste1, ListePoints* liste2, Image image1, Image image2);

int** fusionFinale(int hauteur, int largeur, ListePoints* liste1, ListePoints* liste2, Image image1, Image image2);

Image imageFinale(char* char_str_input1, char* char_str_input2, char* char_str_output, int int_bool_save, int* int_bool_erreur);*/


#endif /* __COLLERIMAGES_H__ */
