#include "harris.h"


int** deriveeVerticale(Image image)
{
	int** result;
	int i;
	int j;
	result = initMatrice(image.width,image.height);
	for (i = 0; i < image.height -1; i += 1)
	{
		for (j = 0; j < image.width -1; j += 1)
		{
			result[i][j] = image.teinte[i+1][j] -image.teinte[i][j];
		}
	}
	return result;
}

int** deriveeHorizontale(Image image)
{
	int** result;
	int i;
	int j;
	result = initMatrice(image.width,image.height);
	for (i = 0; i < image.height -1; i += 1)
	{
		for (j = 0; j < image.width -1; j += 1)
		{
			result[i][j] = image.teinte[i][j+1] -image.teinte[i][j];
		}
	}
	return result;
}

int** derivee(Image image)
{
	int** result;
	int i;
	int j;
	result = initMatrice(image.width,image.height);
	for (i = 0; i < image.height -1; i += 1)
	{
		for (j = 0; j < image.width -1; j += 1)
		{
			result[i][j] = image.teinte[i+1][j+1] -image.teinte[i][j];
		}
	}
	return result;
}

ListePoints* harris(char* input, int* bool_erreur){
	int** mat_A;
	int** mat_B;
	int** mat_C;
	float M;
	int y;
	int x;
	ListePoints* result;	
	Image image;
	result=NULL;
	image = chargerImage(input,bool_erreur);
	mat_A = deriveeVerticale(image);
	mat_B = deriveeHorizontale(image);
	mat_C = derivee(image);
	for (y = 0; y < image.height; y += 1)
	{
		for (x = 0; x < image.width; x += 1)
		{
			M = (mat_A[y][x] * mat_B[y][x] - mat_C[y][x] * mat_C[y][x]) - (0.09 * ((mat_A[y][x] + mat_B[y][x]) * (mat_A[y][x] + mat_B[y][x])));
			if(M>50)
				result = ajoutCoordonnee(result, x, y, M);
		}
	}
	return result;
}

void enregistrerHarris(char* input,char* output, int* bool_erreur)
{
	ListePoints* tmp;
	Image image;
	Image imageResult;
	int** mat_result;
	printf("**%s --harris %s**\n",input,output);
	image = chargerImage(input,bool_erreur);
	if(!*bool_erreur && testType(image,"P2"))
	{
		mat_result = initMatrice(image.width,image.height);
		tmp = harris(input,bool_erreur);
		if(!*bool_erreur)
		{	
			while(tmp->suivant != NULL)
			{
				mat_result[tmp->y][tmp->x] = 1;
				tmp = tmp->suivant;
			}
			imageResult = creationImage("P1",image.width,image.height,1,mat_result);
			save(imageResult, output, bool_erreur);
			if(!*bool_erreur) printf("\tLe traitement de harris a été effectué\n");
		}
		
	}
	else
		*bool_erreur = 1;
}
