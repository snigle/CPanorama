#ifndef __ZNCC_H__
#define __ZNCC_H__

#include "header.h"
#include "gestionListeCoordonnees.h"
#include <math.h>

double absolut(double a);
/*!
       \fn double zncc2(Image image, int x, int y, int n)
       \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
       \date lun. 25 nov. 2013
       \brief Suite du calcul de zncc               
       \param image : (image) 
       \param x : (int) largeur
       \param y : (int) hauteur
       \param n : (int) 
       \return retourne le resultat du calcul
               
       \remarks 

*/
double zncc2(Image image, int x, int y, int n);

/*!
       \fn double sigma(Image image, int x, int y, int n)
       \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
       \date lun. 25 nov. 2013
       \brief Suite du calcul de zncc               
       \param image : (image) 
       \param x : (int) largeur
       \param y : (int) hauteur
       \param n : (int) 
       \return retourne le resultat du calcul
               
       \remarks 

*/
double sigma(Image image, int x, int y, int n);



/*!
       \fn double zncc(Image image1, Image image2, int x1, int y1, int x2, int y2,n)
       \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
       \date lun. 25 nov. 2013
       \brief Renvoi l'indice zncc de deux points               
       \param image1 : (image) Image 1
       \param image2 : (image) Image 2
       \param x1 : (int) position x de l'image 1
       \param y1 : (int) position y de l'image 1
       \param x2 : (int) position x de l'image 2
       \param y2,n : (int) position y de l'image 2
       \return Renvoie l'indice zncc de deux points
               
       \remarks 

*/
double zncc(Image image1, Image image2, int x1, int y1, int x2, int y2, int n);



void calculerDecalage(ListePoints* result, int xA, int yA, int xB, int yB, double valeur);

/*!
       \fn void signerListePoint(ListePoints* liste1, Image image1, ListePoints* liste2, Image image2)
       \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
       \date lun. 25 nov. 2013
       \brief Renvoie le décalage moyen des points de zncc               
       \param liste1 : (listepoints*) liste des points de harris de l'image 1
       \param image1 : (image) Image 1
       \param liste2 : (listepoints*) liste des points de harris de l'image 2
       \param image2 : (image) Image 2
       
               
       \remarks 

*/
ListePoints decalageZNCC(ListePoints* liste1, Image image1, ListePoints* liste2, Image image2);


#endif /* __ZNCC_H__ */

