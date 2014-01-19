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


/*!
       \fn int pixelNoir(Image image, int x, int y, int ppm)
       \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
       \date dim. 19 janv. 2014
       \brief Vérifie si un pixel est noir      
       \param image : (image) Image à tester
       \param x : (int) position en x
       \param y : (int) position en y
       \param ppm : (int) vaut 3 si c'est un ppm
       \return retourne 1 si le pixel est noir
               
       \remarks 

*/
int pixelNoir(Image image, int x, int y, int ppm);

/*!
       \fn int* taille(ListePoints* decalage, int hImage1, int hImage2, int lImage1, int lImage2)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Wed 18 Dec 2013
       \brief Cette fonction retourne la taille de l'image résultant de la fusions de 2 images               
       \param decalage : (listepoints*) : décalage de la deuxième image par rapport à la première
       \param himage1 : (int) : hauteur de la première image
       \param himage2 : (int) : hauteur de la deuxième image
       \param limage1 : (int) : largeur de la première image
       \param limage2 : (int) : largeur de la deuxième image
       \return 
               
       \remarks 

*/
int* taille(ListePoints* decalage, int hImage1, int hImage2, int  lImage1, int lImage2);

/*!
       \fn int** fusionCas1(ListePoints* decalage, int largeur, int hauteur, Image image1, Image image2)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Wed 18 Dec 2013
       \brief Fusionne 2 images quand les décalages en x et en y sont positifs               
       \param decalage : (listepoints*) : décalage de la deuxième image par rapport à la première
       \param largeur : (int) : largeur de l'image finale
       \param hauteur : (int) : hauteur de l'image finale
       \param image1 : (image): première image
       \param image2 : (image): deuxième image 
       \return 
               
       \remarks 

*/
int** fusionCas1(ListePoints* decalage, int largeur, int hauteur, Image image1, Image image2);

/*!
       \fn int** fusionCas2(ListePoints* decalage, int largeur, int hauteur, Image image1, Image image2)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Wed 18 Dec 2013
       \brief Fusionne 2 images quand le décalage en x est positif et quand celui en y est négatif
        \param decalage : (listepoints*) : décalage de la deuxième image par rapport à la première
       \param largeur : (int) : largeur de l'image finale
       \param hauteur : (int) : hauteur de l'image finale
       \param image1 : (image): première image
       \param image2 : (image): deuxième image   
       \return 
               
       \remarks 

*/
int** fusionCas2(ListePoints* decalage, int largeur, int hauteur, Image image1, Image image2);

/*!
       \fn int** fusionCas3(ListePoints* decalage, int largeur, int hauteur, Image image1, Image image2)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Wed 18 Dec 2013
       \brief Fusionne 2 images quand le décalage en x est négatif et quand celui en y est positif
        \param decalage : (listepoints*) : décalage de la deuxième image par rapport à la première
       \param largeur : (int) : largeur de l'image finale
       \param hauteur : (int) : hauteur de l'image finale
       \param image1 : (image): première image
       \param image2 : (image): deuxième image   
       \return 
               
       \remarks 

*/

int** fusion(ListePoints* decalage, int largeur, int hauteur, Image image1, Image image2);

/*!
       \fn Image imageCollee(Image image1, Image image2, ListePoints* decalage)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Wed 18 Dec 2013
       \brief Cette fonction crée l'image qui résulte de la fusion entre les deux images               
       \param image1 : (image)
       \param image2 : (image) 
       \param decalage : (listepoints*) : décalage de l'image2 par rapport à l'image1
       \return une image 
               
       \remarks 

*/
Image imageCollee(Image image1, Image image2, ListePoints* decalage);



#endif /* __COLLERIMAGES_H__ */
