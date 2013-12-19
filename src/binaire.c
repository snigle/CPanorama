#include "binaire.h"

int** remplirMatriceBinaire (Image im_image, int int_seuil)
{
	int** int_teinteBinaire;
	int int_i;
	int int_j;
	int_teinteBinaire=initMatrice(0,im_image.width, im_image.height);
	
		for(int_i = 0 ; int_i < im_image.height ; int_i++)
		{
			for (int_j = 0; int_j < im_image.width; int_j += 1)
			{
				if(im_image.teinte[int_i][int_j]> int_seuil)
					int_teinteBinaire[int_i][int_j]=0;
				else
					int_teinteBinaire[int_i][int_j]=1;
			}
		}	
	
	return (int_teinteBinaire);
}

Image binaire(char* str_input, char* str_output, char* str_valeurDeBascule, int int_bool_save, int* int_bool_erreur)
{
	Image im_image;
	Image im_sortie;	
	int** int_teinteBinaire;
	int int_seuil;
	printf("**%s -b %s**\n",str_input,str_output);
	int_seuil = atoi(str_valeurDeBascule);
	im_image=chargerImage(str_input, int_bool_erreur);
	if(!*int_bool_erreur){
		if(testType(im_image, "P2"))
		{
			int_teinteBinaire = remplirMatriceBinaire(im_image, int_seuil);
			im_sortie = creationImage("P1",im_image.width,im_image.height, int_seuil, int_teinteBinaire);
			if(int_bool_save)
			{
				save(im_sortie, str_output, int_bool_erreur);
				if(!*int_bool_erreur) printf("\tLa conversion en noir et blanc du fichier %s a été effectuée avec succés. Le fichier de sortie est : %s \n", str_input, str_output);
			}
		}
		else
			*int_bool_erreur = 1;
		libererImage(im_image);
	}
	return (im_sortie);
}
