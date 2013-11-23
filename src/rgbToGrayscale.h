/*! \file rgbToGrayscale.h
   \author Perales Quentin <peralesque@eisti.eu>
   \version 0.1
   \date  Thu 26 Sep 2013
 
   \brief permet de passer d'une image en couleur pixmap type P3 à une image pixmap type P2
 
 
 */
 
#ifndef __RGBTOGRAYSCALE_H__
#define __RGBTOGRAYSCALE_H__

#include "gestionFichier.h"
#include "header.h"


/*!
       \fn void creationTabGrayScale(int* tabGrey, Image image)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Thu 26 Sep 2013
       \brief creation d'un tableau de pixels en noir et blanc a partir d'une image en RGB               
       \param tabgrey : (int*) un tableau vide qui se remplit de teintes de gris
       \param image : (image) une image du type PPM
       
               
       \remarks 

*/
void creationTabGrayScale(int** tabGrey, Image image);

/*!
       \fn Image creerGrayScale(Image pixRGB)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Thu 26 Sep 2013
       \brief creer une image en noir et blanc qui correspond à l'image couleur pixRGB               
       \param pixrgb : (image) une image en couleur type pixmap P3
       \return une image pixmap en type P2, qui est alors l'image en noir et blanc
               
       \remarks 

*/
Image creerGrayScale (Image pixRGB);

/*!
       \fn Image grayScale (char* input,char* output, int bool_save, int* bool_erreur);
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Thu 26 Sep 2013
       \brief recupere en parametre le nm de l'image ppm en input et le nom de l'image crée en pgm pour creer une image pgm à partir de l'image ppm correspondante               
       \param input : (char*) une chaine de caractère qui est le nom de l'image ppm existante
       \param output : (char*) une chaine correspondant au nom de l image pgm créée
       \param bool_save : si vaut 1 on affiche un message de sauvegarde pour l'utilisateur
       \param bool_erreur : adresse pour stocker un int, on lui donnera 1 si il y a une erreur dans la fonction
       \return l'image modifiée si !bool_save
               
       \remarks 

*/
Image grayScale (char* input,char* output, int bool_save, int* bool_erreur);

#endif /* __RGBTOGRAYSCALE_H__ */
