 /*! \file main.c
  *  \author Lamarche Ludovic <lamarchelu@eisti.eu>
  *  \version 0.1
  *  \date Mon 23 Sep 2013
  *
  *  \brief Projet panorama
  *
  *
  */
  
 #include <stdlib.h>
 #include <stdio.h>
 
 


/*!
	\fn afficherManuel
	\author LAMARCHE Ludovic <lamarchelu@eisti.eu>
	\date Mon 23 Sep 2013
	\brief Affiche le manuel du programme en mode console
	

		\remarks ras

*/
void afficherManuel(void)
{
	printf("PANORAMA(7)\n\nNAME\n\tpanorama - automatically create panoramas\n\n");
	printf("SYNOPSIS\n\tpanorama [OPTION]...\n\n");
	printf("DESCRIPTION\n\tImage manipulation helper to create panoram\n\n");
	printf("USAGE\n\tUsage : panorama [OPTION...]\n\n\tHelp options\n\t\t-?, --help Shows this help message\n\n");
	printf("\tGeneral Options\n");
	printf("\t\t-g Convert the input file(s) to grayscale\n");
	printf("\t\t-h Extract the histogram from the input file(s)\n");
	printf("\t\t-e Erode the input file(s)\n");
	printf("\t\t-d Dilate the input file(s)\n");
	printf("\t\t-b threshold Render a black-white image using the given threshold\n");
	printf("\t\t-c file Apply a convolution on the input file(s) using the given file as the convolution matrix\n");
	printf("\t\t-p Render the panorama from the input file(s)\n");
	printf("\tWorking on single file\n");
	printf("\t\t-i file Define the input file\n");
	printf("\t\t-o file Define the output file\n");
	printf("\tUsing multiple files\n");
	printf("\t\t-li file1, file2, ..., filen Define a set of files as the input\n");
	printf("\t\t-lo file1, file2, ..., filen Define a set of files as the output\n");
} 

/*!
	\fn gererOptions
	\author LAMARCHE Ludovic <lamarchelu@eisti.eu>
	\date Mon 23 Sep 2013
	\brief Traite les options et exécute la fonction correspondante
	
	\param	
		int argc : nombre d'options
		char** argv : pointeur correspondant à chaque options
	\return 
		
		\remarks ras

*/
int gererOptions(int argc, char** argv)
{
	int i;
	//afficherManuel();
	for (i = 0; i < argc; i += 1)
	{
		printf("%s \n",argv[i]);
	}
	
	return 0;
} 

 
 int main (int argc, char** argv)
 {
 	return gererOptions(argc, argv);
 }
 
