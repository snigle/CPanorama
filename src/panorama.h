/*! \file panorama.h
 *  \author Lamarche Ludovic <lamarchelu@eisti.eu>
 *  \version 0.1
 *  \date Tue 08 Oct 2013
 *
 *  \brief Génère un panorama
 *
 *
 */
 
#ifndef __PANORAMA_H__
#define __PANORAMA_H__
#include <math.h>

#include "header.h"
#include "harris.h"
#include "gestionListeCoordonnees.h"
#include "zncc.h"
#include "comparaison.h"

/*!
        \fn int panorama(char** input, int nombreInput, char* output)
        \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
        \date Tue 08 Oct 2013
        \brief Génère un panorama a partir de la liste des inputs dans le fichier output                
        \param input : (char**) tableau d'inputs
        \param nombreinput : (int) taille du tableau
        \param output : (char*) nom de l'output
        \return retourne 0 si il n'y a pas d'erreur
                
        \remarks ras

*/
int panorama(char** input, int nombreInput, char* output, int* bool_erreur);

#endif /* __PANORAMA_H__ */

