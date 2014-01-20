#include "panorama.h"

ListePoints* recuperationPixelsBlanc(Image image)
{
	int i;
	int j;
	ListePoints* liste_resultat;
	liste_resultat = NULL;
	for (i = 0; i < image.height; i += 1)
	{
		for (j = 0; j < image.width; j += 1)
		{
			if (!image.teinte[i][j])
				liste_resultat = ajoutCoordonnee(liste_resultat, j, i, 0.);
		}
	}
	return(liste_resultat);
}

void transformationCoordonnee(int* x, int* y, Image image, int i, int j)
{
	double px;
	double py;
	double p2x;
	double p2y;
	double r;
	px = (2.0*j - image.width) / image.width;
	py = (2.0*i - image.height) / image.height;
	r = pow(px,2.0) + pow(py,2.0);
	p2x = px * (1.0 - 0.02 * r);
	p2y = py * (1.0 - 0.08 * r);
	*x = (p2x + 1)*image.width/2;
	*y = (p2y+1)*image.height/2;
}

int** transformationCylidrique(Image image)
{
	int** newTeinte;
	int i;
	int j;
	int xp;
	int yp;
	int k;
	int f;
	int teinteInit;
	k = !strcmp(image.type,"P3")? 3 : 1;
	teinteInit = !strcmp(image.type,"P1")? 1 : 0;
	newTeinte = initMatrice(teinteInit,image.width*k, image.height);
	for (i = 0; i < image.height; i += 1)
	{
		for (j = 0; j < image.width; j += 1)
		{
			transformationCoordonnee(&xp, &yp,image,i,j);
			for (f = 0; f < k; f += 1)
			{
/*				if(yp>0 && xp>0 && yp<image.height && xp<image.width)*/
				newTeinte[yp][xp*k+f] = image.teinte[i][j*k+f];
			}
		}
	}
	return newTeinte;
}

void transformationCylidriqueBis(Image image)
{
	int** newTeinte;
	newTeinte = transformationCylidrique(image);
	recopieDesPoints(image, newTeinte);
}

void recopieDesPoints(Image image, int** newTeinte)
{
	int i;
	int j;
	int k;
	int f;
	k = !strcmp(image.type,"P3")? 3 : 1;
	for (i = 0; i < image.width; i += 1)
	{
		for (j = 0; j < image.height; j += 1)
		{
			for (f = 0; f < k; f += 1)
			{
					image.teinte[j][i*k+f] = newTeinte[j][i*k+f];
			}

		}
	}
	libererMatrice((void**)newTeinte, image.height);
}

Image copieImage(Image image)
{
	int** result;
	int i;
	int j;
	int f;
	int k;
	k = !strcmp(image.type,"P3")? 3 : 1;
	result = initMatrice(0,image.width*k, image.height);
	for (i = 0; i < image.height; i += 1)
	{
		for (j = 0; j < image.width; j += 1)
		{
			for (f = 0; f < k; f += 1)
			{
							result[i][j*k+f] = image.teinte[i][j*k+f];
			}

		}
	}
	return (creationImage(image.type,image.width,image.height,image.teinteMax, result));
}

int** creationFiltre(void)
{
	int** filtre;
	filtre = initMatrice(0,3,3);
	filtre[0][0] = 1;
	filtre[0][1] = 1;
	filtre[0][2] = 1;
	

	filtre[1][0] = 0;
	filtre[1][1] = 0;
	filtre[1][2] = 0;
	
	filtre[2][0] = -1;
	filtre[2][1] = -1;
	filtre[2][2] = -1;
	
	return (filtre);
}

int compterVoisins(int x, int y, Image image)
{
	int i;
	int j;
	int k;
	k = 0;
	for (i = x-15; i <= x+15; i += 1)
	{
		for (j = y-15; j <= y+15; j += 1)
		{
			if (i > 0 && i < image.height && j > 0 && j < image.width )
				k = k+(1-image.teinte[i][j]);
		}	
	}
	return (k);
}


