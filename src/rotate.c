#include "rotate.h"

int** transformation(Image image)
{
	int** newTeinte;
	int d;
	int D;
	int i;
	int j;
	int xp;
	int yp;
	d = sin(PI/6.0)*image.height + cos(PI/6.0)*image.width;
	D = cos(PI/6.0)*image.height + sin(PI/6.0)*image.width;
	newTeinte = initMatrice(d, D);
	for (i = 0; i < image.height; i += 1)
	{
		for (j = 0; j < image.width; j += 1)
		{
/*			xp = j * cos(PI/6.0) - i * sin(PI/6.0) + sin(PI/6.0)*image.height;*/
/*			yp = j * sin(PI/6.0) + i* cos(PI/6.0);*/
			xp = j * 0.91 - i*0.03 + 6;
			yp = j * (-0.59) + i* 0.91 + 153;
			if(yp>0 && xp>0 && yp<D && xp<d)
			newTeinte[yp][xp] = image.teinte[i][j];
		}
	}
/*	for (i = 0; i < d; i += 1)*/
/*	{*/
/*		for (j = 0; j < D; j += 1)*/
/*		{*/
/*			if (newTeinte[i][j] == 0)*/
/*				*/
/*		}*/
/*	}*/
	return newTeinte;
}


Image rotate (char* str_input, char* str_output, int bool_save, int* bool_erreur){
	Image im_imageInput;
	Image imageRotation;
	int** newTeinte;
	printf("**%s -rot %s**\n",str_input,str_output);
	im_imageInput = chargerImage(str_input,bool_erreur);
		
	if(!*bool_erreur){
		if(testType(im_imageInput,"P2")){
			newTeinte = transformation(im_imageInput);	
			imageRotation = creationImage(im_imageInput.type, sin(PI/6.0)*im_imageInput.height + cos(PI/6.0)*im_imageInput.width, cos(PI/6.0)*im_imageInput.height + sin(PI/6.0)*im_imageInput.width, im_imageInput.teinteMax, newTeinte);
			if(bool_save)
			{
				save(imageRotation, str_output, bool_erreur);
				if(!*bool_erreur) printf("\tL'image %s a été modifiée dans le fichier %s\n",str_input,str_output);
			}
			
		}else
			*bool_erreur = 1;
		libererImage(im_imageInput);
	}
	
	return imageRotation;
}
