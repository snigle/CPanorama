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
#include "zncc.h"
#include "convolution.h"
#include "binaire.h"
#include "collerImages.h"
#include "erodeDilate.h"

int compterVoisins(int x, int y, Image image);

void enleverPointImage(Image image, int droite);

Image applicationBinaire(Image image, int toDo, int* bool_erreur);

ListePoints* recuperationPixelsBlanc(Image image);

void transformationCoordonnee(int* x, int* y, Image image, int i, int j);

int** transformationCylidrique(Image image);

void recopieDesPoints(Image image, int** newTeinte);

ListePoints* recuperationPointsCle (Image image1, Image image2, int* bool_erreur);

Image couleurVersDilatation(Image image, int* bool_erreur);

Image copieImage(Image image);

int** creationFiltre(void);

void egalisationImages (Image image1, Image image2, int* bool_erreur);

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
