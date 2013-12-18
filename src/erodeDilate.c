#include "erodeDilate.h"



int estUnObjet(int i, int j, Image im_image){
	int int_zero;
	int int_un;
	int int_deux;
	int int_trois;
	int int_quatre;
	int int_cinq;
	int int_six;
	int int_sept;
	int_zero = im_image.teinte[i][j+1];
	int_un = im_image.teinte[i-1][j+1];
	int_deux = im_image.teinte[i-1][j];
	int_trois =  im_image.teinte[i-1][j-1];
	int_quatre = im_image.teinte[i][j-1];
	int_cinq = im_image.teinte[i+1][j-1];
	int_six = im_image.teinte[i+1][j];
	int_sept = im_image.teinte[i+1][j+1];
	return ((int_un||int_deux||int_trois)&&(int_cinq||int_six||int_sept)&&!int_quatre&&!int_zero) ||
	((int_un||int_zero||int_sept)&&(int_trois||int_quatre||int_cinq)&&!int_deux&&!int_six) ||
	(int_trois&&(int_cinq||int_six||int_sept||int_zero||int_un)&&!int_deux&&!int_quatre) ||
	(int_un&&(int_trois||int_quatre||int_cinq||int_six||int_sept)&&!int_deux&&!int_zero) ||
	(int_sept&&(int_un||int_deux||int_trois||int_quatre||int_cinq)&&!int_zero&&!int_six) ||
	(int_cinq&&(int_sept||int_zero||int_un||int_deux||int_trois)&&!int_quatre&&!int_six);
}



void ajouterObjet(int int_hauteur, int int_largeur, int** matInt_matrice, Image im_image)
{
	int i;
	int j;
	for (i = -1; i < 2; i += 1)
	{
		for (j = -1; j < 2; j += 1)
		{
			matInt_matrice[int_hauteur + i][int_largeur + j] = im_image.teinte[int_hauteur + i][int_largeur + j];
		}
	}
}


int estDansLaMatrice(int i, int j, Image im_image)
{
	return i>0 && j>0 && i<im_image.height && j < im_image.width;
}


int** genererMatriceErode(Image im_imageInput)
{
	int** matriceErode;
	int i;
	int j;
	int k;
	int l;
	matriceErode = initMatrice(im_imageInput.width, im_imageInput.height);
	for (i = 1; i < im_imageInput.height-2; i += 1)
	{
		for (j = 1; j < im_imageInput.width-2; j += 1)
		{
			matriceErode[i][j]=1;
			for (k = -1; k < 2; k += 1)
			{
				for (l = -1; l < 2; l += 1)
				{
					matriceErode[i][j]=matriceErode[i][j] && im_imageInput.teinte[i+k][j+l];
				}
			}
		}
	}
	
	return matriceErode;
}

/*int** genererMatriceDilate(Image im_imageInput)*/
/*{*/
/*	int** matriceDilate;*/
/*	int i;*/
/*	int j;*/

/*	matriceDilate = initMatrice(im_imageInput.width, im_imageInput.height);*/
/*	for (i = 1; i < im_imageInput.height-1; i += 1)*/
/*	{*/
/*		for (j = 1; j < im_imageInput.width-1; j += 1)*/
/*		{*/
/*			if(estUnObjet(i,j,im_imageInput))*/
/*			{	*/
/*				ajouterObjet(i,j,matriceDilate,im_imageInput);*/
/*				*/
/*			}*/
/*			else*/
/*				matriceDilate[i][j] = 1;	*/
/*		}*/
/*	}*/
/*	*/
/*	return matriceDilate;*/
/*}*/

int** genererMatriceDilate(Image im_imageInput)
{
	int** matriceDilate;
	int i;
	int j;
	int k;
	int l;
	matriceDilate = initMatrice(im_imageInput.width, im_imageInput.height);
	for (i = 1; i < im_imageInput.height-2; i += 1)
	{
		for (j = 1; j < im_imageInput.width-2; j += 1)
		{
			matriceDilate[i][j]=0;
			for (k = 0; k < 2; k += 1)
			{
				for (l = 0; l < 2; l += 1)
				{
					matriceDilate[i][j]=matriceDilate[i][j] || im_imageInput.teinte[i+k][j+l];
				}
			}
		}
	}
	
	return matriceDilate;
}

Image erode (char* str_input, char* str_output, int bool_save, int* bool_erreur)
{
	Image im_imageInput;
	Image imageErode;
	int** matriceErode;
	printf("**%s -e %s**\n",str_input,str_output);
	im_imageInput = chargerImage(str_input,bool_erreur);
	if(!*bool_erreur){
		if(testType(im_imageInput,"P1"))
		{
			matriceErode = genererMatriceErode(im_imageInput);
			imageErode = creationImage(im_imageInput.type,im_imageInput.width,im_imageInput.height,im_imageInput.teinteMax,matriceErode);
			if(bool_save)
			{	
				save(imageErode, str_output, bool_erreur);
				if(!*bool_erreur) printf("\tL'image %s a été érodé dans le fichier %s\n",str_input,str_output);
			}
		}
		else
			*bool_erreur = 1;
		libererImage(im_imageInput);
	}
	return imageErode;
}

Image dilate (char* str_input, char* str_output, int bool_save, int* bool_erreur){
	Image im_imageInput;
	Image imageDilate;
	int** matriceDilate;
	printf("**%s -d %s**\n",str_input,str_output);
	im_imageInput = chargerImage(str_input,bool_erreur);
		
	if(!*bool_erreur){
		if(testType(im_imageInput,"P1")){
			matriceDilate = genererMatriceDilate(im_imageInput);
			imageDilate = creationImage(im_imageInput.type,im_imageInput.width,im_imageInput.height,im_imageInput.teinteMax,matriceDilate);
			if(bool_save)
			{
				save(imageDilate, str_output, bool_erreur);
				if(!*bool_erreur) printf("\tL'image %s a été dilaté dans le fichier %s\n",str_input,str_output);
			}
			
		}else
			*bool_erreur = 1;
		libererImage(im_imageInput);
	}
	
	return imageDilate;
}
