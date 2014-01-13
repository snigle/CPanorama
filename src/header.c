#include "header.h"


void erreursImage (int int_numeroErreur)
{
	switch(int_numeroErreur)
	{
		case IMAGE_CORROMPUE:
			fprintf(stderr,"Le fichier image est corrompu\n");
		break;
		case IMAGE_NO_EXISTS:
			fprintf(stderr,"Le fichier image n'existe pas\n");
		break;
		case MAUVAIS_FORMAT_GRAYSCALE:
			fprintf(stderr,"L'image n'est pas adaptée. Vous devez utiliser une image en .ppm pour réaliser une image en échelle de gris\n");
		break;
		case ERREUR_TYPE:
			fprintf(stderr,"Le type de cette image n'est pas géré\n");
		break;
		default :
			fprintf(stderr,"Erreur non répertoriée\n");
		break;
	}
}


void erreurParametre(int int_numeroErreur)
{
	switch(int_numeroErreur)
	{
		case ERREUR_PARAMETRE:
			fprintf(stderr,"Les paramètres ne sont pas entrés correctement, entrez panorama -h pour plus d'informations\n");
		break;
		case NO_DOSSIER:
			fprintf(stderr,"Le dossier choisit n'existe pas\n");
		break;
		case TROP_D_OPTIONS:
			fprintf(stderr,"Le nombre d'option est limité à 50\n");
		break;
		default :
			fprintf(stderr,"Erreur non répertoriée\n");
		break;
	}
}


void erreurInputOutput(int int_numeroErreur)
{
	switch(int_numeroErreur)
	{
		case NO_INPUT_OR_OUTPUT:
			fprintf(stderr,"Il n'y a aucun fichier en input ou en output\n");
		break;
		case ERREUR_OUTPUT:
			fprintf(stderr,"Le programme n'a pas la permission d'écrire dans le fichier en output\n");
		break;
		case PAS_ASSEZ_D_INPUTS:
			fprintf(stderr,"Il manque des inputs pour effectuer toutes les options\n");
		break;
		default :
			fprintf(stderr,"Erreur non répertoriée\n");
		break;
	}
}

void autreErreurs(int int_numeroErreur)
{
switch(int_numeroErreur)
	{
		case NO_MEMORY:
			fprintf(stderr,"Il manque de l'espace mémoire pour faire un malloc\n");
		break;
		case ERREUR_FILTRE:
			fprintf(stderr,"Le filtre n'a pas pu être chargé correctement\n");
		break;
		default :
			fprintf(stderr,"Erreur non répertoriée\n");
		break;
	}
}



void erreur(int int_numeroErreur, int int_sortir)
{
	int int_result;
	int_result = 1;
	if(int_numeroErreur)
	{
		if (int_numeroErreur <= 10)
			autreErreurs(int_numeroErreur);
		else if (int_numeroErreur <= 20)
			erreursImage(int_numeroErreur);
		else if (int_numeroErreur <= 30)
			erreurInputOutput(int_numeroErreur);
		else if (int_numeroErreur <= 40)
			erreurParametre(int_numeroErreur);
			else
				fprintf(stderr,"Une erreur est survenue\n");
		if (int_sortir)
			exit(-int_result);
	}
}



void* mallocBis(size_t t_taille)
 {
 	void* result;
 	
	result = malloc(t_taille);
	if(result == NULL)
		erreur(NO_MEMORY, EXIT);
	return (result);
 }


int** initMatrice(int value, int int_largeur, int int_hauteur)
{
	int** int_int_tab;
	int i;
	int j;
	int_int_tab = mallocBis(int_hauteur * sizeof(int*));
	for (i = 0; i < int_hauteur; i += 1)
		int_int_tab[i] = mallocBis(int_largeur * sizeof(int));
	for (i = 0; i < int_hauteur; i += 1)
	{
		for (j = 0; j < int_largeur; j += 1)
		{
			int_int_tab[i][j]=value;
		}
	}
	return (int_int_tab);
}

int largeurMatriceImage (Image im_image)
{
	int int_largeur;
	if(!strcmp(im_image.type, "P3"))
		int_largeur = 3 * im_image.width;
	else
		int_largeur = im_image.width;
	return (int_largeur);
}


Image creationImage(char* str_type, int int_largeur, int int_hauteur, int int_teinteMaximale, int** int_int_pixel)
{
	Image im_newImage;
	im_newImage.type = strdup(str_type);
	im_newImage.width = int_largeur;
	im_newImage.height = int_hauteur;
	im_newImage.teinteMax = int_teinteMaximale;
	im_newImage.teinte = int_int_pixel;
	return (im_newImage);
}


void libererMatrice(void** mat, int int_hauteur)
{
	int i;
	if(mat!=NULL && int_hauteur > 0)
	{
		for(i=0;i<int_hauteur;i++)
		{
			free(mat[i]);	
		}
	
		free(mat);
	}
}

void libererImage(Image im_image)
{
	libererMatrice((void**)im_image.teinte, im_image.height);
}

int verifType(char* str_type)
{
	
	return (!((strcmp(str_type, "P1") && strcmp(str_type, "P2") && strcmp(str_type, "P3"))));
}

int testType(Image im_image, char* str_type)
{
	int int_result;
	if (strcmp(im_image.type, str_type))
	{
		erreur(ERREUR_TYPE, NO_EXIT);
		int_result = 0;
	}else
		int_result = 1;
	
	return(int_result);
}

Image*** initArbre(int nbImages)
{
	Image*** tab;
	int i;
	int j;
	tab=(Image***) mallocBis(nbImages*sizeof(Image**));
	
	for(i=0;i<nbImages;i++)
	{
		tab[i]=(Image**) mallocBis(2*sizeof(Image*));
		for(j=0;j<2;j++)
		{
			tab[i][j]=(Image*) mallocBis(4*sizeof(Image));
/*			tab[i][j][3].teinteMax=20;*/
			
/*			for(k=0;k<3;k++)*/
/*			{*/
/*				tab[i][j][k]= (Image*) malloc(sizeof(Image));*/
/*			}*/
		}
	}
	
return(tab);
}