Image coupeVerticale(Image image, int direction)
{
	int i;
	int j;
	int tier;
	Image result;
	result = copieImage(image);
	tier = image.width / 3;
	
	direction = direction == 2 ? 1 : direction;
	for (i = direction * tier; i < image.height - (tier * (1-direction)); i += 1)
	{
		for (j = direction ; j < image.width ; j += 1)
		{
				result.teinte[i][j] = 1;
		}
	}
	
	return result;
}

Image coupeHorizontale(Image image, int direction)
{
	int i;
	int j;
	int tier;
	Image result;
	result = copieImage(image);
	tier = image.width / 3;
	
	direction = direction == 3 ? 0 : direction;
	for (i = 0; i < image.height; i += 1)
	{
			for (j = direction  * tier; j < image.width- (tier * (1 - direction)); j += 1)
			{
					result.teinte[i][j] = 1;
			}
	}
	
	return result;
	
}

Image coupe(Image image, int direction)
{
	Image result;
	
	if(direction == GAUCHE || direction == DROITE)
		result = coupeHorizontale(image,direction);
	else
		result = coupeVerticale(image, direction);
	
	return result;
}

void enleverPointImage(Image image)
{
	int i;
	int j;

	for (i = 0; i < image.height; i += 1)
	{
		for (j = 0; j < image.width; j += 1)
		{
			if (compterVoisins(i, j, image) < 22)
				image.teinte[i][j] = 1;
		}
	}	
}

void calculerTousLesDecalageBis(int image1, int cylindre, int direction, int image2, Image*** tab, Decalage* result)
{
	ListePoints* ptsImage1;
	ListePoints* ptsImage2;
	ListePoints* listeDecalage;
	ListePoints* decalage;
	int bool_erreur;
	bool_erreur = 0;
	ptsImage1 = recuperationPixelsBlanc(tab[image1][cylindre][direction]);
	ptsImage2 = recuperationPixelsBlanc(tab[image2][cylindre][(direction+2)%4]);
	listeDecalage = comparer( ptsImage1, ptsImage2, tab[image2][cylindre][(direction+2)%4], &bool_erreur);
	if(!bool_erreur)
	{
		decalage = maxListe(listeDecalage->suivant, listeDecalage);
		if(decalage->valeur>result->valeur.valeur)
		{
			result->valeur.x=decalage->x;
			result->valeur.y=decalage->y;
			result->valeur.valeur=decalage->valeur;
			result->cylindre = cylindre;
			result->direction=direction;
			result->positionImage=image2;
		}
	}
/*	else*/
/*	erreur(-1,EXIT);*/
}


void calculerTousLesDecalageBisBis(Image*** tab, int** decalageAPasCalculer, int nombreImage, int* tropDePoins, int l, int i, int j, Decalage* result, int* bool_erreur)
{	
	int k;
	if(*tropDePoins)
	{
		while(compterPointsBlanc(tab[l][i][j])>2000)
			tab[l][i][j] = applicationBinaire(tab[l][i][j],2, bool_erreur);
	}
	if(!decalageAPasCalculer[l][j])
	{	
		for (k = 0; k < nombreImage; k += 1)
		{
			if(k!=l)
			{
				printf(".");
				fflush(stdout);
				calculerTousLesDecalageBis(l,i,j,k,tab, result);
				 if(result->valeur.valeur > 1000)
					*tropDePoins = 1;
			}
		}
	}
	
				
}
Decalage* calculerTousLesDecalage(Image*** tab, int** decalageAPasCalculer, int nombreImage)
{
	int i;
	int j;
	int l;
	int tropDePoins;
	int bool_erreur;
	Decalage* result;
	tropDePoins = 0;
	result = (Decalage*) mallocBis(nombreImage * sizeof(Decalage));
	for (l = 0; l < nombreImage; l += 1)
	{
		result[l].valeur.valeur = 0;
		for (i = 0; i < 2; i += 1)
		{
			for (j = 0; j < 4; j += 1)
				calculerTousLesDecalageBisBis(tab,decalageAPasCalculer, nombreImage, &tropDePoins,  l, i, j, &result[l], &bool_erreur);
		}
		if(result[l].valeur.valeur!=0)
			decalageAPasCalculer[result[l].positionImage][(result[l].direction+2)%4]=1;
	}
	return result;
}

