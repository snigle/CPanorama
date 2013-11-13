#include "convolution.h"



int testFinFichierFiltre(FILE* file_filtre)
{
	int int_k;
	int int_test;
	char char_caractere;
	int_k = 0;
	int_test = 1;
	char_caractere = ' ';
	while (char_caractere != EOF && int_test == 1)
	{
		int_test = fscanf(file_filtre, "%c", &char_caractere);
		if (char_caractere != '\n' && char_caractere != ' ')
			int_k++;
	}
	return (int_k);
}

int retournerLaTaille(int int_taille)
{
	int int_i;
	int_i = 1;
	while (int_i*int_i < int_taille)
	{
		int_i++;
	}
	if ((int_i != 1) && (int_i*int_i == int_taille) && (int_i%2 == 1))
	{
		return (int_i);
	}else{
		return (1);
	}	
}

int calculTailleFiltre(FILE* file_filtre)
{
	int int_i;
	int int_taille;
	int int_test; /*vérifie si le scanf se déroule bien*/
	int_taille = 0;
	int_test = 1;
	int_i = 0;
	while (int_test == 1)
	{
		int_test = fscanf(file_filtre, "%d", &int_i);
		if (int_test == 1)
		{
			int_taille++;
		}
	}
	return (retournerLaTaille(int_taille));
}

void remplirFiltre(FILE* file_filtre, int** int_matrice, int int_taille)
{
	int int_i;
	int int_j;
	int int_coef;
	int int_test;
	for (int_i = 0; int_i < int_taille; int_i += 1)
	{
		for (int_j = 0; int_j < int_taille; int_j += 1)
		{
			int_test = fscanf(file_filtre, "%d", &int_coef);
			if(int_test == 1)
				int_matrice[int_i][int_j] = int_coef;
			else
				erreur(ERREUR_FILTRE, 1);
		}
	}
}

int** recupFiltre(FILE* file_filtre, int int_taille)
{

	int** int_matrice;
	int int_testFichier;
	if (int_taille != 1)
	{
		rewind(file_filtre);
		int_matrice = initMatrice(int_taille,int_taille);
		remplirFiltre(file_filtre, int_matrice, int_taille);
		int_testFichier = testFinFichierFiltre(file_filtre);
		if (int_testFichier != 0)
			erreur(ERREUR_FILTRE, 1);
	}else{
		erreur(ERREUR_FILTRE, 1);
	}
	return (int_matrice);
}



int setNumber(int int_x, int int_y, int int_largeur, int int_hauteur, int** int_pixels, int** int_filtre, int int_taille, int int_decalage)
{
	int int_i;
	int int_j;
	int int_result;
	int_result = 0;
	for (int_i = 0; int_i < int_taille; int_i += 1)
	{
		for (int_j = 0; int_j < int_taille; int_j += 1)
		{
				int_result += int_filtre[int_i][int_j] * int_pixels[int_x - int_decalage + int_i][int_y - int_decalage + int_i];
		}
	}
	if (int_result < 0)
		return (0);
	else if (int_result > 255)
		return (255);
	else
		return (int_result);
}



int** applicationFiltre(Image im_image, int** int_filtre, int int_taille)
{
	int** int_result;
	int int_i;
	int int_j;
	int int_decalage;
	int_decalage = (int_taille - 1) / 2;
	int_result = initMatrice(im_image.width, im_image.height);
	for (int_i = 0; int_i < im_image.height; int_i += 1)
	{
		for (int_j = 0; int_j < im_image.width; int_j += 1)
		{
			if ((int_i < int_decalage) || (int_j < int_decalage) || (int_i >= (im_image.height - int_decalage)) || (int_j >= (im_image.width - int_decalage)))
				int_result[int_i][int_j] = im_image.teinte[int_i][int_j];
			else
				int_result[int_i][int_j] = setNumber(int_i, int_j, im_image.width, im_image.height, im_image.teinte, int_filtre, int_taille, int_decalage);
		}
	}
	return (int_result);
}



Image applicationConvolution(Image im_image, FILE* file_fichierFiltre, int int_taille)
{
	int** int_apresConvolution;
	int** int_filtre;
	Image im_imageConvolution;	
	int_filtre = recupFiltre(file_fichierFiltre, int_taille);

	int_apresConvolution = applicationFiltre(im_image, int_filtre, int_taille);
	im_imageConvolution = creationImage("P2", im_image.width, im_image.height, 255, int_apresConvolution);
	
	return (im_imageConvolution);

}


int testFiltre(FILE* file_filtre)
{
	int int_result;
	if (file_filtre == NULL)
	{
		erreur(ERREUR_FILTRE, NO_EXIT);
		int_result = 0;
	}else
		int_result = 1;
		
	return(int_result);
}

Image convolution (char* str_input, char* str_output, char* str_nomFichier, int int_bool_save, int* int_bool_erreur){
	FILE* file_fichierFiltre;
	Image im_image;
	Image im_result;
	int int_taille;
	printf("**%s -c %s, filtre : %s**\n",str_input,str_output,str_nomFichier);
	file_fichierFiltre = fopen(str_nomFichier, "r");
	im_image = chargerImage(str_input, int_bool_erreur);
	if(!*int_bool_erreur){
		if(testFiltre(file_fichierFiltre) && testType(im_image, "P2"))
		{
			int_taille = calculTailleFiltre(file_fichierFiltre);
			im_result = applicationConvolution(im_image, file_fichierFiltre, int_taille);
			if(int_bool_save)
			{
				save(im_result, str_output, int_bool_erreur);
				if(!*int_bool_erreur) printf("\tLa convolution sur le fichier %s a été effectuée avec succés. Le fichier de sortie est : %s \n", str_input, str_output);
			}
			fclose(file_fichierFiltre);
		}
		else
			*int_bool_erreur = 1;
		libererImage(im_image);
	}
	return (im_result);
}
