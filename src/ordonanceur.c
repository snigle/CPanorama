

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
	printf("\tUsing bool_multiple files\n");
	printf("\t\t-li file1, file2, ..., filen Define a set of files as the input\n");
	printf("\t\t-lo file1, file2, ..., filen Define a set of files as the output\n");
	printf("\t\t-r dir Search a list of input in the directory\n");
} 



char* getOptionInputOutput(int bool_input, int bool_multiple)
{
	char* str_result;
	if(bool_input)
	{
		if(bool_multiple)
			str_result = "-li";
		else
			str_result = "-i";
	}
	else
	{
		if(bool_multiple)
			str_result = "-lo";
		else
			str_result = "-o";
	}
	return str_result;
}




int recuperNombreInputOutput(int argc, char** argv, int bool_input)
{
	int i;
	int int_result;
	int stop;
	
	int_result = -1;
	i = 0;
	stop = 0;
	
	while(i < argc && !stop)
	{
		if(int_result >= 0)
		{
			if(argv[i][0]!='-')
				int_result++;
			else
				stop = 1;
		}
		if(!strcmp(argv[i],getOptionInputOutput(bool_input,1)) || !strcmp(argv[i],getOptionInputOutput(bool_input,0)))
			int_result = 0;
		i++;
	}
	return int_result;
}




void remplirTableauInputOutput(int argc, char** argv, char** char_input, int taille, int bool_input)
{
	int i;
	int bool_trouve;
	int k;
	
	i = 0;
	bool_trouve = 0;
	for (i = 0; i < argc; i += 1)
	{
		if(!strcmp(argv[i],getOptionInputOutput(bool_input,1)) || !strcmp(argv[i],getOptionInputOutput(bool_input,0)))
		{
			if(bool_trouve)
				erreur(ERREUR_PARAMETRE, EXIT);
			for (k = 0; k < taille; k += 1)
			{
				char_input[k] = strdup(argv[i+k+1]);
			}
			bool_trouve = 1;
		}
		
	}
	
} 


char** recupererDossierInput(int argc, char** argv, int* pt_int_taille)
{
	int i;
	char** t_str_result;
	int bool_trouve;
	bool_trouve = 0;
	t_str_result = NULL;
	
	for (i = 0; i < argc; i += 1)
	{
		if(!strcmp(argv[i],"-r"))
		{
			if(bool_trouve)
				erreur(ERREUR_PARAMETRE,EXIT);
			if((i+1)<argc)
			{
				t_str_result = recupererListeInputDossier(argv[i+1],pt_int_taille);
				bool_trouve = 1;
			}
		}
		
	}
	return t_str_result;
}

char** associerTableauString(char** tab1, char** tab2, int taille1, int taille2)
{
	int i;
	int j;
	char** t_str_result;
	t_str_result = mallocBis(sizeof(char*)*(taille1 + taille2));
	for (i = 0; i < taille1; i += 1)
	{
		t_str_result[i] = strdup(tab1[i]);
	}
	for (j = 0; j < taille2; j += 1, i++)
	{
		t_str_result[i] = strdup(tab2[j]);
	}
	return t_str_result;
}

char** recupererInputOutput(int argc, char** argv,  int bool_input, int* pt_int_nombre)
{
	char** char_input;
	char** dossier;
	char** t_str_result;
	int tmp;
	dossier = NULL;
	char_input = NULL;
	*pt_int_nombre = 0;
	tmp = recuperNombreInputOutput(argc,argv,bool_input);
	if(tmp != -1)
	{
		char_input = mallocBis(tmp * sizeof(char*));
		remplirTableauInputOutput(argc, argv,char_input,tmp, bool_input);
	}
	else
		tmp = 0;
	if(bool_input)
		dossier = recupererDossierInput(argc,argv,pt_int_nombre);
	t_str_result = associerTableauString(dossier,char_input,*pt_int_nombre, tmp);
	libererMatrice((void**)char_input,tmp);
	libererMatrice((void**)dossier,*pt_int_nombre);
	*pt_int_nombre = *pt_int_nombre + tmp;
	return t_str_result;
} 


int testOptionAvecParametre(char* option, int i, int argc, char** argv)
{
	int int_result = 0;
	
	if(i < argc && !strcmp(argv[i],option))
	{
		
		if( i < argc - 1)
		{
			if(argv[i+1][0] != '-')
			{
				int_result = 1;
			}
			else
				erreur(ERREUR_PARAMETRE, EXIT);
		}
		else
		{
			erreur(ERREUR_PARAMETRE, EXIT);
		}
	}
	return int_result;
}


char* incrementerInputOutput(char** tab, int* id, int max, int bool_input)
{
	char* str_result;
	if(*id < max)
		str_result = tab[*id];
	else if(!bool_input)
	{
		if(*id < 100)
		{
			str_result = mallocBis(sizeof(char) * 11);
			sprintf(str_result,"output_%d",*id);
		}
		else
			erreur(TROP_D_OPTIONS, EXIT);		
	}
	else
		erreur(PAS_ASSEZ_D_INPUTS, EXIT);
	*id = *id + 1;
	return str_result;
}


