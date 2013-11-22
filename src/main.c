
#include "ordonanceur.h"
#include "header.h"

 

 
int main (int int_argc, char** tab_str_argv)
{
	int int_num;
	int_num = gererOptions(int_argc,tab_str_argv);
	if (int_num)
		erreur(int_num,EXIT);
	return (0);
}
 
 /* Documentation tag for Doxygen
 */

/*! \mainpage Panorama Documentation
 *
 * \section intro_sec Introduction
 *
 * Ceci est documentation du projet Panorama, vous devez d'abord le compiler et ensuite vous pouvez utiliser nos images de test.
 *
 * \section compile_sec Compilation
 *
 * Pour compiler le programme :\n
 * $make
 *
 * \subsection running Lancer le programme
 * Vous pouvez voir la liste des options à l'aide de la commande :\n
 * $./bin/panorama --help ou $./bin/panorama -?
 *\n\n
 * Pour tester le programme nous avons mis plusieurs images dans le dossier src/images/ \n
 * $./bin/panorama -i src/images/image.ppm -g -o test.pgm
 *\n\n
 * Si vous ne précisez pas de fichier en output, le programme le génèrera directement dans le dossier courrant :\n
 * $./bin/panorama -r src/images/ -g
 *\n\n
 * Les options seront exécutées successivement respectivement à l'ordre donnée dans la liste d'input. Par exemple :\n
 * $./bin/panorama -li src/images/image.ppm src/images/image.pgm -g -d
 *\n Cette commande exécute l'option -g sur le premier input et -d sur le second.
 */
 
