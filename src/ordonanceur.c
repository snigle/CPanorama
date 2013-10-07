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
	for (i = 0; i < argc; i += 1)
	{
		if(!strcmp(argv[i],getOptionInputOutput(bool_input,1)) || !strcmp(argv[i],getOptionInputOutput(bool_input,0)))
		{
			if(trouve)
				erreur(ERREUR_PARAMETRE,EXIT);
			for (k = 0; k < taille; k += 1)
			{
				char_input[k] = strdup(argv[i+k+1]);
			}
			trouve = 1;
		}
		
	}
	
} 


char** recupererDossierInput(int argc, char** argv, int* taille)
{
	int i;
	char** result;
	int trouve;
	trouve = 0;
	result = NULL;
	
	for (i = 0; i < argc; i += 1)
	{
		if(!strcmp(argv[i],"-r"))
		{
			if(trouve)
				erreur(ERREUR_PARAMETRE,EXIT);
			if((i+1)<argc)
			{
				result = recupererListeInputDossier(argv[i+1],taille);
				trouve = 1;
			}
		}
		
	}
	return result;
}

char** associerTableauString(char** tab1, char** tab2, int taille1, int taille2)
{
	int i;
	int j;
	char** result;
	result = mallocBis(sizeof(char*)*(taille1 + taille2));
	for (i = 0; i < taille1; i += 1)
	{
		result[i] = strdup(tab1[i]);
	}
	for (j = 0; j < taille2; j += 1, i++)
	{
		result[i] = strdup(tab2[j]);
	}
	return result;
}

char** recupererInputOutput(int argc, char** argv,  int bool_input, int* nombre)
{
	char** char_input;
	char** dossier;
	char** result;
	int tmp;
	dossier = NULL;
	char_input = NULL;
	*nombre = 0;
	tmp = recuperNombreInputOutput(argc,argv,bool_input);
	if(tmp != -1)
	{
		char_input = mallocBis(tmp * sizeof(char*));
		remplirTableauInputOutput(argc, argv,char_input,tmp, bool_input);
	}
	else
		tmp = 0;
	if(bool_input)
		dossier = recupererDossierInput(argc,argv,nombre);
	result = associerTableauString(dossier,char_input,*nombre, tmp);
	//if (tmp) libererMatrice(char_input,tmp);
	//if(*nombre) libererMatrice(dossier,*nombre);
	*nombre = *nombre + tmp;
	return result;
} 

//Vérifie si le paramètre suivant n'est pas une option
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
				erreur(ERREUR_PARAMETRE, EXIT);
		}
		else
		{
			erreur(ERREUR_PARAMETRE, EXIT);
		}
	}
	return result;
}


char* incrementerInputOutput(char** tab, int* id, int max, int bool_input)
{
	char* result;
	if(*id < max)
		result = tab[*id];
	else if(!bool_input)
	{
		if(*id < 100)
		{
			result = mallocBis(sizeof(char) * 11);
			sprintf(result,"output_%d",*id);
		}
		else
			erreur(TROP_D_OPTIONS, EXIT);		
	}
	else
		erreur(PAS_ASSEZ_D_INPUTS, EXIT);
	*id = *id + 1;
	return result;
}


int derniereOption(int argc, char** argv)
{
	argc--;
	while(argc > 0 && (argv[argc][0]!='-' || !strcmp(argv[argc],"-r") || !strcmp(argv[argc],"-i") || !strcmp(argv[argc],"-o")|| !strcmp(argv[argc],"-lo") || !strcmp(argv[argc],"-li")))
		argc--;
	return argc;
}


void listeTestOption(int argc, char** argv, int* i, char** input, int* idInput, int nombreInput, char** output, int* idOutput, int nombreOutput)
{
	if(!strcmp(argv[*i],"-g"))
		erreur(grayScale(incrementerInputOutput(input,idInput,nombreInput,1),incrementerInputOutput(output,idOutput,nombreOutput,0)), NO_EXIT);
	else if(!strcmp(argv[*i],"-h"))
		printf("Appel de la fonction histogram\n");
	else if(!strcmp(argv[*i],"-e"))
		printf("Appel de la fonction erode\n");
	else if(!strcmp(argv[*i],"-d"))
		printf("Appel de la fonction dilate\n");
	else if(testOptionAvecParametre("-b",i,argc,argv))
		printf("Appel de la fonction theshole avec le parametre %s\n",argv[*i]);
	else if(testOptionAvecParametre("-c",i,argc,argv))
		printf("Appel de la fonction convolution avec le fichier %s\n",argv[*i]);
	else if(!strcmp(argv[*i],"-p"))
		printf("Appel de la fonction panorama\n");
	else if(!strcmp(argv[*i],"-s"))
		testChargerImage(incrementerInputOutput(input,idInput,nombreInput,1),incrementerInputOutput(output,idOutput,nombreOutput,0));
	
}

void appelerFonction(int argc, char** argv, char** input, int nombreInput, char** output, int nombreOutput)
{
	int i;
	int tmp; //Pour prévenir du cas où la dernière option ne fait rien
	int idInput;
	int idOutput;

	for (i = 0, idInput = 0, idOutput = 0; i < argc; i += 1)
	{
		listeTestOption(argc,argv,&i,input,&idInput,nombreInput,output,&idOutput,nombreOutput);
	}
	tmp = 0;
	i = derniereOption(argc,argv);
	while (idInput < nombreInput)
	{	
		if(tmp == idInput)
			idInput++;
		tmp = idInput;
		listeTestOption(argc,argv,&i,input,&idInput,nombreInput,output,&idOutput,nombreOutput);	
	}
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

	if(nombreInput>0)
	{
		appelerFonction(argc,argv,input,nombreInput,output,nombreOutput);
	}
	else
	{
		afficherManuel();
		result = NO_INPUT_OR_OUTPUT;
	}
	
	//libererMatrice(input,nombreInput);
	//libererMatrice(output,nombreOutput);
	
	return result;
} 

