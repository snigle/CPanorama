


#include "rgbToGrayscale.h"



void creationTabGrayScale(int** tabGrey, Image image)
{
	int i;
	int j;
	for(i = 0 ; i < image.height ; i++)
	{
		for (j = 0; j < image.width; j += 1)
			tabGrey[i][j] = 0.299 * image.teinte[i][j*3] + 0.587 * image.teinte[i][j*3+1] + 0.114 * image.teinte[i][j*3+2];	
	}	
}

Image creerGrayScale (Image pixRGB)
{
	Image imagePGM;
	int** tabGrey;
	tabGrey = initMatrice(pixRGB.width,pixRGB.height);
	creationTabGrayScale(tabGrey, pixRGB);
	imagePGM = creationImage("P2", pixRGB.width, pixRGB.height, pixRGB.teinteMax, tabGrey);
	return imagePGM;
}

Image grayScale (char* input,char* output, int bool_save, int* bool_erreur)
{
	Image imagePPM;
	Image imagePGM;
	printf("**%s -g %s**\n",input,output);
	imagePPM = chargerImage(input, bool_erreur);
	if(!*bool_erreur){
		if (testType(imagePPM,"P3"))
		{
			imagePGM = creerGrayScale(imagePPM);
			if(bool_save)
			{
				save(imagePGM, output, bool_erreur);
				if(!*bool_erreur) printf("\tLe fichier %s a été converti en échelle de gris dans le fichier %s\n",input,output);
			}
		}
		else
			*bool_erreur = 1;
		libererImage(imagePPM);
	}
	return imagePGM;
}
