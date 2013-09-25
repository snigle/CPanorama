/*! \file ordonanceur.h
 *  \author Lamarche Ludovic <lamarchelu@eisti.eu>
 *  \version 0.1
 *  \date Mon 23 Sep 2013
 *
 *  \brief Gère les options du programme en ligne de commande
 *
 *
 */
 
 
void afficherManuel(void);
char* getOptionInputOutput(int input, int multiple);
int recuperNombreInputOutput(int argc, char** argv, int input);
void remplirTableauInputOutput(int argc, char** argv, char** char_input, int taille, int bool_input);
char** recupererInputOutput(int argc, char** argv,  int bool_input, int* nombre);

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


