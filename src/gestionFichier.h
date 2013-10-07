#ifndef __GESTIONFICHIER_H__
#define __GESTIONFICHIER_H__

	

#include "header.h"
#include <dirent.h>


char* recupererExtension(char* nom);
int recupererNbFichierRepertoire (DIR* rep);
char** listeInputDossier(DIR* rep, int taille, char* nomDossier);
char** recupererListeInputDossier(char* dossier, int* taille);





/*!
       \fn void allerAlaLigne(FILE* fichier)
       \author Perales Quentin <peralesque@eisti.eu>
       \date MON 23 Sep 2013
       \brief va à la ligne dans le fichier             
       \param image : (file*) : le code de l'image en pixmap
               
      		\remarks ras

*/
void allerAlaLigne (FILE* fichier);

/*!
       \fn void sauterCommentaire(FILE* fichier)
       \author Perales Quentin <peralesque@eisti.eu>
       \date MON 23 Sep 2013
       \brief déroule le fichier jusqu'a ce qu'il n'y ai plus de commentaire            
       \param fichier : (file*) : un fichier pixmap
               
      		\remarks ras

*/
void sauterCommentaire(FILE* fichier);

/*!
       \fn char* recupType(FILE* image) ;
       \author Perales Quentin <peralesque@eisti.eu>
       \date MON 23 Sep 2013
       \brief récupère le type d'une image pixmap            
       \param image : (file*) : le code de l'image en ppm
       \return Retourne la chaine de caractères correspondant au type P1 P2 ou P3       
      		\remarks ras

*/
char* recupType(FILE* image) ;

/*!
       \fn int parametrage(FILE* image)
       \author Perales Quentin <peralesque@eisti.eu>
       \date MON 23 Sep 2013
       \brief retourne une caractéristique de l'image           
       \param image : (file*) : l'image en pixmap
               
      		\remarks ras

*/
int parametrage(FILE* image);

/*!
       \fn int teinteMax(char type[3], FILE* image)
       \author Perales Quentin <peralesque@eisti.eu>
       \date MON 23 Sep 2013
       \brief récupère la teinte maximale de l'image P2 ou P3 en modèle pixmap 
       \param type : (char) : le type de l'image   
       \param image : (file*) : l'image en pixmap
       
               
      		\remarks ras

*/
int teinteMax(char* type, FILE* image);


/*!
       \fn int charToInt(char c)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Mon 07 Oct 2013
       \brief fonction qui recoit un caractère (0 ou 1) et le transforme en entier, cette fonction n'est utilisée que lorsque le type de l'image à charger est P1               
       \param c : (char) 
       \return retourne un entier, 0 ou 1, et génère une erreur si le caractère n'est pas '0' ou '1'
               
       \remarks 

*/

int charToInt(char c);


/*!
       \fn void recuperationPixels(FILE* fichier, int** tab, int largeur, int hauteur, char* type)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Mon 07 Oct 2013
       \brief Description Complète un tableau d'entiers qui correspondent aux pixels de l'image
       \return
               \param fichier : (FILE) e fichier contenant l'image à charger
               \param tab : (int**) la matrice a compléter
               \param largeur (int) : la largeur de l'image
               \param hauteur (int) : la hauteur de l'image
               \param type (char*) : une chaine de caractere contenant le type de l'image a charger
       \remarks 

*/
void recuperationPixels(FILE* fichier, int** tab, int largeur, int hauteur, char* type);

/*!
       \fn int* recupPixel(FILE* fichier, int largeur, int hauteur, char* type)
       \author Perales Quentin <peralesque@eisti.eu>
       \date MON 23 Sep 2013
       \brief Renvoie un tableau d'entier contenant l'ensemble des informations contenant l'image
       \param fichier : (file*) :  un fichier rempli d'informations
       \param largeur : (int) : la largeur de l'image
       \param hauteur : (int) : la hauteur de l'image
       \param type : (char*) : type de l'image pixmap
       \return un tableau d'entiers
       
      		\remarks ras

*/
int** recupPixel(FILE* fichier, int largeur, int hauteur, char* type);

/*!
       \fn Image chargerImage(char* nomImage)
       \author Perales Quentin <peralesque@eisti.eu>
       \date MON 23 Sep 2013
       \brief permet de sauvegarder l'image chargée
       
      		\remarks ras

*/
Image chargerImage(char* nomImage);



/*!
       \fn void ecritureFichier(Image fichier)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Thu 03 Oct 2013
       \brief permet d'ecrire toutes les infromations d'une image dans un fichier               
       \param image : (fichier) une image 
       \param fich : (FILE*) le fichier d'ecriture
               
       \remarks 

*/
void ecritureFichier(Image image, FILE* fich);

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
int save(Image image, char* output);

/*!
       \fn int chargerImage(char* input, char* output)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Mon 07 Oct 2013
       \brief fonction test qui charge une image si elle est de type P1 P2 ou P3            
       \param input : (char*) : nom de l'image à charger
       \param output : (char*) : nom du fichier de sauvegarde
       \return 
               
       \remarks 

*/
void testChargerImage(char* input, char* output);
#endif /* __GESTIONFICHIER_H__ */
