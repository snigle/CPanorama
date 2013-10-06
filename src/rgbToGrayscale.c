/*! \file rgbToGreyscale.c
 *  \author Perales Quentin <peralesque@eisti.eu>
 *  \version 0.1
 *  \date  Thu 26 Sep 2013
 *
 *  \brief permet de passer d'une image en couleur pixmap type P3 à une image pixmap type P2
 *
 *
 */


#include "rgbToGrayscale.h"



void creationTabGrayScale(int** tabGrey, Image image)
{
	int i;
	int j;
	for(i = 0 ; i < image.height ; i++)
	{
		for (j = 0; j < image.width; j += 1)
			tabGrey[i][j] = (image.teinte[i][j*3] + image.teinte[i][j*3+1] + image.teinte[i][j*3+2]) / 3;	
	}	
}

Image creerGrayScale (Image pixRGB)
{
	Image imagePGM;
	char p2[3];
	int** tabGrey;
	tabGrey = initMatrice(pixRGB.width,pixRGB.height);
	p2[0] = 'P';
	p2[1] = '2';
	p2[2] = '\0';
	creationTabGrayScale(tabGrey, pixRGB);
	imagePGM = creationImage(p2, pixRGB.width, pixRGB.height, pixRGB.teinteMax, tabGrey);
	return imagePGM;
}

int grayScale (char* input,char* output)
{
	Image imagePPM;
	Image imagePGM;
	imagePPM = chargerImage(input);
	int result;
	result = 0;
	if (!strcmp(imagePPM.type,"P3"))
	{
		if(!result)
			imagePGM = creerGrayScale(imagePPM);
			save(imagePGM, output);
			printf("Le fichier %s a été converti en échelle de gris dans le fichier %s\n",input,output);
	}
	else
		result = MAUVAIS_FORMAT_GRAYSCALE;
	
	return result;
}
