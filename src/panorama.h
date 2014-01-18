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
#include "histogramme.h"

#include "gestionFichier.h"
#include "rgbToGrayscale.h"

#include "gestionListeCoordonnees.h"
#include "comparaison2.h"

#include "convolution.h"
#include "binaire.h"
#include "collerImages.h"
#include "erodeDilate.h"


/*! \struct Decalage  
	\author Perales Quentin <peralesque@eisti.eu>
 *  \version 0.1
 *  \date  Mon 23 Sep 2013
 *
 *  \brief décalage d'une image par rapport à une autre.
 	
 	ListePoint valeur : Les coordonnées du décalage
	int positionImage : numéro de l'image relative
	int direction : position de l'image relative (HAUT BAS GAUCHE DROITE)
	int cylindre : si vaut 1, l'image relative est cylindrique et 0 sinon
 *
 *
 */
typedef struct Decalage
{
	ListePoints valeur;
	int positionImage;
	int direction;
	int cylindre;
} Decalage;



/*!
       \fn void afficherDecalage(Decalage decalage)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Fri 17 Jan 2014
       \brief permet d'afficher un décalage               
       \param decalage : (decalage) : le décalage 
               
       \remarks 

*/
void afficherDecalage(Decalage decalage);
/*!
       \fn void calculerTousLesDecalageBis(int image1, int cylindre, int direction, int image2, Image*** tab, Decalage* result)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Fri 17 Jan 2014
       \brief SOus partie de la fonction calculerTousLesDecalage               
       \param image1 : (int) 
       \param cylindre : (int) : =1 si l'image est cylindrique, 0 sinon
       \param direction : (int) :  la direction dans laquelle on compare
       \param image2 : (int) : 
       \param tab : (image***) : 
       \param result : (decalage*) : Liste des décalages 
       
               
       \remarks 

*/
void calculerTousLesDecalageBis(int image1, int cylindre, int direction, int image2, Image*** tab,  Decalage* result);

/*!
       \fn Decalage* calculerTousLesDecalage(Image*** tab, int** decalageAPasCalculer, int nombreImage)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Fri 17 Jan 2014
       \brief permet de calculer les décalages entre les points  clefs correspondants de plusieurs images            
       \param tab : (image***) : tableau de tableaux d'images
       \param decalageapascalculer : (int**) : 
       \param nombreimage : (int) : nombre d'images où on veut calculer des décalages
       \return 
               
       \remarks 

*/
Decalage* calculerTousLesDecalage(Image*** tab, int** decalageAPasCalculer, int nombreImage);

/*!
       \fn Image coupeHorizontale(Image image, int direction)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Fri 17 Jan 2014
       \brief coupe l'image de manière horyzontale               
       \param image : (image) 
       \param direction : (int) : Permet de choisir si on garde l'image de droite ou de gauche 
       \return L'image de droite ou de gauche
               
       \remarks 

*/
Image coupeHorizontale(Image image, int direction);

/*!
       \fn Image coupeVerticale(Image image, int direction)
       \author Poussou Elie <poussoueli@eisti.eu>
       \date Fri 17 Jan 2014
       \brief coupe l'image en deux parties                
       \param image : (image) : image à couper 
       \param direction : (int) : Permet de choisir si on garde l'image du haut ou du bas
       \return l'image gardée 
               
       \remarks 

*/
Image coupeVerticale(Image image, int direction);


void calculerTousLesDecalageBisBis(Image*** tab, int** decalageAPasCalculer, int nombreImage, int* tropDePoins, int l, int i, int j, Decalage* result, int* bool_erreur);


Image coupe(Image image, int direction);

int compterVoisins(int x, int y, Image image);

void enleverPointImage(Image image);

Image applicationBinaire(Image image, int toDo, int* bool_erreur);

int compterPointsBlanc(Image image);

ListePoints* recuperationPixelsBlanc(Image image);

void transformationCoordonnee(int* x, int* y, Image image, int i, int j);

int** transformationCylidrique(Image image);

void transformationCylidriqueBis(Image image);

void recopieDesPoints(Image image, int** newTeinte);



