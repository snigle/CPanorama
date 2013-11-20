/*! \file recuperationFichier.c
 *  \author Perales Quentin <peralesque@eisti.eu>
 *  \version 0.1
 *  \date  Mon 23 Sep 2013
 *
 *  \brief chargement d'une image
 *
 *
 */


#ifndef __GESTIONFICHIER_H__
#define __GESTIONFICHIER_H__

	

#include "header.h"
#include <dirent.h>

/*!
       \fn char* recupererExtension(char* nom)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Mon 07 Oct 2013
       \brief permet de recuperer l'extension d'un fichier selectionné               
       \param nom : (char*) le nom du fichier
       \return l'extension du fichier
               
       \remarks 

*/


char* recupererExtension(char* char_nom);

/*!
       \fn int recupererNbFichierRepertoire(DIR* rep)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Mon 07 Oct 2013
       \brief permet de récuperer le nombre de fichier exploitable par le programme dans un répertoire spécifié               
       \param rep : (dir*) le répertoire choisit par l'utilisateur
       \return le nombre de fichier dont l extension est .ppm .pgm ou .pbm
               
       \remarks 

*/
int recupererNbFichierRepertoire (DIR* dir_rep);

/*!
       \fn char** listeInputDossier(DIR* rep, int taille, char* nomDossier)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Mon 07 Oct 2013
       \brief permet de renvoyer un tableau de chaine de caractère constituant l'ensembles des images du dossier               
       \param rep : (dir*) le flux de fichier dans le dossier
       \param taille : (int) le nombre de fichiers exploitables
       \param nomdossier : (char*) le dossier selectionné par l'utilisateur
       \return retourne un tableau qui spécifie les fichiers a utiliser
               
       \remarks 

*/
char** listeInputDossier(DIR* dir_rep, int int_taille, char* char_nomDossier);

/*!
       \fn char** recupererListeInputDossier(char* dossier, int* taille)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Mon 07 Oct 2013
       \brief recupere le tableau des images exploitables du dossier et genere une erreur si l'opération est impossible               
       \param dossier : (char*) le nom du dossier
       \param taille : (int*) un poiteur qui permet de récuperer le nombre de paramètres ouput a créer
       \return retourne le tableau de fichiers input
               
       \remarks 

*/
char** recupererListeInputDossier(char* char_dossier, int* int_taille);


/*!
       \fn void allerAlaLigne(FILE* fichier)
       \author Perales Quentin <peralesque@eisti.eu>
       \date MON 23 Sep 2013
       \brief va à la ligne dans le fichier             
       \param image : (file*) : le code de l'image en pixmap
               
      		\remarks ras

*/
void allerAlaLigne (FILE* file_fichier);

/*!
       \fn void sauterCommentaire(FILE* fichier)
       \author Perales Quentin <peralesque@eisti.eu>
       \date MON 23 Sep 2013
       \brief déroule le fichier jusqu'a ce qu'il n'y ai plus de commentaire            
       \param fichier : (file*) : un fichier pixmap
               
      		\remarks ras

*/
void sauterCommentaire(FILE* file_fichier);

/*!
       \fn char* recupType(FILE* image, int* bool_erreur) ;
       \author Perales Quentin <peralesque@eisti.eu>
       \date MON 23 Sep 2013
       \brief récupère le type d'une image pixmap            
       \param image : (file*) : le code de l'image en ppm
       \return Retourne la chaine de caractères correspondant au type P1 P2 ou P3       
      		\remarks ras

*/
char* recupType(FILE* file_image, int* bool_erreur) ;

/*!
       \fn int parametrage(FILE* image, int* bool_erreur)
       \author Perales Quentin <peralesque@eisti.eu>
       \date MON 23 Sep 2013
       \brief retourne une caractéristique de l'image           
       \param image : (file*) : l'image en pixmap
       \param bool_erreur : pointeur à mettre à 1 si il y a une erreur
               
      		\remarks ras

*/
int parametrage(FILE* file_image, int* bool_erreur);

/*!
       \fn int teinteMax(char* type, FILE* image, int* bool_erreur)
       \author Perales Quentin <peralesque@eisti.eu>
       \date MON 23 Sep 2013
       \brief récupère la teinte maximale de l'image P2 ou P3 en modèle pixmap 
       \param type : (char*) : le type de l'image   
       \param image : (file*) : l'image en pixmap
       \param bool_erreur : pointeur à mettre à 1 si il y a une erreur
               
      		\remarks ras

*/
int teinteMax(char* char_type, FILE* file_image, int* bool_erreur);


/*!
       \fn int charToInt(char c)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Mon 07 Oct 2013
       \brief fonction qui recoit un caractère (0 ou 1) et le transforme en entier, cette fonction n'est utilisée que lorsque le type de l'image à charger est P1               
       \param c : (char) 
       \return retourne un entier, 0 ou 1, et génère une erreur si le caractère n'est pas '0' ou '1'
               
       \remarks 

*/

