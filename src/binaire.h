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
       \fn int** remplirMatriceBinaire(Image im_image, int int_seuil)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Tue 22 Oct 2013
       \brief permet de remplir la matrice de 0 et de 1 pour créer une image en noi et blanc               
       \param im_image : (image) une image en teinte de gris
       \param int_seuil : (int) la valeur pour laquelle on écrit 0 si le pixel en teinte de gris est supérieur au seuil, sinon on met 1
       \return une matrice de 0 et de 1
               
       \remarks 

*/
int** remplirMatriceBinaire (Image im_image, int int_seuil);

/*!
       \fn Image binaire(char* str_input, char* str_output, char* str_valeurDeBascule, int int_bool_save, int* int_bool_erreur)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Wed 16 Oct 2013
       \brief Description               
       \param str_input : (char*) fichier d'entrée  
       \param str_output : (char*) ficier de sortie
       \param str_valeurDeBascule : (int) Seuil
       \param int_bool_save : si vaut 1 on affiche un message de sauvegarde pour l'utilisateur
       \param int_bool_erreur : adresse pour stocker un int, on lui donnera 1 si il y a une erreur dans la fonction
       \return l'image modifiée si !bool_save
               
       \remarks 

*/
Image binaire(char* str_input, char* str_output, char* str_valeurDeBascule, int int_bool_save, int* int_bool_erreur)

#endif /* __BINAIRE_H__ */

