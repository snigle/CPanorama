/*! \file convolution.h
 *  \author Lamarche Ludovic <lamarchelu@eisti.eu>
 *  \version 0.1
 *  \date Tue 08 Oct 2013
 *
 *  \brief Converti l'input dans l'output avec une convolution
 *
 *
 */
 
#ifndef __CONVOLUTION_H__
#define __CONVOLUTION_H__

#include "header.h"
#include "gestionFichier.h"



int** recupFiltre(FILE* filtre);
int associationPossible(int x, int y, int i, int j, int largeur, int hauteur);
int setNumber(int y, int x, int largeur, int hauteur, int** pixels, int** filtre);
int** applicationFiltre(Image image, int** filtre);
int applicationConvolution(Image image, int** filtre, char* output);
/*!
       \fn int convolution(char* input, char* output, char* fichierMatrice)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Tue 08 Oct 2013
       \brief realise la convolution d une image en fonction d'une matrice en parametre               
       \param input : (char*) fichier d'entré
       \param output : (char*) fichier de sortie
       \param fichiermatrice : (char*) fichier contenant une matrice
       \return retourne un entier qui correspond a l'avancement du programme
               
       \remarks 

*/
int convolution (char* input, char* ouput, char* fichierMatrice);

#endif /* __CONVOLUTION_H__ */

