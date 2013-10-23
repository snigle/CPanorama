/*! \file ordonanceur.h
 *  \author Lamarche Ludovic <lamarchelu@eisti.eu>
 *  \version 0.1
 *  \date Mon 23 Sep 2013
 *
 *  \brief Gère les options du programme en ligne de commande
 *
 *
 */

#ifndef __ORDONANCEUR_H__
#define __ORDONANCEUR_H__

#include "header.h" 
#include "rgbToGrayscale.h"
#include "gestionFichier.h"
#include "convolution.h"
#include "erodeDilate.h"
#include "histogramme.h"
#include "panorama.h"
#include "binaire.h"


 
 

 /*!
	*	\fn afficherManuel
	*	\author LAMARCHE Ludovic <lamarchelu@eisti.eu>
	*	\date Mon 23 Sep 2013
	*	\brief Affiche le manuel du programme en mode console
	*
	*
	*	\remarks ras
	*
*/
void afficherManuel(void);



/*!
	* \fn char* getOptionInputOutput(int input, int multiple)
	* \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
	* \date Mon 23 Sep 2013
	* \brief Renvoie l'option correspondante à input et output en fonction de si c'est multiple ou unique
	* \param input faux si vaut 0, vrai sinon
	* \param multiple faux si vaut 0, vrai sinon
	* \return smth
	*
	* \remarks ras
	*
*/
char* getOptionInputOutput(int input, int multiple);


/*!
	\fn int recuperNombreInputOutput(int argc, char** argv, int input)
	\author LAMARCHE Ludovic <lamarchelu@eisti.eu>
	\date Mon 23 Sep 2013
	\brief Calcul le nombre de fichier après l'option -li
	\param argc : nombre de paramètres
	\param argv : tableau de paramètres
	\param input : si vaut 0, on traite l'output sinon on traite l'input
	\return le nombre d'input dans la liste de paramètres	
	\remarks ras

*/
int recuperNombreInputOutput(int argc, char** argv, int input);

/*!
	\fn void remplirTableauInputOutput(int argc, char** argv, char** char_input, int taille, int bool_input)
	\author LAMARCHE Ludovic <lamarchelu@eisti.eu>
	\date Mon 23 Sep 2013
	\brief Remplie le tableau d'input ou d'output 
	\param argc : nombre de paramètres
	\param argv : tableau de paramètres
	\param input : tableau a remplir
	\param taille : taille du tableau a remplir
	\param input : si vaut 0, on traite l'output sinon on traite l'input	
	\remarks ras

*/
void remplirTableauInputOutput(int argc, char** argv, char** char_input, int taille, int bool_input);

/*!
	\fn char** recupererInputOutput(int argc, char** argv,  int bool_input, int* nombre)
	\author LAMARCHE Ludovic <lamarchelu@eisti.eu>
	\date Mon 23 Sep 2013
	\brief Génère un tableau contenant chaque fichier d'input et renvoie le nombre de fichier
	\param argc : nombre de paramètres
	\param argv : tableau de paramètres
	\param bool_input : vaut 1 si il faut créer le tableau d'input et 0 pour l'output
	\param nombre : pointeur qui contiendra le nombre d'input ou d'output
	\return le nombre de fichiers importés
		
	\remarks ras

*/
char** recupererInputOutput(int argc, char** argv,  int bool_input, int* nombre);



/*!
       \fn char** recuperDossierInput(int argc, char** argv, int* taille)
       \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
       \date mer. 16 oct. 2013
       \brief Récupère un tableau d'inputs contenue dans un dossier               
       \param argc : (int) nombre de paramètres
       \param argv : (char**) tableau de paramètres
       \param taille : (int*) pointeur sur un int libre pour stocker le nombre d'inputs
       \return retourne le tableau d'inputs et le nombre d'inputs trouvés
               
       \remarks ras

*/
char** recupererDossierInput(int argc, char** argv, int* taille);

/*!
       \fn char** associerTableauString(char** tab1, char** tab2, int taille1, int taille2)
       \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
       \date mer. 16 oct. 2013
       \brief Associe deux chaine en créant un nouvel espace mémoire               
       \param tab1 : (char**) 
       \param tab2 : (char**) 
       \param taille1 : (int) 
       \param taille2 : (int) 
       \return 
               
       \remarks 

*/
char** associerTableauString(char** tab1, char** tab2, int taille1, int taille2);

