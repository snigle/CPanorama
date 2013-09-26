/*! \file rgbToGreyscale.c
 *  \author Perales Quentin <peralesque@eisti.eu>
 *  \version 0.1
 *  \date  Thu 26 Sep 2013
 *
 *  \brief permet de passer d'une image en couleur pixmap type P3 à une image pixmap type P2
 *
 *
 */


void creationTabGrayScale(int* tabGrey, Image image)
{
	int i;
	int taille;
	taille = image.width * image.heigth;
	for(i = 0 ; i < taille ; i++)
	{
		tabGrey[i] = (image.teinte[i*3] + image.teinte[i*3+1] + image.teinte[i*3+2]) / 3;
	}	
}

Image creerGreyScale (Image pixRGB)
{
	Image imagePGM;
	char type[3];
	int* tabGrey;
	type = "P2";
	tabGrey = malloc(pixRGB.width * pixRGB.height * sizeof(int*));
	creationTabGrayScale(tabGrey, pixRGB);
	imagePGM = creationImage(type, pixRGB.width, pixRGB.height, pixRGB.teinteMax, tabGrey);
	return imagePGM;
}

int greyScale (char* input,char* output)
{
	Image imagePPM;
	Image imagePGM;
	imagePPM = chargerImage(input);
	imagePGM = creerGreyScale(imagePPM);
	sauvegarder(imagePGM, ouput);
	return (0);
}
