/*! \file recuperationFichier.c
 *  \author Perales Quentin <peralesque@eisti.eu>
 *  \version 0.1
 *  \date  Mon 23 Sep 2013
 *
 *  \brief chargement d'une image
 *
 *
 */


#include "header.h"



/*!
       \fn allerAlaLigne
       \author Perales Quentin <peralesque@eisti.eu>
       \date Mon 23 Sep 2013
       \brief va a la ligne dans le fichier
       
       \param       
       	file* image : le code de l image en pixmap
       
               
               \remarks

*/

void allerAlaLigne (FILE* fichier){
	char carac;//un caractere quelconque
    do 
    {
    	fscanf(fichier, "%c", &carac);
    } while (carac != '\n');
}

/*!
       \fn sauterCommentaire
       \author Perales Quentin <peralesque@eisti.eu>
       \date Mon 23 Sep 2013
       \brief déroule le fichier jusqu'a ce qu'il n'y ai plus de commentaire
       
       \param       
       	file* fichier : un fichier pixmap
       
               
               \remarks 

*/
void sauterCommentaire(FILE* fichier)
{
	char carac;//un caractere quelconque
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

/*!
       \fn recuperationType
       \author Perales Quentin <peralesque@eisti.eu>
       \date Mon 23 Sep 2013
       \brief récupere le type d une image pixmap
       
       \param       
       	char* tab : un tableau vide qui sera ensuite remplie par le type P1 P2 ou P3
       	file* image : le code de l image en ppm
       
               
               \remarks

*/
void recupType(char* tab, FILE* image) 
{
	sauterCommentaire(image);
	fscanf(image, "%c", &tab[0]);
	fscanf(image, "%c", &tab[1]);
	tab[2] = '\0';
}



/*!
       \fn parametrage
       \author Perales Quentin <peralesque@eisti.eu>
       \date Mon 23 Sep 2013
       \brief retourne une caractéristique de l'image
       
       \param       
       	file* image : l'image en pixmap
       \return 
               
               \remarks 

*/
int parametrage(FILE* image)
{
	int result;//le resultat de la fonction (largeur de l'image)
	int test; // permet de savoir si le scanf ne génère pas d'erreur
	result = 0;
	sauterCommentaire(image);
	test = fscanf(image, "%d", &result);
	if (test != 1)
		erreur(IMAGE_CORROMPUE);
    
    return result;
}

/*!
       \fn teinteMax
       \author Perales Quentin <peralesque@eisti.eu>
       \date Mon 23 Sep 2013
       \brief récupère la teinte maximale de l'image P2 ou P3 en modele pixmap
       
       \param       
       	char type : 
       	file* image : 
       \return 
               
               \remarks on retourne 0 pour l'image de type P1

*/
int teinteMax(char type[3], FILE* image)
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

/*!
       \fn recuperationPixels
       \author Perales Quentin <peralesque@eisti.eu>
       \date Mon 23 Sep 2013
       \brief recupération de chaque teintes de pixel, quelque soit le type P1 P2 ou P3
       
       \param       
       	file* fichier : un fichier, ici l'image a charger
       	int* tab : un tableau vide qui se remplis d'entiers qui correspondent a des teintes 
        tailleTotale : un entier qui prend en considération la taille totale du tableau en fonction du Type
               
               \remarks 

*/

void recuperationPixels(FILE* fichier, int* tab, int tailleTotale)
{
	int i;
	int pixel;
	int test; // permet de savoir si le scanf ne génère pas d'erreur
	pixel = 0;
	for (i = 0 ; i < tailleTotale ; i++)
	{
		sauterCommentaire(fichier);
		test = fscanf(fichier, "%d", &pixel);
		if (test == 1)
		{
			tab[i] = pixel;
		}else
			{
				erreur(IMAGE_CORROMPUE);
			}
	}
}


/*!
       \fn recupPixel
       \author Perales Quentin <peralesque@eisti.eu>
       \date Tue 24 Sep 2013
       \brief Renvoie un tableau d'entier contenant l'ensemble des informations contenant l'image
       
       \param       
       	int* tab : un tableau d'entier qui entre vide et qui ressort avec l'ensemble des teintes
       	file* fichier : un fichier rmpli d'information
       	int largeur : la largeur de l image
       	int hauteur : la hauteur de l'image
       	type : type de l'image pixmap
       \return 
               retourne un tableau d'entier
               \remarks 

*/
int* recupPixel(FILE* fichier, int largeur, int hauteur, char* type)
{
	int* tab;
	if (!strcmp(type, "P1") || !strcmp(type, "P2"))
	{
		tab = malloc(largeur * hauteur * sizeof(int));
		recuperationPixels(fichier, tab, largeur * hauteur);
	}else{
			tab = malloc(3 * largeur * hauteur * sizeof(int));
			recuperationPixels(fichier, tab, 3 * largeur * hauteur);
		 }
	return tab;
}

/*!
       \fn chargerImage
       \author Perales Quentin <peralesque@eisti.eu>
       \date Tue 24 Sep 2013
       \brief Charger une image pixmap
       
       \param       
       	char* nomimage : une chaine de caractere qui precise le nom de l'image a charger
       \return retourne une imageCharge
               \remarks RAS

*/

Image chargerImage(char* nomImage){
	Image imageCharge;
	FILE* image;
	char type[3];
	int largeur;
	int hauteur;
	int teinteMaximale;
	int* teinte;
	image = fopen(nomImage, "r");
	if (image != NULL)
	{
		recupType(type, image);
		largeur = parametrage(image);
		hauteur = parametrage(image);
		teinteMaximale = teinteMax(type, image);
		teinte = recupPixel(image, largeur, hauteur, type);
		imageCharge = creationImage(type, largeur, hauteur, teinteMaximale, teinte);//création de l image
	}else
		erreur(IMAGE_NO_EXISTS);
	fclose(image);
	//free(teinte);//libère la mémoire
	return imageCharge;	
}



int save(Image image, char* output)
{
	FILE* fich;
	int taille;
	taille = image.width * image.height;
	int i;
	fich=fopen(output, "w");
	fprintf(fich,"%s\n",image.type);
	fprintf(fich,"%d\t",image.width);
	fprintf(fich,"%d\n",image.height);
	fprintf(fich,"%d\n",image.teinteMax);
	for(i=0;i<taille;i++)
	{
		if(!strcmp(image.type,"P3"))
			fprintf(fich,"%d\t%d\t%d\n",image.teinte[i*3],image.teinte[i*3+1],image.teinte[i*3+2]);
		else
			fprintf(fich,"%d\n",image.teinte[i]);	
	}
	
	fclose(fich);
	return 0;
}
	