/*!
       \fn void listeTestOption(int argc, char** argv, int* i, char** input, int* idInput, int nombreInput, char** output, int* idOutput, int nombreOutput)
       \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
       \date mer. 16 oct. 2013
       \brief Effectue tout les test sur une option donnée               
       \param argc : (int) nombre de paramètres
       \param argv : (char**) tableau de paramètres
       \param i : (int*) position dans le tableau argv
       \param input : (char**) tableau d'inputs
       \param idinput : (int*) position dans le tableau d'inputs
       \param nombreinput : (int) taille du tableau d'inputs
       \param output : (char**) tableau d'output
       \param idoutput : (int*) position dans le tableau d'output
       \param nombreoutput : (int) taille du tableau d'output
       
               
       \remarks 

*/
void listeTestOption(int argc, char** argv, int* i, char** input, int* idInput, int nombreInput, char** output, int* idOutput, int nombreOutput);

/*!
	\fn int testOptionAvecParametre(char* option, int* i, int argc, char** argv)
	\author LAMARCHE Ludovic <lamarchelu@eisti.eu>
	\date Mon 30 Sep 2013
	\brief Test une option qui nécessite un paramètre		
	\param option : (char*) l'option à tester
	\param i : (int*) index qui sera incrémenté si l'option est valide
	\param argc : (int) nombre de paramètres
	\param argv : (char**) tableau de parametres
	\return Retourne 1 si l'option est valide, 0 sinon
		
	\remarks 

*/
int testOptionAvecParametre(char* option, int i, int argc, char** argv);


/*!
	\fn char* incrementerInputOutput(char** tab, int* id, int max, int bool_input)
	\author LAMARCHE Ludovic <lamarchelu@eisti.eu>
	\date Mon 07 Oct 2013
	\brief Parcourt le tableau input ou output et gère les erreurs		
	\param tab : (char**) tableau d'input ou d'output
	\param id : (int*) index en cours de tu tableau
	\param max : (int) taille du tableau
	\param bool_input : (int) vrai si c'est un output, faux sinon
	\param extension : (char*) chaine de caractère précisant l'exension de l'image à approer s'il manque un output 
	\return retourne l'id incrémenté.
		
	\remarks si on dépasse la taille du tableau d'output, on en crée un.

*/
char* incrementerInputOutput(char** tab, int* id, int max, int bool_input);

/*!
	\fn int derniereOption(int argc, char** argv)
	\author LAMARCHE Ludovic <lamarchelu@eisti.eu>
	\date Mon 07 Oct 2013
	\brief Récupère la dernière option demandée		
	\param argc : (int) nombre de paramètres
	\param argv : (char**) tableau de paramètres
	\return retourne la position de la dernière option de argv
		
	\remarks 

*/
int derniereOption(int argc, char** argv);


/*!
	\fn int appelerFonction(int argc, char** argv, char** input, int nombreInput, char** output, int nombreOutput)
	\author LAMARCHE Ludovic <lamarchelu@eisti.eu>
	\date Tue 24 Sep 2013
	\brief Appelle les fonctions correspondants aux options des paramètres		
	\param argc : (int) nombre de paramètres
	\param argv : (char**) tableau de paramètres
	\param input : (char**) tableau de fichier d'input
	\param nombreinput : (int) nombre d'input
	\param output : (char**) tableau de fichiers d'output
	\param nombreoutput : (int) nombre d'output
	\return retourne 0 si elle s'exécute correctement
		
	\remarks ras

*/
void appelerFonction(int argc, char** argv, char** input, int nombreInput, char** output, int nombreOutput);


/*!
	\fn int gererOptions(int argc, char** argv)
	\author LAMARCHE Ludovic <lamarchelu@eisti.eu>
	\date Tue 24 Sep 2013
	\brief Charge les paramètres et lance les options choisient		
	\param argc : (int) nombre de paramètres
	\param argv : (char**) tableau de parametres
	\return Retourne 0 si tout s'est bien passé
		
	\remarks ras

*/
int gererOptions(int argc, char** argv);



#endif /* __ORDONANCEUR_H__ */
