/*! \file binaire.h
 *  \author Lamarche Ludovic <lamarchelu@eisti.eu>
 *  \version 0.1
 *  \date Tue 08 Oct 2013
 *
 *  \brief Génère un fichier en binaire à partir d'un ppm
 *
 *
 */
 
#ifndef __BINAIRE_H__
#define __BINAIRE_H__

/*!
	\fn int binaire(char* input, char* output, int seuil)
	\author LAMARCHE Ludovic <lamarchelu@eisti.eu>
	\date Tue 08 Oct 2013
	\brief Génère le binaire de l'output à partir du seuil		
	\param input : (char*) nom de l'input
	\param output : (char*) nom de l'output
	\param seuil : (int) seuil de conversion
	\return 
		
	\remarks ras

*/
int binaire(char* input, char* output, int seuil);

#endif /* __BINAIRE_H__ */

