/*! \file panorama.h
 *  \author Lamarche Ludovic <lamarchelu@eisti.eu>
 *  \version 0.1
 *  \date Tue 08 Oct 2013
 *
 *  \brief Génère un panorama
 *
 *
 */
 
#ifndef __PANORAMA_H__
#define __PANORAMA_H__
#include <math.h>

#include "header.h"
#include "histogramme.h"
#include "harris.h"
#include "gestionFichier.h"
#include "rgbToGrayscale.h"

#include "gestionListeCoordonnees.h"
#include "comparaison2.h"

#include "convolution.h"
#include "binaire.h"
#include "collerImages.h"
#include "erodeDilate.h"


/*! \struct Decalage  
	\author Perales Quentin <peralesque@eisti.eu>
 *  \version 0.1
 *  \date  Mon 23 Sep 2013
 *
 *  \brief décalage d'une image par rapport à une autre.
 	
 	ListePoint valeur : Les coordonnées du décalage
	int positionImage : numéro de l'image relative
	int direction : position de l'image relative (HAUT BAS GAUCHE DROITE)
	int cylindre : si vaut 1, l'image relative est cylindrique et 0 sinon
 *
 *
 */
typedef struct Decalage
{
	ListePoints valeur;
	int positionImage;
	int direction;
	int cylindre;
} Decalage;

/*!
       \fn void afficherDecalage(Decalage decalage)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Fri 17 Jan 2014
       \brief permet d'afficher un décalage               
       \param decalage : (decalage) : le décalage 
               
       \remarks 

*/
void afficherDecalage(Decalage decalage);
/*!
       \fn void calculerTousLesDecalageBis(int image1, int cylindre, int direction, int image2, Image*** tab, Decalage* result)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Fri 17 Jan 2014
       \brief SOus partie de la fonction calculerTousLesDecalage               
       \param image1 : (int) 
       \param cylindre : (int) : =1 si l'image est cylindrique, 0 sinon
       \param direction : (int) :  la direction dans laquelle on compare
       \param image2 : (int) : 
       \param tab : (image***) : 
       \param result : (decalage*) : Liste des décalages 
       
               
       \remarks 

*/
void calculerTousLesDecalageBis(int image1, int cylindre, int direction, int image2, Image*** tab,  Decalage* result);

/*!
       \fn Decalage* calculerTousLesDecalage(Image*** tab, int** decalageAPasCalculer, int nombreImage)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Fri 17 Jan 2014
       \brief permet de calculer les décalages entre les points  clefs correspondants de plusieurs images            
       \param tab : (image***) : tableau de tableaux d'images
       \param decalageapascalculer : (int**) : 
       \param nombreimage : (int) : nombre d'images où on veut calculer des décalages
       \return 
               
       \remarks 

*/
Decalage* calculerTousLesDecalage(Image*** tab, int** decalageAPasCalculer, int nombreImage);

/*!
       \fn Image coupeHorizontale(Image image, int direction)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Fri 17 Jan 2014
       \brief coupe l'image de manière horyzontale               
       \param image : (image) 
       \param direction : (int) : Permet de choisir si on garde l'image de droite ou de gauche 
       \return L'image de droite ou de gauche
               
       \remarks 

*/
Image coupeHorizontale(Image image, int direction);

/*!
       \fn Image coupeVerticale(Image image, int direction)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Fri 17 Jan 2014
       \brief coupe l'image en deux parties                
       \param image : (image) : image à couper 
       \param direction : (int) : Permet de choisir si on garde l'image du haut ou du bas
       \return l'image gardée 
               
       \remarks 

*/
Image coupeVerticale(Image image, int direction);

Image coupe(Image image, int direction);

int compterVoisins(int x, int y, Image image);

void enleverPointImage(Image image);

Image applicationBinaire(Image image, int toDo, int* bool_erreur);

int compterPointsBlanc(Image image);

ListePoints* recuperationPixelsBlanc(Image image);

void transformationCoordonnee(int* x, int* y, Image image, int i, int j);

int** transformationCylidrique(Image image);

void transformationCylidriqueBis(Image image);

void recopieDesPoints(Image image, int** newTeinte);

ListePoints* recuperationPointsCle (Image image1, Image image2, int* bool_erreur);

Image couleurVersDilatation(Image image, int cylindre, int* bool_erreur);

Image copieImage(Image image);

int** creationFiltre(void);

void egalisationImages (Image image1, Image image2, int* bool_erreur);

Image creerTemporaire(Image origine, int cylindre, int* bool_erreur);

void libererTableauImages2(Image** tabImage, int nbImage);

int** genererTableauDecalageAPasCalculer(int nombreImage);

void collerToutesLesImages(Decalage* decalages, Image* tableauImageCouleur, int nombreImage);

Image* creationTableauImageCouleur(char** imageOrigine, int nombreImageOrigine, int* bool_erreur);

Image*** creerTableauCoupe(Image** imageTemporaires, int nombreImage, int* bool_erreur);

void libererTableauImages(Image* tabImage, int nbImage);

ListePoints* initialisationTableauOrigine(Image* tableauImageCouleur, Decalage* decalages, int nombreImage);

void nouvellesOrigines(Decalage* decalages, ListePoints* origine, int i);

int recupererImagePlusGrande(Image* tableauImageCouleur, int nombreImage);

Image** creationTableauImageTemporaire(Image* imageOrigine, int nombreImageOrigine, int* bool_erreur);

/*!
        \fn int panorama(char** input, int nombreInput, char* output)
        \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
        \date Tue 08 Oct 2013
        \brief Génère un panorama a partir de la liste des inputs dans le fichier output                
        \param input : (char**) tableau d'inputs
        \param nombreinput : (int) taille du tableau
        \param output : (char*) nom de l'output
        \return retourne 0 si il n'y a pas d'erreur
                
        \remarks ras

*/
int panorama(char** input, int nombreInput, char* output, int* bool_erreur);

#endif /* __PANORAMA_H__ */
