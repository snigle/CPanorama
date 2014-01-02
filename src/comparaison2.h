#ifndef __COMPARAISON2_H__
#define __COMPARAISON2_H__


#include <stdlib.h>
#include <time.h>
#include <math.h>


#include "header.h"
#include "gestionFichier.h"
#include "gestionListeCoordonnees.h"
#include "harris.h"
#include "zncc.h"

ListePoints* vecteur(ListePoints* pointA,ListePoints* pointB );
int pasDansTableau(ListePoints** tab, int taille, ListePoints* point);
void creerListePointsProche(ListePoints* tete, ListePoints* liste, int n);
ListePoints* reduireListe(ListePoints* liste, int n, int distance, int* bool_erreur);
ListePoints* comparerVecteurs(ListePoints** tableauPoints,int tailleTableau, ListePoints* liste2, Image image2);
ListePoints** tableauPointsAutour(ListePoints* point1, ListePoints* liste1, int n, int* bool_erreur);
ListePoints comparer(ListePoints* liste1, ListePoints* liste2, Image image2, int* bool_erreur);

#endif /* __COMPARAISON2_H__ */

