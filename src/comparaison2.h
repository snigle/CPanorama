#ifndef __COMPARAISON2_H__
#define __COMPARAISON2_H__


#include <stdlib.h>
#include <time.h>
#include <math.h>


#include "header.h"
#include "gestionFichier.h"
#include "gestionListeCoordonnees.h"

/*!
       \fn ListePoints* ajouterDecalage(ListePoints* tete, ListePoints liste, ListePoints decalage)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Fri 17 Jan 2014
       \brief permet d'ajouter des décalages à une liste de décalages existante               
       \param tete : (listepoints*) : début de la liste de décalages
       \param liste : (listepoints) : fin de la liste de décalages
       \param decalage : (listepoints) : La liste de décalages 
       \return la nouvelle liste de points
               
       \remarks 

*/

ListePoints* ajouterDecalage(ListePoints* tete, ListePoints* liste, ListePoints decalage);
/*!
       \fn ListePoints calculerDecalage(int xA, int yA, int xB, int yB)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Fri 17 Jan 2014
       \brief calcule les décalages d'une image2	               
       \param xa : (int) : coordonnées en x des points clefs dans la première image
       \param ya : (int) : coordonnées en y des points clefs dans la première image
       \param xb : (int) : coordonnées en x des points clefs dans la deuxième image
       \param yb : (int) : coordonnées en x des points clefs dans la première image
       \double valeur : (double) : valeur du décalage entre les 2 points clefs des 2 images
       \return 
               
       \remarks 

*/

ListePoints calculerDecalage(int xA, int yA, int xB, int yB, double valeur);
/*!
       \fn ListePoints* vecteur(ListePoints* pointA, LIstePoints* pointB)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Fri 17 Jan 2014
       \brief calcule le vecteur entre 2 points a ET B               
       \param pointa : (listepoints*) : point A 
       \param pointb : (listepoints*)  : point B
       \return le vecteur de type ListePoints
               
       \remarks 

*/
ListePoints* vecteur(ListePoints* pointA,ListePoints* pointB );

/*!
       \fn int pasDansTableau(ListePoints** tab, int taille, ListePoints* point)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Fri 17 Jan 2014
       \brief détermine si un point est das un tableau de points               
       \param tab : (listepoints**) : Tableau de liste de points
       \param taille : (int) : taille du tableau
       \param point : (listepoints*) : tableau à tester 
       \return : retourne 1 si le points est dans le tableau
               
       \remarks 

*/	
int pasDansTableau(ListePoints** tab, int taille, ListePoints* point);

/*!
       \fn void creerListePointsProche(ListePoint* tete, ListePoints* liste, int n)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Fri 17 Jan 2014
       \brief Description               
       \param tete : (listepoint*) 
       \param liste : (listepoints*) 
       \param n : (int) 
       
               
       \remarks 

*/
void creerListePointsProche(ListePoints* tete, ListePoints* liste, int n);

/*!
       \fn LIstePoints* comparerVecteurs(ListePoints** tableauPoints, int tailleTableau, LIstePoints* liste2, Image image2)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Fri 17 Jan 2014
       \brief Compare 2 vecturs. 1 existant et un autre que l'on calcule dans la fonction               
       \param tableaupoints : (listepoints**) : tableau de liste de points
       \param tailletableau : (int) : taille du tableau 
       \param liste2 : (listepoints*) : liste des points de l'image 2
       \param image2 : (image) : image 2 
       \return 
               
       \remarks 

*/
ListePoints* comparerVecteurs(ListePoints** tableauPoints,int tailleTableau, ListePoints* liste2, Image image2);
/*!
       \fn ListePoints** tableauPointsAutour(ListePoints* point1, ListePoints* liste1, int n, int* bool_erreur)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Fri 17 Jan 2014
       \brief Trouve les points qui sont autour d'un point clef               
       \param point1 : (listepoints*) : point central
       \param liste1 : (listepoints*) : liste des points autours
       \param n : (int) : nombre de points
       \param bool_erreur : (int*) :
       \return retourne la liste de points 
               
       \remarks 

*/
ListePoints** tableauPointsAutour(ListePoints* point1, ListePoints* liste1, int n, int* bool_erreur);

/*!
       \fn ListePoints* comparer(ListePoints* liste1, ListePoints* liste2, Image image2, int* bool_erreur)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Fri 17 Jan 2014
       \brief compare des points de deux listes.                
       \param liste1 : (listepoints*) : liste des points de la première liste
       \param liste2 : (listepoints*) : liste des points de la deuxième image
       \param image2 : (image) : image 2
       \param bool_erreur : (int*) 
       \return une liste de points
               
       \remarks 

*/
ListePoints* comparer(ListePoints* liste1, ListePoints* liste2, Image image2, int* bool_erreur);

#endif /* __COMPARAISON2_H__ */

