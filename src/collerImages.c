#include "collerImages.h"

int* taille(ListePoints* decalage, int hImage1, int hImage2, int  lImage1, int lImage2)
{
	int hauteur;
	int largeur;
	int* taille;
	taille=mallocBis(2*sizeof(int));
	if(decalage->x>0 && decalage->y>0){
		largeur=fmax(lImage1,decalage->x + lImage2);
		hauteur=fmax(hImage1,decalage->y + hImage2);
	}
	if(decalage->x>0 && decalage->y<0){
		largeur=fmax(lImage1,decalage->x + lImage2);
		hauteur=fmax(hImage2,(-decalage->y)+hImage1);
	}
	if(decalage->x<0 && decalage->y>0){
		largeur=fmax(lImage2,(-decalage->x)+lImage1);
		hauteur=fmax(hImage1,decalage->y + hImage2);
	}
	if(decalage->x<0 && decalage->y<0){
		largeur=fmax(lImage2,(-decalage->x)+lImage1);
		hauteur=fmax(hImage2,(-decalage->y)+hImage1);
	}
	taille[0]=largeur;
	taille[1]=hauteur;
	return(taille);	
}

int estNoir(int** teinte, int y, int x, int k)
{
	int result;
	int f;
	result = 1;
	for (f = 0; f < k; f += 1)
	{
		result = result && teinte[y][x+f];
	}
	return result;
}

int pixelNoir(Image image, int x, int y, int ppm)
{
	int result;
	int i;
	result = 1;
	for (i = 0; i < ppm; i += 1)
	{
		result = result && !image.teinte[x][y+ppm*i];
	}
	
	return(result);
}

int** fusionCas1(ListePoints* decalage, int largeur, int hauteur, Image image1, Image image2)
{
	int** matImageFinale;
	int i;
	int j;
	int k;
	int f;
	k = !strcmp (image2.type,"P3") ? 3 :1;
	matImageFinale=initMatrice(0,largeur*k, hauteur);
	for(i=0;i<image1.width*k;i+=k){
		for(j=0;j<image1.height;j++){
			for (f = 0; f < k; f += 1){
				matImageFinale[j][i+f]=image1.teinte[j][i+f];
			}	
		}
	}		
		for(i=(decalage->x+image1.width)/2*k;i<(image2.width*k+decalage->x*k);i+=k){
			for(j=decalage->y;j<image2.height+decalage->y;j++){
				if(!pixelNoir(image2,j-(decalage->y),i-decalage->x*k+f,k))
				{
					for (f = 0; f < k; f += 1)
					matImageFinale[j][i+f] = image2.teinte[j-(decalage->y)][i-decalage->x*k+f];
				}
			}
		}
	return(matImageFinale);
}

int** fusionCas2(ListePoints* decalage, int largeur, int hauteur, Image image1, Image image2)
{
	int** matImageFinale;
	int i;
	int j;
	int k;
	int f;
	if(strcmp(image1.type,"P2")==0 && strcmp (image2.type,"P2")==0) k=1;
	if(strcmp(image1.type,"P3")==0 && strcmp (image2.type,"P3")==0) k=3;
	matImageFinale=initMatrice(0,largeur*k, hauteur);
	for(i=0;i<image1.width*k;i+=k){
		for (j = -decalage->y; j < image1.height - decalage->y; j += 1){
			for (f = 0; f < k; f += 1){
				matImageFinale[j][i+f]=image1.teinte[j+decalage->y][i+f];
			}	
		}
	}
	for (i = (decalage->x+ image1.width)*k/2; i < image2.width*k + decalage->x*k; i += k){
		for (j = 0; j < image2.height; j += 1){
			if(!pixelNoir(image2,j,i-decalage->x*k+f,k))
			{
				for (f = 0; f < k; f += 1){
					matImageFinale[j][i+f] = image2.teinte[j][i-decalage->x*k+f];
				}
			}	
		}	
	}
	return(matImageFinale);	
}

