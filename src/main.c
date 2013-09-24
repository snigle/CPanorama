 /*! \file main.c
  *  \author Lamarche Ludovic <lamarchelu@eisti.eu>
  *  \version 0.1
  *  \date Mon 23 Sep 2013
  *
  *  \brief Projet panorama
  *
  *
  */
  
  #include "ordonanceur.h"
 #include "recuperationFichier.h"
 

 
 int main (int argc, char** argv)
 {
 	int num;
 	Image image;
 	num = 0;
 	image = chargerImage("image.ppm");
 	if (num)
 		erreur(num);
 	return 0;
 }
 
