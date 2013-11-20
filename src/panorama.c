#include "panorama.h"

int panorama(char** input, int nombreInput, char* output, int* bool_erreur)
{
	Image result;
	Image imageInput;
	int** mat_result;
	int fin;
	/*Liste point des deux premières images*/
	ListePoints* image1;
	ListePoints* image2;
	ListePoints* image11;
	ListePoints* image21;
	ListePoints* image22;
	if(nombreInput==2)
	{
	imageInput = chargerImage(input[0],bool_erreur);
	image1 = harris(input[0],bool_erreur);
	image2 = harris(input[1],bool_erreur);
	mat_result = initMatrice(imageInput.width,imageInput.height);
	while(image1->suivant !=NULL)
	{
		image11 = image1->suivant;
		fin =0;
		while(image11->suivant != NULL && !fin)
		{
			image21 = image2;
			while(image21->suivant != NULL && !fin)
			{
				if(image21->valeur==image1->valeur)
				{
					image22 = image21;
					while(image22->suivant != NULL && !fin)
					{
						if(image11->valeur==image22->valeur && pow((image1->x - image11->x),2) +pow((image1->y - image11->y),2) == pow((image21->x - image22->x),2)+ pow((image21->y - image22->y),2))
						{
							mat_result[image1->y][image1->x]= 1;
							fin = 1;
						}
						image22 = image22->suivant;
					}
				}
				image21 = image21->suivant;
			}
			image11 = image11->suivant;
		}
		image1 = image1->suivant;
		
	}
	result = creationImage("P1",imageInput.width, imageInput.height, 1, mat_result);
	save(result,output, bool_erreur);
	}
	printf("Appel de la fonction Panorama\n");
	return 0;
}

