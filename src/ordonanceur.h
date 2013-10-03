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
int testOptionAvecParametre(char* option, int* i, int argc, char** argv);


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
int appelerFonction(int argc, char** argv, char** input, int nombreInput, char** output, int nombreOutput);


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
