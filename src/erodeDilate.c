/*! \file erode.c
 *  \author Perales Quentin <peralesque@eisti.eu>
 *  \version 0.1
 *  \date  Tue 08 Oct 2013
 *
 *  \brief permet d'eroder l'image choisit
 *
 *
 */

#include "erodeDilate.h"



int estUnObjet(int i, int j, Image image){
	int zero;
	int un;
	int deux;
	int trois;
	int quatre;
	int cinq;
	int six;
	int sept;
	zero = image.teinte[i][j+1];
	un = image.teinte[i-1][j+1];
	deux = image.teinte[i-1][j];
	trois =  image.teinte[i-1][j-1];
	quatre = image.teinte[i][j-1];
	cinq = image.teinte[i+1][j-1];
	six = image.teinte[i+1][j];
	sept = image.teinte[i+1][j+1];
	return ((un||deux||trois)&&(cinq||six||sept)&&!quatre&&!zero) ||
	((un||zero||sept)&&(trois||quatre||cinq)&&!deux&&!six) ||
	(trois&&(cinq||six||sept||zero||un)&&!deux&&!quatre) ||
	(un&&(trois||quatre||cinq||six||sept)&&!deux&&!zero) ||
	(sept&&(un||deux||trois||quatre||cinq)&&!zero&&!six) ||
	(cinq&&(sept||zero||un||deux||trois)&&!quatre&&!six);
}



void ajouterObjet(int hauteur, int largeur, int** matrice, Image image)
{
	int i;
	int j;
	for (i = -1; i < 2; i += 1)
	{
		for (j = -1; j < 2; j += 1)
		{
			matrice[hauteur + i][largeur + j] = image.teinte[hauteur + i][largeur + j];
		}
	}
}


int estDansLaMatrice(int i, int j, Image image)
{
	return i>0 && j>0 && i<image.height && j < image.width;
}


int** genererMatriceErode(Image imageInput)
{
	int** matriceErode;
	int i;
	int j;
	int k;
	int l;
	int copy;
	matriceErode = initMatrice(imageInput.width, imageInput.height);
	for (i = 1; i < imageInput.height-1; i += 1)
	{
		for (j = 1; j < imageInput.width-1; j += 1)
		{
			if(estUnObjet(i,j,imageInput))
			{	
					/*If the pixel is an object pixel AND all its neighbouts are object pixels*/
					copy = 1;
					for (k = -1; k < 2; k += 1)
					{
						for (l = -1; l < 2; l += 1)
						{
							if(estDansLaMatrice(i+k,j+k,imageInput))
								copy = copy && estUnObjet(i+k,j+l,imageInput);
						}
					}
					if(copy)
					matriceErode[i][j] = imageInput.teinte[i][j];
					else
						matriceErode[i][j] = 0;
			}
			else
				matriceErode[i][j] = 1;
		}
	}
	
	return matriceErode;
}

int** genererMatriceDilate(Image imageInput)
{
	int** matriceDilate;
	int i;
	int j;

	matriceDilate = initMatrice(imageInput.width, imageInput.height);
	for (i = 1; i < imageInput.height-1; i += 1)
	{
		for (j = 1; j < imageInput.width-1; j += 1)
		{
			if(estUnObjet(i,j,imageInput))
			{	
				ajouterObjet(i,j,matriceDilate,imageInput);
				
			}
			else
				matriceDilate[i][j] = 1;	
		}
	}
	
	return matriceDilate;
}

int erode (char* input, char* output)
{
	Image imageInput;
	Image imageErode;
	int** matriceErode;
	
	imageInput = chargerImage(input);
	if(!strcmp(imageInput.type,"P1"))
	{
		matriceErode = genererMatriceErode(imageInput);
	
		imageErode = creationImage(imageInput.type,imageInput.width,imageInput.height,imageInput.teinteMax,matriceErode);
		save(imageErode, output);
		printf("L'image %s a été érodé dans le fichier %s\n",input,output);
		libererImage(imageErode);
	}
	else
		erreur(ERREUR_TYPE,0);
	libererImage(imageInput);
	return (0);
}

int dilate (char* input, char* output)
{
	Image imageInput;
	Image imageDilate;
	int** matriceDilate;
	
	imageInput = chargerImage(input);
	
	matriceDilate = genererMatriceDilate(imageInput);
	
	imageDilate = creationImage(imageInput.type,imageInput.width,imageInput.height,imageInput.teinteMax,matriceDilate);
	save(imageDilate, output);
	printf("L'image %s a été dilaté dans le fichier %s\n",input,output);
	libererImage(imageInput);
	libererImage(imageDilate);
	return (0);
}

