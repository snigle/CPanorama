#ifndef __COMPARAISON_H__
#define __COMPARAISON_H__



#include <stdlib.h>
#include <time.h>
#include <math.h>


#include "header.h"
#include "gestionFichier.h"
#include "gestionListeCoordonnees.h"
#include "harris.h"

/*!
       \fn ListePoints PointsRandom(ListePoints* Harris)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Mon 25 Nov 2013
       \brief Renvoie un tableau de 3 random        
       \param harris : (listepoints*) 
       \param image : (image) 
       \return 
               
       \remarks 

*/
 ListePoints* pointsRandom(ListePoints* Harris);
 
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
 
 	

#endif /* __COMPARAISON_H__ */