/*!
       \fn Image couleurVersDilatation(Image image, int bool_erreur)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Sat 18 Jan 2014
       \brief permet de prendre une image couleur et de la transformer en image premtte a être dilatée s'il y a trop de points clés               
       \param image : (image) une image couleur
       \param bool_erreur : (int*) un booléen pour savoir si une erreur apparait au cours des executions
       \return une image en noir et blanc
               
       \remarks 

*/
Image couleurVersDilatation(Image image, int* bool_erreur);

/*!
       \fn Image copieImage(Image image)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Sat 18 Jan 2014
       \brief permet de copier l'image "image"               
       \param image : (image) l image a dupliquer
       \return une image
               
       \remarks 

*/
Image copieImage(Image image);

/*!
       \fn int ** creationFiltre(void)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Sat 18 Jan 2014
       \brief permet de créer un filtre de Sobel        
       \return un tableau 3x3
               
       \remarks 

*/
int** creationFiltre(void);

/*void egalisationImages (Image image1, Image image2, int* bool_erreur);*/

/*!
       \fn int imageAvecMeilleurDecalage(Decalage* decalages, int nombreImage)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Sat 18 Jan 2014
       \brief permet de recupérer le meilleur decalage d une image avec celle testée
                      
       \param decalages : (decalage*) un tableau de décalage
       \param nombreimage : (int) le nombre d image testé
       \return retourne un entier
               
       \remarks 

*/
int imageAvecMeilleurDecalage(Decalage* decalages, int nombreImage);

/*!
       \fn Image creerTemporaire(Image origine, int* bool_erreur)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Sat 18 Jan 2014
       \brief permet de passer d une image en couleur a une image en noir et blanc grace à couleurVersDilatation. De plus, on affine notre sélection des points clés               
       \param origine : (image) l'image en couleur d origine
       \param cylindre : (int) un booléen
       \param bool_erreur : (int*) un booléen pour savoir si une erreur apparait au cours des executions
       \return une image en noir et blanc
               
       \remarks 

*/
Image creerTemporaire(Image origine, int* bool_erreur);

/*!
       \fn void libererTableauImages2(Image** tabImage, int nbImage)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Sat 18 Jan 2014
       \brief libere le tableau d image en noir et blanc(celui qui contient les points clés de toutes les images               
       \param tabimage : (image**) le tableau d image en noir et blanc
       \param nbimage : (int) le nombre d image de base a liberer
       
               
       \remarks 

*/
void libererTableauImages2(Image** tabImage, int nbImage);

/*!
       \fn int** genererTableauDecalageAPasCalculer(int nombreImage)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Sat 18 Jan 2014
       \brief créer pour chaque image quatres pointeurs vers un entier qui symbolisera la direction du découpage (haut bas gauche droite)               
       \param nombreimage : (int) le nombre d'image que le programme doit gérer
       \return un tableau deux dimensions
               
       \remarks 

*/
int** genererTableauDecalageAPasCalculer(int nombreImage);

/*!
       \fn Image collerToutesLesImages(Decalage* decalages, Image* tableauImageCouleur, int nombreImage)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Sat 18 Jan 2014
       \brief permet de coller toutes les images               
       \param decalages : (decalage*) le tableau des décalages
       \param tableauimagecouleur : (image*) le tableau d'image de couleur a coller
       \param nombreimage : (int) le nombre d image a coller
       \return une image qui constituera l image finale du programme
               
       \remarks 

*/
Image collerToutesLesImages(Decalage* decalages, Image* tableauImageCouleur, int nombreImage);

/*!
       \fn Image* creationTableauImageCouleur(char** imageOrigine, int nombreImageOrigine, int* bool_erreur)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Sat 18 Jan 2014
       \brief permet de charger toutes les images saisies par l utilisateur dans un tableau               
       \param imageorigine : (char**) le noms des images a charger
       \param nombreimageorigine : (int) le nombre d image a charger
       \param bool_erreur : (int*) un booléen pour savoir si une erreur apparait au cours des executions
       \return un tableau d'image en couleur
               
       \remarks 

*/
Image* creationTableauImageCouleur(char** imageOrigine, int nombreImageOrigine, int* bool_erreur);

