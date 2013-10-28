/*! \file recuperationFichier.c
 *  \author Perales Quentin <peralesque@eisti.eu>
 *  \version 0.1
 *  \date  Mon 23 Sep 2013
 *
 *  \brief chargement d'une image
 *
 *
 */


#include "gestionFichier.h"



char* recupererExtension(char* nom)
{
	int i;
	i = 0;
	while (nom[i]!='.' && nom[i] != '\0')
	{
		i++;
	}
	if(nom[i] != '\0')
		return &nom[i+1];
	else
		return &nom[i];
}


int recupererNbFichierRepertoire(DIR* rep)
{
	char* ext;
	int taille;
	struct dirent* ent;
	taille = 0;

    while ((ent = readdir(rep)) != NULL)
    {
		ext = recupererExtension(ent->d_name);
		if (!strcmp(ext, "ppm") || !strcmp(ext, "pgm") || !strcmp(ext, "pbm"))
     		taille++;
    }	
	return taille;
}

char** listeInputDossier(DIR* rep, int taille, char* nomDossier)
{
	char* ext;
	char** resultat;
	int i;
	struct dirent* ent;
	i = 0;
	resultat = mallocBis(taille*sizeof(char*));
	rewinddir(rep);

    while ((ent = readdir(rep)) != NULL)
    {
		ext = recupererExtension(ent->d_name);
		if (!strcmp(ext, "ppm") || !strcmp(ext, "pgm") || !strcmp(ext, "pbm"))
     	{
     		resultat[i] = mallocBis(sizeof(ent->d_name)+sizeof(nomDossier)-1);
     		sprintf(resultat[i],"%s%s",nomDossier,ent->d_name);
     		i++;
     	} 
    }
    
	return resultat;
}

char** recupererListeInputDossier(char* dossier, int* taille)
{
    char** result;
    DIR* rep;
    rep = opendir(dossier);
    if (rep != NULL)
	{
		*taille = recupererNbFichierRepertoire(rep);
		if (*taille != 0)
			result = listeInputDossier(rep, *taille,dossier);
		else
			erreur(NO_INPUT_OR_OUTPUT, EXIT);
	}else
		erreur(NO_DOSSIER, EXIT);
	closedir(rep);
	return result;
}





void allerAlaLigne (FILE* fichier){
	char carac;
    do 
    {
    	fscanf(fichier, "%c", &carac);
    } while (carac != '\n');
}

void sauterCommentaire(FILE* fichier)
{
	char carac;
	fscanf(fichier, "%c", &carac);
	if (carac == '\n' || carac == ' ' || carac == '\t')
	{
		sauterCommentaire(fichier);
	}else if (carac == '#' )
		{
			allerAlaLigne(fichier);
			sauterCommentaire(fichier);
		}else{
	   		fseek(fichier, -1, SEEK_CUR);
			 }
}

char* recupType(FILE* image) 
{
	char* result;
	result = malloc(3*sizeof(char));
	sauterCommentaire(image);
	fscanf(image, "%c", &result[0]);
	fscanf(image, "%c", &result[1]);
	result[2] = '\0';
	return result;
}



int parametrage(FILE* image)
{
	int result;
	int test;
	result = 0;
	sauterCommentaire(image);
	test = fscanf(image, "%d", &result);
	if (test != 1)
		erreur(IMAGE_CORROMPUE,EXIT);
    
    return result;
}


int teinteMax(char* type, FILE* image)
{
    int result;
    result = 0;
    if (!strcmp(type, "P2") || !strcmp(type, "P3"))
	{
		result = parametrage(image);
	}else{
		result = 0;
	}
	return result;
}

int charToInt(char c){
if (c == '0')
	return (0);
else
	return (1);
}