int derniereOption(int argc, char** argv)
{
	argc--;
	while(argc > 0 && (argv[argc][0]!='-' || !strcmp(argv[argc],"-r") || !strcmp(argv[argc],"-i") || !strcmp(argv[argc],"-o")|| !strcmp(argv[argc],"-lo") || !strcmp(argv[argc],"-li")))
		argc--;
	return argc;
}

/*
un input un output un idInput commande

afficher la commande appellée
erreur
incremeter idInput
*/
void mauvaisParametre (char* input, char* output, char* commande)
{
	printf("** %s %s %s **\n", input, commande, output);
	erreur(ERREUR_PARAMETRE, NO_EXIT);
}


void listeTestOption(int argc, char** argv, int* i, char** input, int* idInput, int nombreInput, char** output, int* idOutput, int nombreOutput)
{
	int bool_erreur;
	bool_erreur = 0;
	if(!strcmp(argv[*i],"-g"))
		grayScale(incrementerInputOutput(input,idInput,nombreInput,1),incrementerInputOutput(output,idOutput,nombreOutput,0),1,&bool_erreur);
	else if(!strcmp(argv[*i],"--harris"))
		enregistrerHarris(incrementerInputOutput(input,idInput,nombreInput,1),incrementerInputOutput(output,idOutput,nombreOutput,0),&bool_erreur);
	else if(!strcmp(argv[*i],"-h"))
		histogramme(incrementerInputOutput(input,idInput,nombreInput,1),incrementerInputOutput(output,idOutput,nombreOutput,0),1,&bool_erreur);
	else if(!strcmp(argv[*i],"-e"))
		erode(incrementerInputOutput(input,idInput,nombreInput,1),incrementerInputOutput(output,idOutput,nombreOutput,0),1,&bool_erreur);
	else if(!strcmp(argv[*i],"-d"))
		dilate(incrementerInputOutput(input,idInput,nombreInput,1),incrementerInputOutput(output,idOutput,nombreOutput,0),1,&bool_erreur);
	else if(testOptionAvecParametre("-b",*i,argc,argv))
		binaire(incrementerInputOutput(input,idInput,nombreInput,1),incrementerInputOutput(output,idOutput,nombreOutput,0),argv[*i+1],1,&bool_erreur);
	else if(testOptionAvecParametre("-c",*i,argc,argv))
		convolution(incrementerInputOutput(input,idInput,nombreInput,1),incrementerInputOutput(output,idOutput,nombreOutput,0),argv[*i+1],1,&bool_erreur);
	else if(!strcmp(argv[*i],"-p"))
	{
		erreur(panorama(input,nombreInput,incrementerInputOutput(output,idOutput,nombreOutput,0),&bool_erreur), NO_EXIT);
		*idInput=nombreInput;
	}
	else if((*i==1 && (!strcmp(argv[*i],"-?") || !strcmp(argv[*i],"--help"))) || argc == 1)
		afficherManuel();
	else if(argv[*i][0]=='-' && !(!strcmp(argv[*i],"-li") || !strcmp(argv[*i],"-i") || !strcmp(argv[*i],"-li") || !strcmp(argv[*i],"-o") || !strcmp(argv[*i],"-lo")))
		mauvaisParametre(incrementerInputOutput(input,idInput,nombreInput,1),incrementerInputOutput(output,idOutput,nombreOutput,0),argv[*i]);
}



void appelerFonction(int argc, char** argv, char** input, int nombreInput, char** output, int nombreOutput)
{
	int i;
	int idInput;
	int idOutput;
	/*Parcourt de toute les options présente*/
	for (i = 0, idInput = 0, idOutput = 0; i < argc; i += 1)
	{
		if(argv[i][0] == '-')
		{
			listeTestOption(argc,argv,&i,input,&idInput,nombreInput,output,&idOutput,nombreOutput);
		}
	}	
	i = derniereOption(argc,argv);/*Continu de charger les inputs avec la derniere option*/
	while (idInput < nombreInput)
	{	
		if(!i)/*Si il n'y a pas d'option*/
			testChargerImage(incrementerInputOutput(input,&idInput,nombreInput,1),incrementerInputOutput(output,&idOutput,nombreOutput,0));
		else
			listeTestOption(argc,argv,&i,input,&idInput,nombreInput,output,&idOutput,nombreOutput);	
	}
} 



int gererOptions(int argc, char** argv)
{
	int nombreInput;
	int nombreOutput;
	int int_result;
	char** input;
	char** output;
	
	int_result = 0;
	input = recupererInputOutput(argc, argv, 1, &nombreInput);
	output = recupererInputOutput(argc, argv, 0, &nombreOutput);

	appelerFonction(argc,argv,input,nombreInput,output,nombreOutput);

	libererMatrice((void**)input,nombreInput);
	libererMatrice((void**)output,nombreOutput);
	return int_result;
} 

