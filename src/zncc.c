#include "zncc.h"


double zncc2(Image image, int x, int y, int n)
{
	double result;
	double tmp;
	int i;
	int j;
	tmp=0;
	result = 1.0 / ((2 * n+1)*(2 * n+1));
	for (i = -n; i < n+1; i += 1)
	{
		for (j = -n; j < n+1; j += 1)
		{
			if(y+i>=0 && j+x>0 && x+i<image.width && y+i<image.height)
			tmp = tmp + image.teinte[y+i][x+j];
		}
	}
	return result * tmp;
}

double sigma(Image image, int x, int y, int n)
{
	double result;
	double tmp;
	int i;
	int j;
	result=10;
	if(n!=-1)
		result = 1.0 / ((2 * n+1)*(2 * n+1));
	else result = 2000;

	tmp=0;
	for (i = -n; i < n+1; i += 1)
	{
		for (j = -n; j < n+1; j += 1)
		{
			if(y+i>=0 && j+x>0 && x+j<image.width && y+i<image.height)
			tmp = tmp + pow(image.teinte[y+i][x+j] - zncc2(image,x,y,n),2);
		}
	}
	
	return sqrt(result * tmp);
}

double zncc(Image image1, Image image2, int x1, int y1, int x2, int y2, int n)
{
	double result;
	double tmp;
	double sig;
	int i;
	int j;
	
	tmp = 0;
	result = 1.0 / ((2 * n+1)*(2 * n+1));
	sig = sigma(image1,x1,y1,n);
	if(sig != 0)
		result = result / sig;
	sig = sigma(image2,x2,y2,n);
	if(sig != 0)
		result = result / sig;
	else
		result = 2000;
	
	for (i = -n; i < n+1; i += 1)
	{
		for (j = -n; j < n+1; j += 1)
		{
			if(y1+i >=0 && y2+i>=0 && x1+j>=0 && x2+j>=0 && x1+j<image1.width && y1+i<image1.height && x2+j<image2.width && y2+i<image2.height)
				tmp = tmp + (image1.teinte[y1+i][x1+j]-zncc2(image1,x1,y1,n))*(image2.teinte[y2+i][x2+j]-zncc2(image2,x2,y2,n));
		}
	}
	
	return result * tmp;
}


void calculerDecalage(ListePoints* result, int xA, int yA, int xB, int yB, double valeur)
{
	result->x = xA - xB;
	result->y = yA - yB;
	result->valeur = valeur;
} 


double absolut(double a)
{
	if(a<0)
		return -a;
	else
		return a;
}
ListePoints decalageZNCC(ListePoints* liste1, Image image1, ListePoints* liste2, Image image2)
{
	ListePoints* tmp1;
	ListePoints* tmp2;
	ListePoints result;
	double valeur;
	tmp1 = liste1;
	result = nouveauListePoints(0,0,1);
	while(tmp1 != NULL)
	{
		tmp2=liste2;

		while(tmp2 != NULL)
		{
			valeur = zncc(image1,image2,tmp1->x,tmp1->y,tmp2->x,tmp2->y,5);
			if(absolut(valeur) < result.valeur )
				{calculerDecalage(&result,tmp1->x,tmp1->y,tmp2->x,tmp2->y,absolut(valeur));
			printf("Decalage : x-> %d y-> %d zncc-> %f\n",result.x,result.y,result.valeur);
			}
			tmp2 = tmp2->suivant;
		}
		tmp1 = tmp1->suivant;
	}
	return result;
}


/*
Pour chaque points de Harris de l'image de gauche
	Tant qu'il ny a pas de corresponsdance et qu'il reste des points de l'image de droite
		On calcul ZNCC(img1,img2,x1,y1,x2,y2,n)
		Si ZNCC < 0
			Ajout du décalage dans une liste
		
Ensuite on prend le décalage moyen.
*/
