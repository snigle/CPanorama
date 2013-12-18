/*! \file comparaison.h
   \author Lamarche Ludovic <lamarchelu@eisti.eu>
   \version 0.1
   \date  mer. 18 déc. 2013
 
   \brief Algo de comparaisons de points clés entre deux images
 
 
 */


#ifndef __COMPARAISON_H__
#define __COMPARAISON_H__



#include <stdlib.h>
#include <time.h>
#include <math.h>


#include "header.h"
#include "gestionFichier.h"
#include "gestionListeCoordonnees.h"
#include "harris.h"
#include "zncc.h"


int pasDansTableau(ListePoints** tab, int taille, ListePoints* point);

void creerListePointsProche(ListePoints* tete, ListePoints* liste, int n);
ListePoints* reduireListe(ListePoints* liste, int n, int distance, int* bool_erreur);

ListePoints** pointsRandom(ListePoints* liste, int n, int* bool_erreur);

ListePoints* vecteur(ListePoints* pointA,ListePoints* pointB );
ListePoints* chercherAutour(ListePoints* liste, ListePoints* pointA, ListePoints* vect);



ListePoints* chercheMotif(int* trouvePas, ListePoints* parcourtListe, ListePoints* liste2, ListePoints** ptsImage1, int n);
ListePoints* parcourtListe2(int* trouvePas, ListePoints* liste, ListePoints** tableauPoints, int n);

ListePoints comparaison(ListePoints* liste1, ListePoints* liste2, int* bool_erreur);

 
 	

#endif /* __COMPARAISON_H__ */
