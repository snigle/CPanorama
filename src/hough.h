/*! \file hough.h
 *  \author Lamarche Ludovic <lamarchelu@eisti.eu>
 *  \version 0.1
 *  \date  lun. 04 nov. 2013
 *
 *  \brief Détection des lignes de hough
 *
 *
 */


#ifndef __HOUGH_H__
#define __HOUGH_H__

#include "header.h"
#include "gestionFichier.h"
#include <math.h>

Image hough(char* input,char* output, int bool_save, int* bool_erreur);

#endif /* __HOUGH_H__ */

