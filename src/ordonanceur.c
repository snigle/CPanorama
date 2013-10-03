/*! \file ordonanceur.c
 *  \author Lamarche Ludovic <lamarchelu@eisti.eu>
 *  \version 0.1
 *  \date Mon 23 Sep 2013
 *
 *  \brief Gère les options du programme en ligne de commande
 *
 *
 */

#include "ordonanceur.h"

 
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



char* getOptionInputOutput(int input, int multiple)
{
	char* result;
	if(input)
	{
		if(multiple)
			result = "-li";
		else
			result = "-i";
	}
	else
	{
		if(multiple)
			result = "-lo";
		else
			result = "-o";
	}
	return result;
}




int recuperNombreInputOutput(int argc, char** argv, int input)
{
	int i;
	int result;
	int stop;
	
	result = -1;
	i = 0;
	stop = 0;
	
	while(i < argc && !stop)
	{
		if(result >= 0)
		{
			if(argv[i][0]!='-')
				result++;
			else
				stop = 1;
		}
		if(!strcmp(argv[i],getOptionInputOutput(input,1)) || !strcmp(argv[i],getOptionInputOutput(input,0)))
			result = 0;
		i++;
	}
	return result;
}




void remplirTableauInputOutput(int argc, char** argv, char** char_input, int taille, int bool_input)
{
	int i;
	int trouve;
	int k;
	
	i = 0;
	trouve = 0;
	while(i < argc && !trouve)
	{
		if(!strcmp(argv[i],getOptionInputOutput(bool_input,1)) || !strcmp(argv[i],getOptionInputOutput(bool_input,0)))
			trouve = 1;
		if(trouve)
		{
			for (k = 0; k < taille; k += 1)
			{
				char_input[k] = mallocBis(sizeof(argv[i+k+1]));
				char_input[k] = argv[i+k+1];
			}
		}
		
		i++;
	}
	
} 


char** recupererInputOutput(int argc, char** argv,  int bool_input, int* nombre)
{
	char** char_input;
	
	*nombre = recuperNombreInputOutput(argc,argv,bool_input);
	if(*nombre != -1)
	{
		char_input = mallocBis(*nombre * sizeof(char*));
		remplirTableauInputOutput(argc, argv,char_input,*nombre, bool_input);
	}
	
	
	
	return char_input;
} 


int testOptionAvecParametre(char* option, int* i, int argc, char** argv)
{
	int result = 0;
	
	if(*i < argc && !strcmp(argv[*i],option))
	{
		//Si l'option n'est pas à la fin
		if( *i < argc - 1)
		{
			if(argv[*i+1][0] != '-')
			{
				result = 1;
				*i = *i + 1;
			}
			else
				erreur(ERREUR_PARAMETRE);
		}
		else
		{
			erreur(ERREUR_PARAMETRE);
		}
	}
	return result;
}

int appelerFonction(int argc, char** argv, char** input, int nombreInput, char** output, int nombreOutput)
{
	int i;
	int result;
	result = 0;
	for (i = 0; i < argc; i += 1)
	{
		if(!strcmp(argv[i],"-g"))
			result = greyScale(input[0],output[0]);
		else if(!strcmp(argv[i],"-h"))
			printf("Appel de la fonction histogram\n");
		else if(!strcmp(argv[i],"-e"))
			printf("Appel de la fonction erode\n");
		else if(!strcmp(argv[i],"-d"))
			printf("Appel de la fonction dilate\n");
		else if(testOptionAvecParametre("-b",&i,argc,argv))
			printf("Appel de la fonction theshole avec le parametre %s\n",argv[i]);
		else if(testOptionAvecParametre("-c",&i,argc,argv))
			printf("Appel de la fonction convolution avec le fichier %s\n",argv[i]);
		else if(!strcmp(argv[i],"-p"))
			printf("Appel de la fonction panorama\n");
	}
	return result;
} 



int gererOptions(int argc, char** argv)
{
	int nombreInput;
	int nombreOutput;
	int result;
	char** input;
	char** output;

	result = 0;
	input = recupererInputOutput(argc, argv, 1, &nombreInput);
	output = recupererInputOutput(argc, argv, 0, &nombreOutput);
	
	if(nombreInput>0 && nombreOutput>0)
	{
		result = appelerFonction(argc,argv,input,nombreInput,output,nombreOutput);
	}
	else
	{
		afficherManuel();
		result = NO_INPUT_OR_OUTPUT;
	}
	
	return result;
} 

