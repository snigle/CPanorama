#include "gestionFichier.h"

char* recupererExtension(char* char_nom)
{
	int int_i;
	int_i = 0;
	while (char_nom[int_i]!='.' && char_nom[int_i] != '\0')
	{
		int_i++;
	}
	if(char_nom[int_i] != '\0')
		return &char_nom[int_i+1];
	else
		return (&char_nom[int_i]);
}


int recupererNbFichierRepertoire(DIR* dir_rep)
{
	char* char_ext;
	int int_taille;
	struct dirent* ent;
	int_taille = 0;

    while ((ent = readdir(dir_rep)) != NULL)
    {
		char_ext = recupererExtension(ent->d_name);
		if (!strcmp(char_ext, "ppm") || !strcmp(char_ext, "pgm") || !strcmp(char_ext, "pbm"))
     		int_taille++;
    }	
	return (int_taille);
}

char** listeInputDossier(DIR* dir_rep, int int_taille, char* char_nomDossier)
{
	char* char_ext;
	char** char_resultat;
	int int_i;
	struct dirent* ent;
	int_i = 0;
	char_resultat = mallocBis(int_taille*sizeof(char*));
	rewinddir(dir_rep);

    while ((ent = readdir(dir_rep)) != NULL)
    {
		char_ext = recupererExtension(ent->d_name);
		if (!strcmp(char_ext, "ppm") || !strcmp(char_ext, "pgm") || !strcmp(char_ext, "pbm"))
     	{
     		char_resultat[int_i] = mallocBis(sizeof(ent->d_name)+sizeof(char_nomDossier)-1);
     		sprintf(char_resultat[int_i],"%s%s",char_nomDossier,ent->d_name);
     		int_i++;
     	} 
    }
    
	return (char_resultat);
}

char** recupererListeInputDossier(char* char_dossier, int* int_taille)
{
    char** char_result;
    DIR* dir_rep;
    dir_rep = opendir(char_dossier);
    if (dir_rep != NULL)
	{
		*int_taille = recupererNbFichierRepertoire(dir_rep);
		if (*int_taille != 0)
			char_result = listeInputDossier(dir_rep, *int_taille,char_dossier);
		else
			erreur(NO_INPUT_OR_OUTPUT, EXIT);
	}else
		erreur(NO_DOSSIER, EXIT);
	closedir(dir_rep);
	return (char_result);
}





void allerAlaLigne (FILE* file_fichier){
	char char_carac;
    do 
    {
    	fscanf(file_fichier, "%c", &char_carac);
    } while (char_carac != '\n');
}

void sauterCommentaire(FILE* file_fichier)
{
	char char_carac;
	fscanf(file_fichier, "%c", &char_carac);
	if (char_carac == '\n' || char_carac == ' ' || char_carac == '\t')
	{
		sauterCommentaire(file_fichier);
	}else if (char_carac == '#' )
		{
			allerAlaLigne(file_fichier);
			sauterCommentaire(file_fichier);
		}else{
	   		fseek(file_fichier, -1, SEEK_CUR);
			 }
}

char* recupType(FILE* file_image, int* bool_erreur) 
{
	char* char_result;
	char_result = malloc(3*sizeof(char));
	sauterCommentaire(file_image);
	if(!fscanf(file_image, "%c", &char_result[0]))
		*bool_erreur = 1;
	else
		if(!fscanf(file_image, "%c", &char_result[1]))
			*bool_erreur = 1;
	char_result[2] = '\0';
	return (char_result);
}



int parametrage(FILE* file_image, int* bool_erreur)
{
	int int_result;
	int int_test;
	int_result = 0;
	sauterCommentaire(file_image);
	int_test = fscanf(file_image, "%d", &int_result);
	if (int_test != 1)
	{
		erreur(IMAGE_CORROMPUE,NO_EXIT);
		*bool_erreur = 1;
	}
    
    return (int_result);
}


int teinteMax(char* char_type, FILE* file_image, int* bool_erreur)
{
    int int_result;
    int_result = 0;
    if (!strcmp(char_type, "P2") || !strcmp(char_type, "P3"))
	{
		int_result = parametrage(file_image,bool_erreur);
	}else{
		int_result = 0;
	}
	return (int_result);
}

int charToInt(char char_c){
if (char_c == '0')
	return (0);
else
	return (1);
}

void recuperationPixelsBis(FILE* file_fichier, int** int_tab, char* str_type, int* bool_erreur, int int_i, int int_j)
{
	int int_pixel;
	int int_test; /* permet de savoir si le scanf ne génère pas d'erreur*/
	int_pixel = 0;
	int_test = 1;
	if(!*bool_erreur)
	{
		sauterCommentaire(file_fichier);
		if (!strcmp(str_type, "P2") || !strcmp(str_type,"P3")) 
			int_test = fscanf(file_fichier, "%d", &int_pixel);
		else
			int_pixel = charToInt(fgetc(file_fichier));
		if (int_test == 1)
			int_tab[int_i][int_j] = int_pixel;
		else
		{
			erreur(IMAGE_CORROMPUE,NO_EXIT);
			*bool_erreur = 1;
		}
	}
}