Image applicationBinaire(Image image, int toDo, int* bool_erreur)
{
	int** newTeinte;
	Image tmp;
	
	switch(toDo)
	{
		case 1:
			newTeinte = remplirMatriceBinaire(image, 100);
		break;
		case 2:
			newTeinte = genererMatriceDilate(image);
		break;
		default:
			newTeinte = genererMatriceErode(image);
		break;
	}
	tmp = creationImage("P1", image.width, image.height, image.teinteMax, newTeinte);
	libererImage(image);
	return (tmp);
	
}

int compterPointsBlanc(Image image)
{
	int result;
	int i;
	int j;
	result = 0;
	for (i = 0; i < image.height; i += 1)
	{
		for (j = 0; j < image.width; j += 1)
		{
			if(image.teinte[i][j]==0)
				result ++;
		}
	}
	return result;
}

Image couleurVersDilatation(Image image, int* bool_erreur)
{
	int i;
	Image tmp;
	tmp = applicationConvolution(image, creationFiltre(), 3, bool_erreur);
	libererImage(image);
	image = creationImage(tmp.type, tmp.width, tmp.height, tmp.teinteMax, tmp.teinte);
	
	image = applicationBinaire(image,1, bool_erreur);
	
	for (i = 0; i < 5; i += 1)
	{
		image = applicationBinaire(image,19, bool_erreur);
		image = applicationBinaire(image,2, bool_erreur);
		
	}
	return (image);
}

/*void egalisationImages (Image image1, Image image2, int* bool_erreur)*/
/*{*/
/*	int decalageIm1Im2;*/
/*	int* m1supm2;*/
/*	m1supm2 = malloc(sizeof(int));	*/
/*	decalageIm1Im2 = calculDecalage(image1, image2, m1supm2, bool_erreur);*/
/*	remplirNouvellesTeintes (image1, *m1supm2 * decalageIm1Im2);*/
/*	remplirNouvellesTeintes (image2, - *m1supm2 * decalageIm1Im2);*/
/*}*/

Image creerTemporaire(Image origine, int* bool_erreur)
{
	Image temporaire;
	
	if(!strcmp(origine.type,"P3"))
		temporaire =  creerGrayScale(origine);
	else
		temporaire =  copieImage(origine);

	temporaire = couleurVersDilatation(temporaire, bool_erreur);
	enleverPointImage(temporaire);

	return (temporaire);
}

Image* creationTableauImageCouleur(char** imageOrigine, int nombreImageOrigine, int* bool_erreur)
{
	Image* tableauImageCouleur;
	int i;
	tableauImageCouleur = mallocBis(nombreImageOrigine * sizeof(Image));
	for (i = 0; i < nombreImageOrigine; i += 1)
	{
		printf(".");
		fflush(stdout);
		tableauImageCouleur[i] = chargerImage(imageOrigine[i], bool_erreur);
	}
	if(!*bool_erreur)
	{
		for (i = 0; i < nombreImageOrigine-1; i += 1)
			*bool_erreur = *bool_erreur || strcmp(tableauImageCouleur[i].type,tableauImageCouleur[i+1].type);
		if(*bool_erreur)
			fprintf(stderr,"\nErreur : Les images doivent être du même type");
		else if(!strcmp(tableauImageCouleur[0].type,"P1"))
		{
			*bool_erreur = 1;
			fprintf(stderr,"\nErreur : Les fichiers PBM ne sont pas compatibles");
		}
	}
	return (tableauImageCouleur);	
}