/*!
       \fn Image*** creerTableauCoupe(Image** imageTemporaires, int nombreImage, int* bool_erreur)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Sat 18 Jan 2014
       \brief permet de découper chaque image en 4 (haut bas gauche droite) et de créer une image par découpe               
       \param imagetemporaires : (image**) les images en noir et blanc, remplie de points clés
       \param nombreimage : (int) le nombre d'image a traiter
       \param bool_erreur : (int*) un booléen pour savoir si une erreur apparait au cours des executions
       \return un pointeur de pointeur de pointeur d'image contenant les points clés
               
       \remarks 

*/
Image*** creerTableauCoupe(Image** imageTemporaires, int nombreImage, int* bool_erreur);

/*!
       \fn void libererTableauImages(Image* tabImage, int nbImage)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Sat 18 Jan 2014
       \brief permet de liberer le tableau d image               
       \param tabImage : (Image*) le tableau d image a liberer
       \param nbimage : (int) le nombre d image a liberer
       
               
       \remarks 

*/
void libererTableauImages(Image* tabImage, int nbImage);

/*!
       \fn ListePoints* initialisationTableauOrigine(Image* tableauImageCouleur, Decalage* decalages, int nombreImage)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Sat 18 Jan 2014
       \brief permet de "bomber" les image du tableau si le decalage est connu grace a un decalage d une image "bombée"               
       \param tableauimagecouleur : (image*) le tableau d image en couleur qu il faut assembler
       \param decalages : (decalage*) la liste des décalages
       \param nombreimage : (int) le nombre d image du tableau
       \return la liste des décalages image par image
               
       \remarks 

*/
ListePoints* initialisationTableauOrigine(Image* tableauImageCouleur, Decalage* decalages, int nombreImage);

/*!
       \fn void nouvellesOrigines(Decalage* decalages, ListePoints origine, int i)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Sat 18 Jan 2014
       \brief permet de savoir le décalage d'une image apres que cette image soit issue d'un premier collage               
       \param decalages : (decalage*) le decalage entre une image de base et celle à coller
       \param origine : (listepoints) 
       \param i : (int) 
       
               
       \remarks 

*/
void nouvellesOrigines(Decalage* decalages, ListePoints* origine, int i);

/*!
       \fn int recupererImagePlusGrande(Image* tableauImageCouleur, int nombreImage)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Sat 18 Jan 2014
       \brief permet de récupérer l'image avec la longueur et la hauteur la plus grande               
       \param tableauimagecouleur : (image*) le tableau des images du panorama
       \param nombreimage : (int) le nombre d'image
       \return le numéro de l image la plus grande
               
       \remarks 

*/
int recupererImagePlusGrande(Image* tableauImageCouleur, int nombreImage);

/*!
       \fn Image traitementPanorama(Image* tableauImagesCouleur, int nombreInput, int* bool_erreur)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Sat 18 Jan 2014
       \brief enchaine les étapes qui vont permettre de créer le panorama               
       \param tableauimagescouleur : (image*) le tableau des images couleurs
       \param nombreinput : (int) le nombre de photo
       \param bool_erreur : (int*) un booleen qui permet de savoir si le proramme genere un erreur
       \return renvoie l'image finale
               
       \remarks 

*/
Image traitementPanorama(Image* tableauImagesCouleur, int nombreInput, int* bool_erreur);

/*!
       \fn Image** creationTableauImageTemporaire(Image* imageOrigine, int nombreImageOrigine, int* bool_erreur)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Sat 18 Jan 2014
       \brief créée un tableau d image en noir et blanc qui constitue les pointes cléés              
       \param imageorigine : (image*) le tableau d image couleur
       \param nombreimageorigine : (int) le nombre d image dans le tableau
       \param bool_erreur : (int*) un booleen qui permet de savoir si le proramme genere un erreur
       \return retourne un tableau d'image en noir et blanc qui contient les points clés
               
       \remarks 

*/
Image** creationTableauImageTemporaire(Image* imageOrigine, int nombreImageOrigine, int* bool_erreur);

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
