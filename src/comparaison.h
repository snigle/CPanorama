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


ListePoints** pointsRandom(ListePoints* liste);
 
 /*!
        \fn ListePoints** Points(ListePoints* Harris)
        \author Poussou Elie <poussoueli@eisti.eu>
        \date Mon 25 Nov 2013
        \brief 	renvoie un tableau avec les coordonnées des points random                
        \param harris : (listepoints*) 
        \return 
                
        \remarks 
 
 */
ListePoints** points(ListePoints* Harris);

int vecteurX(ListePoints* liste);
int vecteurY(ListePoints* liste);
ListePoints* vecteur(ListePoints* pointA,ListePoints* pointB );
ListePoints* chercherAutour(ListePoints* liste, ListePoints* pointA, ListePoints* vect);
ListePoints comparaison(ListePoints* liste1, ListePoints* liste2, int* bool_erreur);

 
 	

#endif /* __COMPARAISON_H__ */