Image** creationTableauImageTemporaire(Image* imageOrigine, int nombreImageOrigine, int* bool_erreur)
{
	Image** tableauImageTemporaire;
	int i;
	int ** newTeinte;
	
	tableauImageTemporaire= mallocBis(nombreImageOrigine * sizeof(Image*));
	
	for (i = 0; i < nombreImageOrigine; i += 1)
	{
		tableauImageTemporaire[i] = mallocBis(2*sizeof(Image));
	}

	for (i = 0; i < nombreImageOrigine; i += 1)
	{
		printf(".");
		fflush(stdout);
		tableauImageTemporaire[i][0] = creerTemporaire(imageOrigine[i], bool_erreur);
		newTeinte = transformationCylidrique(tableauImageTemporaire[i][0]);
		tableauImageTemporaire[i][1] = creationImage("P1",imageOrigine[i].width,imageOrigine[i].height ,1,newTeinte );
		

	}
	return (tableauImageTemporaire);	
}

void libererTableauImages(Image* tabImage, int nbImage)
{
	int i;
	for (i = 0; i < nbImage; i += 1)
	{
		libererImage(tabImage[i]);
	}
	
}

void libererTableauImages2(Image** tabImage, int nbImage)
{
	int i;
	int k;
	for (i = 0; i < nbImage; i += 1)
	{
		for (k = 0; k < 2; k += 1)
		{
				libererImage(tabImage[i][k]);
		}
	}
	free(tabImage);
}

Image*** creerTableauCoupe(Image** imageTemporaires, int nombreImage, int* bool_erreur)
{
	Image*** tableauCoupe;
	int i;
	int j;
	int k;
	tableauCoupe = initArbre(nombreImage);
	for (i = 0; i < nombreImage; i += 1)
	{
		for (j = 0; j < 2; j += 1)
		{
			for (k = 0; k < 4; k += 1)
			{	
				tableauCoupe[i][j][k] = coupe(imageTemporaires[i][j], k);
				while(compterPointsBlanc(tableauCoupe[i][j][k])>7000)
					tableauCoupe[i][j][k] = applicationBinaire(tableauCoupe[i][j][k],2, bool_erreur);

			}
		}
	}
	return (tableauCoupe);
}

int** genererTableauDecalageAPasCalculer(int nombreImage)
{
	int i;
	int k;
	int** result;
	result = mallocBis(sizeof(int*)*nombreImage);
	for (i = 0; i < nombreImage; i += 1)
	{
		result[i]= mallocBis(sizeof(int)*4);
		for (k = 0; k < 4; k += 1)
		{
			result[i][k]=0;
		}

	}
	return result;
}

ListePoints* initialisationTableauOrigine(Image* tableauImageCouleur, Decalage* decalages, int nombreImage)
{
	ListePoints* origine;
	int i;
	int cylindrique;
	cylindrique = 0;
	origine = mallocBis(sizeof(ListePoints)*nombreImage);
	for (i = 0; i < nombreImage; i += 1)
	{
		cylindrique = cylindrique || decalages[i].cylindre;
	}
	for (i = 0; i < nombreImage; i += 1)
	{
		if(cylindrique)
			transformationCylidriqueBis(tableauImageCouleur[i]);
		origine[i].x=0;
		origine[i].y=0;
	}
	return (origine);
}

void nouvellesOrigines(Decalage* decalages, ListePoints* origine, int i)
{
	if(decalages[i].valeur.x<0)
		origine[i].x-=decalages[i].valeur.x;
	else
		origine[decalages[i].positionImage].x+=decalages[i].valeur.x;
	if(decalages[i].valeur.y<0)
		origine[i].y-=decalages[i].valeur.y;
	else
		origine[decalages[i].positionImage].y+=decalages[i].valeur.y;
}


int recupererImagePlusGrande(Image* tableauImageCouleur, int nombreImage)
{
	int i;
	int result;
	ListePoints dimension;
	result = 1;
	dimension.x = tableauImageCouleur[0].width;
	dimension.y = tableauImageCouleur[0].height;
	for (i = 1; i < nombreImage; i += 1)
	{
		if (dimension.x <= tableauImageCouleur[i].width && dimension.y <= tableauImageCouleur[i].height)
		{
			result = i;
			dimension.x = tableauImageCouleur[i].width;
			dimension.y = tableauImageCouleur[i].height; 
		}
	}
	return (result);
}


