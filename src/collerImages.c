#include "collerImages.h"

	
int* taille(ListePoints* liste1, ListePoints* liste2, int hImage1, int hImage2, int  lImage1, int lImage2)
{
	int hauteur;
	int largeur;
	int* taille;
	taille=mallocBis(2*sizeof(int));
	
	hauteur=fmax(liste1->y,liste2->y)+ fmax((hImage1 - liste1->y),(hImage2 - liste2->y));
	largeur=fmax(liste1->x,liste2->x)+ fmax((lImage1 - liste1->x),(lImage2 - liste2->x));
	
	taille[0]=hauteur;
	taille[1]=largeur;
	
	return(taille);
	
}

int** fusionCas1(int hauteur, int largeur, ListePoints* liste1, ListePoints* liste2, Image image1, Image image2)
{
	int** matImageFinale;
	int i;
	int j;
	int deltaX;
	int deltaY;
	matImageFinale=initMatrice(largeur,hauteur);
	deltaX=(liste1->x)-(liste2->x);
	deltaY=(liste1->y)-(liste2->y);
		for(i=0;i<largeur;i++){	
			for(j=0;j<hauteur;j++){
				if(j<image1.height)
				{
					if(i<image1.width) matImageFinale[i][j]=image1.teinte[i][j];
					else
					{
						if(j< deltaX) matImageFinale[i][j]=-1;
						else matImageFinale[i][j]=image2.teinte[i-deltaX][j-deltaY];
					}	
				}
				else 
				{
					if(i<deltaX) matImageFinale[i][j]=-1;
					else matImageFinale[i][j]=image2.teinte[i-deltaX][j-deltaY];
				}
			}	
	}
	return(matImageFinale);
}

int** fusionCas2(int hauteur, int largeur, ListePoints* liste1, ListePoints* liste2, Image image1, Image image2)
{
	int** matImageFinale;
	int i;
	int j;
	int deltaX;
	int deltaY;
	matImageFinale=initMatrice(largeur,hauteur);
	deltaX=(liste2->x)-(liste1->x);
	deltaY=(liste2->y)-(liste1->y);
	for(i=0;i<largeur;i++){
		for(j=0;j<hauteur;j++){
			if(j<deltaY) 
			{
				if(i<deltaX) matImageFinale[i][j]=-1;
				else matImageFinale[i][j]=image2.teinte[i-deltaX][j];
			}
			
			else
			{
				if(i<image1.width) matImageFinale[i][j]=image1.teinte[i][j-deltaY];
				else 
				{
					if(j>image2.height) matImageFinale[i][j]=-1;
					else matImageFinale[i][j]=image2.teinte[i-deltaX][j];
				}
			}			
		}
	}
	return(matImageFinale);	
}

int** fusionFinale(int hauteur, int largeur, ListePoints* liste1, ListePoints* liste2, Image image1, Image image2)
{
	int** matImageFinale;
	matImageFinale=initMatrice(largeur,hauteur);
	
	if((liste1->x > liste2->x) && (liste1->y > liste2->y) )
	{
		matImageFinale=fusionCas1(hauteur,largeur,liste1,liste2,image1,image2);
	}
	
	if((liste1->x > liste2->x) && (liste1->y < liste2->y))
	{
		matImageFinale=fusionCas2(hauteur,largeur,liste1,liste2,image1,image2);
	}
	
	if((liste2->x > liste1->x) && (liste2->y > liste1->y) )
	{
		matImageFinale=fusionCas1(hauteur,largeur,liste2,liste1,image2,image1);
	}
	
	if((liste2->x > liste1->x) && (liste1->y > liste2->y) )
	{
		matImageFinale=fusionCas2(hauteur,largeur,liste2,liste1,image2,image1);
	}
	
	return(matImageFinale);
	
}

Image imageFinale(char* char_str_input1, char* char_str_input2, char* char_str_output, int int_bool_save, int* int_bool_erreur)
{
	Image image1;
	Image image2;
	Image imageFinale;
	ListePoints* liste1;
	ListePoints* liste2;
	int teinteMax;
	int* size;
	int** matImageFinale;
	
	teinteMax=fmax(image1.teinteMax,image2.teinteMax);
	image1=chargerImage(char_str_input1, int_bool_erreur);
	image2=chargerImage(char_str_input2, int_bool_erreur);
	
	liste1 = harris(char_str_input1,int_bool_erreur);
	liste2 = harris(char_str_input1,int_bool_erreur);
	
	size=taille(liste1,liste2,image1.height,image2.height,image1.width,image2.width);
	
	matImageFinale=fusionFinale(size[0], size[1],liste1, liste2,image1, image2);
	
	imageFinale=creationImage("P2",size[1],size[0],teinteMax, matImageFinale);
	
	printf("\t L'image %s et l'image %s ont été fusionnées. L'image finale se trouve dans le fichier %s \n", char_str_input1, char_str_input2, char_str_output);
	
	return(imageFinale);
	
}