void recuperationPixels(FILE* fichier, int** tab, int largeur, int hauteur, char* type)
{
	int i;
	int j;
	int pixel;
	int test; /* permet de savoir si le scanf ne génère pas d'erreur*/
	pixel = 0;
	test = 1;
	for (i = 0 ; i < hauteur ; i++)
	{
		for (j = 0; j < largeur; j += 1)
		{
			sauterCommentaire(fichier);
			if (!strcmp(type, "P2") || !strcmp(type,"P3"))
				test = fscanf(fichier, "%d", &pixel);
			else
				pixel = charToInt(fgetc(fichier));
			if (test == 1)
				tab[i][j] = pixel;
			else
				erreur(IMAGE_CORROMPUE,EXIT);

	
		}
	}
}


int** recupPixel(FILE* fichier, int largeur, int hauteur, char* type)
{
	int** tab;
	if(!strcmp(type,"P3"))	
		largeur *= 3;
	tab = initMatrice(largeur,hauteur);	
	recuperationPixels(fichier, tab, largeur, hauteur, type);
	return tab;
}



Image chargerImage(char* nomImage, int* bool_erreur){
	Image imageCharge;
	FILE* image;
	char* type;
	int largeur;
	int hauteur;
	int teinteMaximale;
	int** teinte;
	image = fopen(nomImage, "r");
	if (image != NULL)
	{
		type = recupType(image);
		largeur = parametrage(image);
		hauteur = parametrage(image);
		if (!strcmp(type, "P2") || !strcmp(type,"P3"))
			teinteMaximale = teinteMax(type, image);
		teinte = recupPixel(image, largeur, hauteur, type);
		imageCharge = creationImage(type, largeur, hauteur, teinteMaximale, teinte);/*création de l image*/
	}else{
		erreur(IMAGE_NO_EXISTS,NO_EXIT);
		*bool_erreur = 1;
	}
	fclose(image);
	free(type);
	return imageCharge;	
}


void ecritureFichier(Image image, FILE* fich){
	int i;
	int j;
	int largeur;
	largeur = largeurMatriceImage (image);
	fprintf(fich,"%s\n",image.type);
	fprintf(fich,"%d\t",image.width);
	fprintf(fich,"%d\n",image.height);
	if (strcmp(image.type,"P1")){
		fprintf(fich,"%d\n",image.teinteMax);
	}
	for(i=0;i<image.height;i++)
	{
		for (j = 0; j < largeur; j += 1)
		{
			fprintf(fich,"%d\n",image.teinte[i][j]);
		}
	}
}


void setExtention (Image image, char* output)
{
	if(!strcmp(image.type, "P1"))
		sprintf(output,"%s%s",output, ".pbm");
	else if(!strcmp(image.type, "P2"))
		sprintf(output,"%s%s",output, ".pgm");
	else
		sprintf(output,"%s%s",output, ".ppm");
}

void save(Image image, char* output, int* bool_erreur)
{
	FILE* fich;
	char* ext;
	ext = "";
	if(!*bool_erreur)
	{
		ext = recupererExtension(output);
		if (!strcmp(ext,""))
			setExtention(image, output);
		fich=fopen(output, "w");
		if(fich != NULL)
		{
			ecritureFichier(image, fich);
			fclose(fich);
			libererImage(image);
		}
		else{
			*bool_erreur = 1;
			libererImage(image);
			erreur(ERREUR_OUTPUT,NO_EXIT);
			}
	}

}


void testChargerImage(char* input, char* output)
{
	Image image;
	char* type;
	int bool_erreur;
	bool_erreur = 0;
	image = chargerImage(input,&bool_erreur);
	if(!bool_erreur)
	{
		type = image.type;
		if (!strcmp(recupererExtension(output),""))
			sprintf(output,"%s.%s",output, recupererExtension(input));	
		if(verifType(type))
		{
			erreur(ERREUR_TYPE, NO_EXIT);
		}
		else
		{
			save(image, output,&bool_erreur);
			printf("L'image %s a été sauvegardée dans le fichier %s \n", input, output);
		}
	}
	
}