void recuperationPixels(FILE* file_fichier, int** int_tab, int int_largeur, int int_hauteur, char* char_type, int* bool_erreur)
{
	int int_i;
	int int_j;
	for (int_i = 0 ; int_i < int_hauteur ; int_i++)
	{
		for (int_j = 0; int_j < int_largeur; int_j += 1)
		{
			recuperationPixelsBis(file_fichier, int_tab, char_type, bool_erreur, int_i, int_j);
		}
	}
}


int** recupPixel(FILE* file_fichier, int int_largeur, int int_hauteur, char* char_type, int* bool_erreur)
{
	int** int_tab;
	if(!strcmp(char_type,"P3"))	
		int_largeur *= 3;
	int_tab = initMatrice(0,int_largeur,int_hauteur);	
	recuperationPixels(file_fichier, int_tab, int_largeur, int_hauteur, char_type, bool_erreur);
	return (int_tab);
}


void capterLesParametres(FILE* file_image, char* char_type, int* int_hauteur, int* int_largeur, int* int_teinteMaximale, int* bool_erreur)
{
	if(!*bool_erreur) 
		*int_largeur = parametrage(file_image, bool_erreur);
	if(!*bool_erreur) 
		*int_hauteur = parametrage(file_image, bool_erreur);
	if (!strcmp(char_type, "P2") || !strcmp(char_type,"P3"))
	{
		if(!*bool_erreur) *int_teinteMaximale = teinteMax(char_type, file_image, bool_erreur);
	}
}


Image chargerImage(char* char_nomImage, int* bool_erreur){
	Image image_imageCharge;
	FILE* file_image;
	char* char_type;
	int int_largeur;
	int int_hauteur;
	int int_teinteMaximale;
	int** int_teinte;
	file_image = fopen(char_nomImage, "r");
	if (file_image != NULL){
		char_type = recupType(file_image, bool_erreur);
		capterLesParametres(file_image, char_type, &int_hauteur, &int_largeur, &int_teinteMaximale, bool_erreur);
		if(!*bool_erreur) int_teinte = recupPixel(file_image, int_largeur, int_hauteur, char_type, bool_erreur);
		if(!*bool_erreur) image_imageCharge = creationImage(char_type, int_largeur, int_hauteur, int_teinteMaximale, int_teinte);
		free(char_type);
		fclose(file_image);
	}else{
		erreur(IMAGE_NO_EXISTS,NO_EXIT);
		*bool_erreur = 1;
	}
	return (image_imageCharge);	
}


void ecritureFichier(Image image_image, FILE* file_fich){
	int int_i;
	int int_j;
	int int_largeur;
	int_largeur = largeurMatriceImage (image_image);
	fprintf(file_fich,"%s\n",image_image.type);
	fprintf(file_fich,"%d\t",image_image.width);
	fprintf(file_fich,"%d\n",image_image.height);
	if (strcmp(image_image.type,"P1")){
		fprintf(file_fich,"%d\n",image_image.teinteMax);
	}
	for(int_i=0;int_i<image_image.height;int_i++)
	{
		for (int_j = 0; int_j < int_largeur; int_j += 1)
		{
			fprintf(file_fich,"%d\n",image_image.teinte[int_i][int_j]);
		}
	}
}


char* setExtention (Image image_image, char* char_output)
{
	char* result;
	result = mallocBis(sizeof(char_output)+sizeof(char)*4);
	if(!strcmp(image_image.type, "P1"))
		sprintf(result,"%s%s",char_output, ".pbm");
	else if(!strcmp(image_image.type, "P2"))
		sprintf(result,"%s%s",char_output, ".pgm");
	else
		sprintf(result,"%s%s",char_output, ".ppm");
	
/*	free(char_output);*/
	return result;
}

void save(Image image_image, char* char_output, int* bool_erreur)
{
	FILE* file_fich;
	char* char_ext;
	char_ext = "";

	if(!*bool_erreur)
	{
		char_ext = recupererExtension(char_output);
		if (!strcmp(char_ext,""))
			char_output = setExtention(image_image, char_output);

		file_fich=fopen(char_output, "w");
		if(file_fich != NULL)
		{
			ecritureFichier(image_image, file_fich);
			fclose(file_fich);
			libererImage(image_image);
		}
		else{
			*bool_erreur = 1;
			libererImage(image_image);
			erreur(ERREUR_OUTPUT,NO_EXIT);
			}
	}
}


void testChargerImage(char* char_input, char* char_output)
{
	Image image_image;
	char* char_type;
	int bool_erreur;
	bool_erreur = 0;
					printf("tute%s",char_input);fflush(stdout);
	image_image = chargerImage(char_input,&bool_erreur);
	if(!bool_erreur)
	{
						printf("tute");fflush(stdout);
		char_type = image_image.type;
		if (!strcmp(recupererExtension(char_output),""))
			sprintf(char_output,"%s.%s",char_output, recupererExtension(char_input));	
		if(!verifType(char_type))
		{
			erreur(ERREUR_TYPE, NO_EXIT);
			libererImage(image_image);
		}
		else
		{
			save(image_image, char_output,&bool_erreur);
			printf("L'image %s a été sauvegardée dans le fichier %s \n", char_input, char_output);
		}
	}
}
