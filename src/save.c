/*! \file  save.c
	\author Poussou Elie poussoueli@eisti.eu
	\date Thu 26 Sep 2013
	
	\brief sauvegarde d'une image                                   
	

*/

int save(Image image, char* output)
{
	FILE* = fich;
	int taille;
	taille = image.width * image.heigth;
	int* tabGrey;
	int i;

	fich=fopen(output, "w");
	fprintf(fich,"%s\n",image.type);
	fprintf(fich,"%d\t",image.width);
	fprintf(fich,"%d\n",image.heigth);
	fprintf(fich,"%d\n",image.teinteMax);


	for(i=0;i<taille;i++)
	{
		if(!strcmp(image.type,"P3"))
			fprintf(fich,"%d\t%d\t%d\n",image.teinte[i*3],image.teinte[i*3+1],image.teinte[i*3+2]);
		else
			fprintf(fich,"%d\n",image.teinte[i]);	
	}
	
	fclose(fich);
	return 0;
}
	

	