int charToInt(char char_c);


/*!
       \fn void recuperationPixels(FILE* fichier, int** tab, int largeur, int hauteur, char* type, int* bool_erreur)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Mon 07 Oct 2013
       \brief Description Complète un tableau d'entiers qui correspondent aux pixels de l'image
       \return
               \param fichier : (FILE) e fichier contenant l'image à charger
               \param tab : (int**) la matrice a compléter
               \param largeur (int) : la largeur de l'image
               \param hauteur (int) : la hauteur de l'image
               \param type (char*) : une chaine de caractere contenant le type de l'image a charger
               \param bool_erreur : pointeur à mettre à 1 si il y a une erreur
       \remarks 

*/
void recuperationPixels(FILE* file_fichier, int** int_tab, int int_largeur, int int_hauteur, char* char_type, int* bool_erreur);

/*!
       \fn int* recupPixel(FILE* fichier, int largeur, int hauteur, char* type, int* bool_erreur)
       \author Perales Quentin <peralesque@eisti.eu>
       \date MON 23 Sep 2013
       \brief Renvoie un tableau d'entier contenant l'ensemble des informations contenant l'image
       \param fichier : (file*) :  un fichier rempli d'informations
       \param largeur : (int) : la largeur de l'image
       \param hauteur : (int) : la hauteur de l'image
       \param type : (char*) : type de l'image pixmap
       \param bool_erreur : (int*) adresse pour stocker un int
       \return un tableau d'entiers
       
      		\remarks ras

*/
int** recupPixel(FILE* file_fichier, int int_largeur, int int_hauteur, char* char_type, int* bool_erreur);


/*!
       \fn void capterLesParametres(FILE* image, char* type, int* hauteur, int* largeur, int* teinteMaximale, int* bool_erreur)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Thu 31 Oct 2013
       \brief permet de modifier les paramètres de l'image en chargeant le fichier               
       \param image : (file*) l'image dans le fichiers
       \param type : (char*) le type de l'image
       \param hauteur : (int*) la hauteur de l'image
       \param largeur : (int*) la largeur de l'image 
       \param teintemaximale : (int*) la teinte maximale de l'image 
       \param bool_erreur : (int*) un entier qui renvoie 1 s'il y a une erreur 
       
               
       \remarks 

*/
void capterLesParametres(FILE* file_image, char* char_type, int* int_hauteur, int* int_largeur, int* int_teinteMaximale, int* bool_erreur);
/*!
       \fn Image chargerImage(char* nomImage)
       \author Perales Quentin <peralesque@eisti.eu>
       \date MON 23 Sep 2013
       \brief permet de sauvegarder l'image chargée
       \param nomImage : (char*) le nom de l'image a charger
       \param bool_erreur : (int*) adresse pour stocker un int
       \return	Retourne une image si bool_erreur est nul, sinon il faut gérer l'erreur
      		\remarks ras

*/

Image chargerImage(char* char_nomImage, int* bool_erreur);



/*!
       \fn void ecritureFichier(Image fichier)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Thu 03 Oct 2013
       \brief permet d'ecrire toutes les infromations d'une image dans un fichier               
       \param image : (fichier) une image 
       \param fich : (FILE*) le fichier d'ecriture
               
       \remarks 

*/
void ecritureFichier(Image image_image, FILE* file_fich);




/*!
       \fn void setExtention(Image image, char* output)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Wed 16 Oct 2013
       \brief permet d'ajouter l'extention au fichier de sortie si elle n'est pas précisée, en fonction du type de l'image               
       \param image : (image) l'image en question
       \param output : (char*) le nom du fichier de sortie
       
               
       \remarks 

*/
void setExtention (Image image_image, char* char_output);

/*!
       \fn int save(Image image, char* ouput)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Thu 26 Sep 2013
       \brief permet de sauvegarder l'image chargée               
       \param image : (image) : image que l'on souhaite sauvegarder
       \param ouput : (char*) : fichier de sortie
       \return 0 si l'image a été enregistrée
               
       \remarks ras

*/



void save(Image image_image, char* char_output, int* bool_erreur);

/*!
       \fn int chargerImage(char* input, char* output)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Mon 07 Oct 2013
       \brief fonction test qui charge une image si elle est de type P1 P2 ou P3            
       \param input : (char*) : nom de l'image à charger
       \param output : (char*) : nom du fichier de sauvegarde
       \param bool_erreur : Si il y a une erreur on ne fait rien mais le programme continue
               
       \remarks 

*/
void testChargerImage(char* char_input, char* char_output);
#endif /* __GESTIONFICHIER_H__ */
