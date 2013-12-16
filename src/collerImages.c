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
		hauteur=fmax(hImage1,(-decalage->y)+hImage1);
	}
	
	taille[0]=largeur;
	taille[1]=hauteur;
	return(taille);
	
}


int** fusion(ListePoints* decalage, int largeur, int hauteur, Image image1, Image image2)
{
	int** matImageFinale;
	int i;
	int j;
	matImageFinale=initMatrice(largeur, hauteur);
	
	if(decalage->x>0 && decalage->y>0){
		for(i=0;i<image1.width;i++){
			for(j=0;j<image1.height;j++){
				matImageFinale[j][i]=image1.teinte[j][i];
				}
			}
			
		for(i=decalage->x;i<image2.width+decalage->x;i++){
			for(j=decalage->y;j<image2.height+decalage->y;j++){
				matImageFinale[j][i]=image2.teinte[j-(decalage->y)][i-(decalage->x)];
			}
		}
		
	}
	
	
	/*if(decalage.x>0 && decalage.y<0){
		for(i=0;i<image1.width;i++){
			for (j = -decalage.y; j < image1.height - decalage.y; j += 1){
				matImageFinale[i][j]=image1.teinte[i][j+decalage.y];
			}
		}
		for (i = decalage.x; i < image2.width + decalage.x; i += 1){
			for (j = 0; j < image2.height; j += 1){
				matImageFinale[i][j]=image2.teinte[i-decalage.x][j];	
			}	
		}
	}
	if (decalage.x<0 && decalage.y>0){
		for (i = -decalage.x; i < image1.width-decalage.x; i += 1){
			for (j = 0; j < image1.height; j += 1){
				matImageFinale[i][j]=image1.teinte[i+decalage.x][j];
			}
		}
		for (i = 0; i < image2.width; i += 1){
			for (j = decalage.y; j < image2.height + decalage.y; j += 1){
				matImageFinale[i][j]=image2.teinte[i][j-decalage.y];		
			}
		}
	}
	if(decalage.x<0 && decalage.y<0)
	{
		for (i = -decalage.x; i < image1.width - decalage.x; i += 1){
			for (j = -decalage.y; j < image1.height - decalage.y; j += 1){
				matImageFinale[i][j]=image1.teinte[i-decalage.x][j-decalage.y];
			}
		}
		
		for (i = 0; i < image2.width; i += 1){
			for (j = 0; j < image2.height; j += 1){
				matImageFinale[i][j]=image2.teinte[i][j];
			}
		}
	} */
	
	return(matImageFinale);
}	

Image imageCollee(Image image1, Image image2, ListePoints* decalage)
{
	
	Image imageFinale;
	int teinteMax;
	int* size;
	int** matImageFinale;
	teinteMax=fmax(image1.teinteMax,image2.teinteMax);
	
	size=taille(decalage,image1.height,image2.height,image1.width,image2.width);
	
	matImageFinale=fusion(decalage, size[0], size[1],image1,image2);
	
	imageFinale=creationImage("P2",size[0],size[1],teinteMax, matImageFinale);
	
	return(imageFinale);
}