/*int** fusionCas3(ListePoints* decalage, int largeur, int hauteur, Image image1, Image image2)*/
/*{*/
/*	int** matImageFinale;*/
/*	int i;*/
/*	int j;*/
/*	int k;*/
/*	int f;*/
/*	if(strcmp(image1.type,"P2")==0 && strcmp (image2.type,"P2")==0) k=1;*/
/*	if(strcmp(image1.type,"P3")==0 && strcmp (image2.type,"P3")==0) k=3;*/
/*	matImageFinale=initMatrice(0,largeur*k, hauteur);*/
/*	for (i = -decalage->x*k; i < image1.width*k-decalage->x*k; i += k){*/
/*		for (j = 0; j < image1.height; j += 1){*/
/*			for (f = 0; f < k; f += 1){*/
/*				matImageFinale[j][i+f]=image1.teinte[j][i+decalage->x*k+f];*/
/*			}	*/
/*		}*/
/*	}*/
/*	for (i = 0; i < image2.width*k; i += k){*/
/*		for (j = decalage->y; j < image2.height + decalage->y; j += 1){*/
/*			for (f = 0; f < k; f += 1){*/
/*				if(matImageFinale[j][i+f	])*/
/*				matImageFinale[j][i+f] = (matImageFinale[j][i+f] + image2.teinte[j-decalage->y][i+f])/2;else*/
/*				matImageFinale[j][i+f]=image2.teinte[j-decalage->y][i+f];	*/
/*			}	*/
/*		}*/
/*	}*/
/*	return(matImageFinale);*/
/*}*/

/*int** fusionCas4(ListePoints* decalage, int largeur, int hauteur, Image image1, Image image2)*/
/*{*/
/*	int** matImageFinale;*/
/*	int i;*/
/*	int j;*/
/*	int k;*/
/*	int f;*/
/*	if(strcmp(image1.type,"P2")==0 && strcmp (image2.type,"P2")==0) k=1;*/
/*	if(strcmp(image1.type,"P3")==0 && strcmp (image2.type,"P3")==0) k=3;*/
/*	matImageFinale=initMatrice(0,largeur*k, hauteur);*/
/*	for (i = (-decalage->x-image1.width)/2*k; i < image1.width*k - decalage->x*k; i += k){*/
/*		for (j = -decalage->y; j < image1.height - decalage->y; j += 1){*/
/*			for (f = 0; f < k; f += 1){	*/
/*				matImageFinale[j][i+f]=image1.teinte[j+decalage->y][i+decalage->x*k+f];*/
/*			}*/
/*		}*/
/*	}*/
/*	for (i = 0; i < image2.width*k; i += k){*/
/*		for (j = 0; j < image2.height; j += 1){*/
/*			for (f = 0; f < k; f += 1){*/
/*				if(matImageFinale[j][i+f])*/
/*				matImageFinale[j][i+f] = (matImageFinale[j][i+f] + image2.teinte[j][i+f];*/
/*			}*/
/*		}*/
/*	}	*/
/*	return(matImageFinale);*/
/*}*/

int** fusion(ListePoints* decalage, int largeur, int hauteur, Image image1, Image image2)
{
	int** matImageFinale;
	if(decalage->x>0 && decalage->y>0){
		matImageFinale=fusionCas1(decalage, largeur, hauteur, image1, image2);
	}
	
	if(decalage->x>0 && decalage->y<0){
		matImageFinale=fusionCas2(decalage, largeur, hauteur, image1, image2);
	}
	if (decalage->x<0 && decalage->y>0){
		decalage->x = -decalage->x;
		decalage->y = -decalage->y;
		matImageFinale = fusionCas2(decalage, largeur, hauteur, image2, image1);
	}
	if(decalage->x<0 && decalage->y<0){
		decalage->x = -decalage->x;
		decalage->y = -decalage->y;
		matImageFinale=fusionCas1(decalage, largeur, hauteur, image2, image1);
	} 
	return(matImageFinale);
}	

Image imageCollee (Image image1, Image image2, ListePoints* decalage)
{
	Image imageFinale;
	int teinteMax;
	int* size;
	int** matImageFinale;
	char* type;
	if(strcmp(image1.type,"P2")==0 && strcmp (image2.type,"P2")==0) type="P2";
	if(strcmp(image1.type,"P3")==0 && strcmp (image2.type,"P3")==0) type="P3";
	teinteMax=fmax(image1.teinteMax,image2.teinteMax);
	
	size=taille(decalage,image1.height,image2.height,image1.width,image2.width);
	
	matImageFinale=fusion(decalage, size[0], size[1],image1,image2);
	
	imageFinale=creationImage(type,size[0],size[1],teinteMax, matImageFinale);
	
	return(imageFinale);
}





