/*! \file erodeDilate.h
 *  \author Lamarche Ludovic <lamarchelu@eisti.eu>
 *  \version 0.1
 *  \date  mar. 22 oct. 2013
 *
 *  \brief permet d'éroder ou de dilater une image
 *
 *
 */


#ifndef __ERODEDILATE_H__
#define __ERODEDILATE_H__

#include "header.h"
#include "gestionFichier.h"

/*!
       \fn int estUnObjet(int i, int j, Image image, int erode)
       \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
       \date mar. 22 oct. 2013
       \brief Vérifie si le pixel est un object pixel               
       \param i : (int) hauteur du pixel
       \param j : (int) largeur du pixel
       \param image : (image) image à traiter
       \return 1 si c'est un objet pixel et 0 sinon
               
       \remarks voir http://homepages.inf.ed.ac.uk/rbf/BOOKS/VERNON/Chap004.pdf p.66 pour l'explication de l'objet pixel

*/
int estUnObjet(int i, int j, Image image);

/*!
       \fn void ajouterObjet(int hauteur, int largeur, int** matrice, Image image)
       \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
       \date mar. 22 oct. 2013
       \brief Copie l'objet pixel de image dans la matrice               
       \param hauteur : (int) hauteur du pixel
       \param largeur : (int) largeur du pixel
       \param matrice : (int**) matrice à remplir
       \param image : (image) image à copier
       
               
       \remarks 

*/
void ajouterObjet(int hauteur, int largeur, int** matrice, Image image);

/*!
       \fn int estDansLaMatrice(int i, int j, Image image)
       \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
       \date mar. 22 oct. 2013
       \brief Vérifie si un point est dans la matrice de image               
       \param i : (int) hauteur du point
       \param j : (int) largeur du point
       \param image : (image) image
       \return retourne 1 si le point est à l'intérieur de la matrice de l'image
               
       \remarks 

*/
int estDansLaMatrice(int i, int j, Image image);

/*!
       \fn int** genererMatriceErode(Image imageInput)
       \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
       \date mar. 22 oct. 2013
       \brief génère la matrice de l'image après érosion               
       \param imageinput : (image) image à traiter
       \return 
               
       \remarks 

*/
int** genererMatriceErode(Image imageInput);

/*!
       \fn int** genererMatriceDilate(Image imageInput)
       \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
       \date mar. 22 oct. 2013
       \brief génère la matrice de l'image après dilatation               
       \param imageinput : (image) image à traiter
       \return 
               
       \remarks 

*/
int** genererMatriceDilate(Image imageInput);


/*!
       \fn int erode(char* input, char* output)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Tue 08 Oct 2013
       \brief erode l'image               
       \param input : (char*) fichier en entré
       \param ouput : (char*) fichier en sortie
       \return un entier pour savoir comment s'est déroulé le programme
  
       \remarks 

*/
int erode (char* input, char* output);

/*!
       \fn int dilate(char* input, char* output)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Tue 08 Oct 2013
       \brief dilate l'image               
       \param input : (char*) fichier en entré
       \param ouput : (char*) fichier en sortie
       \return un entier pour savoir comment s'est déroulé le programme
  
       \remarks 

*/
int dilate (char* input, char* output);

#endif /* __ERODEDILATE_H__ */

