#include "binaire.h"

int** remplirMatriceBinaire (Image im_image, int int_seuil)
{
	int** int_teinteBinaire;
	int int_i;
	int int_j;
	int_teinteBinaire=initMatrice(im_image.width, im_image.height);
	
		for(int_i = 0 ; int_i < im_image.height ; int_i++)
		{
			for (int_j = 0; int_j < im_image.width; int_j += 1)
			{
				if(im_image.teinte[i][j]> int_seuil)
					int_teinteBinaire[i][j]=0;
				else
					int_teinteBinaire[i][j]=1;
			}
		}	
	
	return (int_teinteBinaire);
}

Image binaire(char* input, char* output, char* valeurDeBascule, int bool_save, int* bool_erreur)
{
	Image image;
	Image sortie;	
	int** teinteBinaire;
	int seuil;
	printf("**%s -b %s**\n",input,output);
	seuil = atoi(valeurDeBascule);
	image=chargerImage(input,bool_erreur);
	if(!*bool_erreur){
		if(testType(image, "P2"))
		{
			teinteBinaire = remplirMatriceBinaire(image, seuil);
			sortie = creationImage("P1",image.width,image.height, seuil, teinteBinaire);
			if(bool_save)
			{
				save(sortie, output, bool_erreur);
				if(!*bool_erreur) printf("\tLa conversion en noir et blanc du fichier %s a été effectuée avec succés. Le fichier de sortie est : %s \n", input, output);
			}
		}
		else
			*bool_erreur = 1;
		libererImage(image);
	}
	return sortie;
}
