/*! \file harris.h
 *  \author Lamarche Ludovic <lamarchelu@eisti.eu>
 *  \version 0.1
 *  \date  mer. 13 nov. 2013
 *
 *  \brief Traitement de harris pour récupérer les points importants
 *
 *
 */


#ifndef __HARRIS_H__
#define __HARRIS_H__

#include "header.h"
#include "gestionFichier.h"
#include "gestionListeCoordonnees.h"

/*!
       \fn int** deriveeVerticale(Image image)
       \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
       \date mer. 13 nov. 2013
       \brief Genere la dérivée verticale d'une Image             
       \param image : (image) Image à dériver
       \return retourne la matrice de la dérivée verticale de l'image
               
       \remarks ras

*/
int** deriveeVerticale(Image image);

/*!
       \fn int** deriveeHorizontale(Image image)
       \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
       \date mer. 13 nov. 2013
       \brief Genere la dérivée horizontale d'une Image             
       \param image : (image) Image à dériver
       \return retourne la matrice de la dérivée horizontale de l'image
               
       \remarks ras

*/
int** deriveeHorizontale(Image image);

/*!
       \fn int** deriveeVerticale(Image image)
       \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
       \date mer. 13 nov. 2013
       \brief Genere la dérivée d'une Image             
       \param image : (image) Image à dériver
       \return retourne la matrice de la dérivée de l'image
               
       \remarks ras

*/
int** derivee(Image image);


/*!
       \fn ListePoints* harris(char* input, int* bool_erreur)
       \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
       \date mer. 13 nov. 2013
       \brief génère la liste des points de harris               
       \param input : (char*) nom du fichier de l'image à traiter
       \param bool_erreur : (int*) vaut vrai si il y a une erreur et faux sinon
       \return une liste de points et la valeur de harris
               
       \remarks 

*/
ListePoints* harris(Image image, int* bool_erreur);

/*!
       \fn void enregistrerHarris(char* input, char* output, int* bool_erreur)
       \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
       \date ven. 22 nov. 2013
       \brief Enregistre une image binaire affichant les points de harris               
       \param input : (char*) image à traiter
       \param output : (char*) fichier a sauvegarder
       \param bool_erreur : (int*) vaut 1 si il y a une erreur 0 sinon
       
               
       \remarks 

*/
void enregistrerHarris(char* input,char* output, int* bool_erreur);
#endif /* __HARRIS_H__ */

