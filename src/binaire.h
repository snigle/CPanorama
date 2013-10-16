/*! \file  binaire.h
	\author Poussou Elie poussoueli@eisti.eu
	\date Wed 16 Oct 2013
	
	\brief Génère un fichier en binaire à partir d'un ppm                                   
	

*/
	
	
	
 
#ifndef __BINAIRE_H__
#define __BINAIRE_H__
#include "header.h"

/*!
       \fn int binaire(char* input, char* output, int seuil)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Wed 16 Oct 2013
       \brief Description               
       \param input : (char*) fichier d'entrée  
       \param output : (char*) ficier de sortie
       \param seuil : (int) Seuil
       \return 0 si le traitement a été effectué
               
       \remarks 

*/
int binaire(char* input, char* output, int seuil);

#endif /* __BINAIRE_H__ */

