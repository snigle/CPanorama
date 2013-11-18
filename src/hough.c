#include "hough.h"

Image hough(char* input,char* output, int bool_save, int* bool_erreur)
{
	Image imageInput;
	Image imageOutput;
	double theta_step;
	int i,j,t,x,y;
	double theta;
	int r_max,r;
	int** mat_A;
	int centreLigne;
	int centreColonne;
	
	printf("**%s --hough %s**\n",input,output);
	imageInput = chargerImage(input,bool_erreur);
	
	if(!*bool_erreur)
	{
		if(testType(imageInput,"P1"))
		{
			theta_step = imageInput.height / M_PI;
	
			r_max = ceil(sqrt(imageInput.height*imageInput.height + imageInput.width*imageInput.width) / 2) ;
			mat_A = initMatrice(r_max*2+1,imageInput.height);
	
			centreLigne = round(imageInput.height/2);
			centreColonne = round(imageInput.width/2);
	
			for (i = 0; i < imageInput.height; i += 1)
			{
				for (j = 0; j < imageInput.width; j += 1)
				{
					
					if(!imageInput.teinte[i][j]){
						x = i- centreLigne;
						y=j-centreColonne;
						for (t = 0; t < imageInput.height; t += 1)
						{
							theta = t * theta_step;
		r = r_max + 1 + round(x*cos(theta) +y*sin(theta));
							mat_A[t][r] = mat_A[t][r]+1;
						}
					}
			
				}
			}
			
			
			/****Tracer des lignes***/
			
			
			for (i = 0; i < imageInput.height; i += 1)
			{
				for (j = 0; j < r_max*2+1; j += 1)
				{
					if(mat_A[i][j]<100)
						mat_A[i][j]=0;
					else
						mat_A[i][j]=255;
				}
			}
			
			
			
			
			
			
			imageOutput = creationImage("P2",r_max*2+1,imageInput.height,255,mat_A);
			if(bool_save)
			{
				save(imageOutput, output, bool_erreur);
				if(!*bool_erreur) printf("\tLa représentation de Hough de %s est sauvegardé dans %s\n",input,output);
			}
		}
		else
			*bool_erreur = 1;
		libererImage(imageInput);
	}
	
	return imageOutput;
}
