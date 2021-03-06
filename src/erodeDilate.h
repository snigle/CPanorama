/*!\file erodeDilate.h
 	\author Perales Quentin <peralesque@eisti.eu>
 	\version 0.1
 	\date  Tue 08 Oct 2013
 
 	\brief permet d'eroder l'image choisit
 
 
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
int estUnObjet(int i, int j, Image im_image);

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
void ajouterObjet(int int_hauteur, int int_largeur, int** matInt_matrice, Image im_image);

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
int estDansLaMatrice(int i, int j, Image im_image);

/*!
       \fn int** genererMatriceErode(Image imageInput)
       \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
       \date mar. 22 oct. 2013
       \brief génère la matrice de l'image après érosion               
       \param imageinput : (image) image à traiter
       \return 
               
       \remarks 

*/
int** genererMatriceErode(Image im_imageInput);

/*!
       \fn int** genererMatriceDilate(Image imageInput)
       \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
       \date mar. 22 oct. 2013
       \brief génère la matrice de l'image après dilatation               
       \param imageinput : (image) image à traiter
       \return 
               
       \remarks 

*/
int** genererMatriceDilate(Image im_imageInput);


/*!
       \fn Image erode (char* input, char* output, int bool_save, int* bool_erreur)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Tue 08 Oct 2013
       \brief erode l'image               
       \param input : (char*) fichier en entré
       \param ouput : (char*) fichier en sortie
       \param bool_save : si vaut 1 on affiche un message de sauvegarde pour l'utilisateur
       \param bool_erreur : adresse pour stocker un int, on lui donnera 1 si il y a une erreur dans la fonction
       \return l'image modifiée si !bool_save
  
       \remarks 

*/
Image erode (char* str_input, char* str_output, int bool_save, int* bool_erreur);

/*!
       \fn int dilate(char* input, char* output)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Tue 08 Oct 2013
       \brief dilate l'image               
       \param input : (char*) fichier en entré
       \param ouput : (char*) fichier en sortie
       \param bool_save : si vaut 1 on affiche un message de sauvegarde pour l'utilisateur
       \param bool_erreur : adresse pour stocker un int, on lui donnera 1 si il y a une erreur dans la fonction
       \return l'image modifiée si !bool_save
  
       \remarks 

*/
Image dilate (char* str_input, char* str_output, int bool_save, int* bool_erreur);

#endif /* __ERODEDILATE_H__ */

