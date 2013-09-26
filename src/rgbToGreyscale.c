/*! \file rgbToGreyscale.c
 *  \author Perales Quentin <peralesque@eisti.eu>
 *  \version 0.1
 *  \date  Thu 26 Sep 2013
 *
 *  \brief permet de passer d'une image en couleur pixmap type P3 à une image pixmap type P2
 *
 *
 */
//#include "header.h"
#include "recuperationFichier.h"


void creationTabGrayScale(int* tabGrey, Image image)
{
	int i;
	int taille;
	taille = image.width * image.height;
	for(i = 0 ; i < taille ; i++)
	{
		tabGrey[i] = (image.teinte[i*3] + image.teinte[i*3+1] + image.teinte[i*3+2]) / 3;
	}	
}

Image creerGreyScale (Image pixRGB)
{
	Image imagePGM;
	char* type;
	int* tabGrey;
	type = "P2";
	tabGrey = malloc(pixRGB.width * pixRGB.height * sizeof(int));
	creationTabGrayScale(tabGrey, pixRGB);
	imagePGM = creationImage(type, pixRGB.width, pixRGB.height, pixRGB.teinteMax, tabGrey);
	return imagePGM;
}

int greyScale (char* input,char* output)
{
	Image imagePPM;
	Image imagePGM;
	imagePPM = chargerImage(input);
	if (!strcmp(imagePPM.type, "P3"))
	{
		imagePGM = creerGreyScale(imagePPM);
		save(imagePGM, output);
		printf("Le fichier %s a été converti en noir et blanc dans le fichier %s\n",input,output);
	}
	else
	{
		return MAUVAIS_FORMAT_GRAYSCALE;
	}
	
	return (0);
}
