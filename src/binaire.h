/*! \file  binaire.h
	\author Poussou Elie poussoueli@eisti.eu
	\date Wed 16 Oct 2013
	
	\brief Génère un fichier en binaire à partir d'un ppm                                   
	

*/
	
	
	
 
#ifndef __BINAIRE_H__
#define __BINAIRE_H__
#include "header.h"
#include "gestionFichier.h"

/*!
       \fn int** remplirMatriceBinaire(Image image, int seuil)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Tue 22 Oct 2013
       \brief permet de remplir la matrice de 0 et de 1 pour créer une image en noi et blanc               
       \param image : (image) une image en teinte de gris
       \param seuil : (int) la valeur pour laquelle on écrit 0 si le pixel en teinte de gris est supérieur au seuil, sinon on met 1
       \return une matrice de 0 et de 1
               
       \remarks 

*/
int** remplirMatriceBinaire (Image image, int seuil);

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
int binaire(char* input, char* output, char* valeurDeBascule);

#endif /* __BINAIRE_H__ */

