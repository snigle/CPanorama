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
int appelerFonction(int argc, char** argv, char** input, int nombreInput, char** output, int nombreOutput);
int gererOptions(int argc, char** argv);