int imageAvecMeilleurDecalage(Decalage* decalages, int nombreImage)
{
	Decalage decalageMax;
	int result;
	int i;
	
	decalageMax = decalages[0];
	result = 0;
	for (i = 1; i < nombreImage; i += 1)
	{
		if(decalageMax.valeur.valeur < decalages[i].valeur.valeur)
		{
			result = i;
			decalageMax = decalages[i];
		}
	}
	decalages[result].valeur.valeur = 0;
	return result;
}


Image collerToutesLesImages(Decalage* decalages, Image* tableauImageCouleur, int nombreImage)
{
	int i;
	int j;
	ListePoints* origine;
	Image tmp;
	origine = initialisationTableauOrigine(tableauImageCouleur, decalages, nombreImage);
	for (j = 0; j < nombreImage-1; j += 1)
	{
		i = imageAvecMeilleurDecalage(decalages, nombreImage);
		decalages[i].valeur.x+=origine[i].x;
		decalages[i].valeur.y+=origine[i].y;
		tmp = imageCollee(tableauImageCouleur[i], tableauImageCouleur[decalages[i].positionImage], decalages[i].valeur);
		tableauImageCouleur[i] = tmp;
		tableauImageCouleur[decalages[i].positionImage]=copieImage(tmp);
		nouvellesOrigines(decalages, origine, i);
	}
	return (copieImage(tableauImageCouleur[recupererImagePlusGrande(tableauImageCouleur, nombreImage)]));
}

/*void afficherDecalage(Decalage* decalages, int n)*/
/*{*/
/*	int i;*/
/*	for (i = 0; i < n; i += 1)*/
/*	{*/
/*		printf("\n****Image %d****\nDecalage %dx%d : %f\n",i,decalages[i].valeur.x,decalages[i].valeur.y,decalages[i].valeur.valeur);*/
/*		printf("Position image : %d\n",decalages[i].positionImage);*/
/*	}*/
/*}*/

Image traitementPanorama(Image* tableauImagesCouleur, int nombreInput, int* bool_erreur)
{
	Image** tableauImagesTemporaire;
	Image*** tabCoupes;
	Decalage* decalages;
	Image imageFin;
	int** decalageAPasCalculer;
	printf("\nRecherche des points clés : ");
	fflush(stdout);
	tableauImagesTemporaire = creationTableauImageTemporaire(tableauImagesCouleur, nombreInput, bool_erreur);
	if(!*bool_erreur)
	{
		tabCoupes = creerTableauCoupe(tableauImagesTemporaire, nombreInput, bool_erreur);
		if(!*bool_erreur)
		{
			decalageAPasCalculer = genererTableauDecalageAPasCalculer(nombreInput);
			printf("\nCalcul des décalages : ");
			fflush(stdout);
			decalages = calculerTousLesDecalage(tabCoupes, decalageAPasCalculer, nombreInput);
			libererTableauImages2(tableauImagesTemporaire, nombreInput);
			imageFin = collerToutesLesImages(decalages,tableauImagesCouleur, nombreInput);
		}
	}
	return(imageFin);
}



int panorama(char** input, int nombreInput, char* output, int* bool_erreur)
{
	Image* tableauImagesCouleur;
	Image panorama;
	printf("Chargement des images : ");
	fflush(stdout);
	tableauImagesCouleur = creationTableauImageCouleur(input, nombreInput, bool_erreur);
	if(!*bool_erreur && nombreInput > 1)
	{
		panorama = traitementPanorama(tableauImagesCouleur, nombreInput, bool_erreur);
		save(panorama, output, bool_erreur);
		if(!*bool_erreur)
			printf("\nLe panorama a été enregistré dans le fichier %s\n", output);
	}
	printf("\nFin du panorama \n");
	return 0;
}
