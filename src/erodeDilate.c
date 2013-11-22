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
	matriceErode = initMatrice(imageInput.width, imageInput.height);
	for (i = 1; i < imageInput.height-2; i += 1)
	{
		for (j = 1; j < imageInput.width-2; j += 1)
		{
			matriceErode[i][j]=1;
			for (k = -1; k < 2; k += 1)
			{
				for (l = -1; l < 2; l += 1)
				{
					matriceErode[i][j]=matriceErode[i][j] && imageInput.teinte[i+k][j+l];
				}
			}
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
/*

DEUXIEME METHODE

int** genererMatriceDilate(Image imageInput)
{
	int** matriceDilate;
	int i;
	int j;
	int k;
	int l;
	matriceDilate = initMatrice(imageInput.width, imageInput.height);
	for (i = 1; i < imageInput.height-2; i += 1)
	{
		for (j = 1; j < imageInput.width-2; j += 1)
		{
			matriceDilate[i][j]=0;
			for (k = -1; k < 2; k += 1)
			{
				for (l = -1; l < 2; l += 1)
				{
					matriceDilate[i][j]=matriceDilate[i][j] || imageInput.teinte[i+k][j+l];
				}
			}
		}
	}
	
	return matriceDilate;
}
*/
Image erode (char* input, char* output, int bool_save, int* bool_erreur)
{
	Image imageInput;
	Image imageErode;
	int** matriceErode;
	printf("**%s -e %s**\n",input,output);
	imageInput = chargerImage(input,bool_erreur);
	if(!*bool_erreur){
		if(testType(imageInput,"P1"))
		{
			matriceErode = genererMatriceErode(imageInput);
			imageErode = creationImage(imageInput.type,imageInput.width,imageInput.height,imageInput.teinteMax,matriceErode);
			if(bool_save)
			{	
				save(imageErode, output, bool_erreur);
				if(!*bool_erreur) printf("\tL'image %s a été érodé dans le fichier %s\n",input,output);
			}
		}
		else
			*bool_erreur = 1;
		libererImage(imageInput);
	}
	return imageErode;
}

Image dilate (char* input, char* output, int bool_save, int* bool_erreur){
	Image imageInput;
	Image imageDilate;
	int** matriceDilate;
	printf("**%s -d %s**\n",input,output);
	imageInput = chargerImage(input,bool_erreur);
		
	if(!*bool_erreur){
		if(testType(imageInput,"P1")){
			matriceDilate = genererMatriceDilate(imageInput);
			imageDilate = creationImage(imageInput.type,imageInput.width,imageInput.height,imageInput.teinteMax,matriceDilate);
			if(bool_save)
			{
				save(imageDilate, output, bool_erreur);
				if(!*bool_erreur) printf("\tL'image %s a été dilaté dans le fichier %s\n",input,output);
			}
			
		}else
			*bool_erreur = 1;
		libererImage(imageInput);
	}
	
	return imageDilate;
}
