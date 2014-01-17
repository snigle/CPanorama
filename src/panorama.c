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
				if(yp==0 && k==3)
					printf("xp %d\n",xp);
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
		printf("\n**Image : %d , Cylindre : %d , d1 : %d, d2 : %d Decalage %dx%d valeur %f",image1,cylindre,direction,(direction+2)%4,decalage->x,decalage->y,decalage->valeur);
		fflush(stdout);
	}
}

Decalage* calculerTousLesDecalage(Image*** tab, int** decalageAPasCalculer, int nombreImage)
{
	int i;
	int j;
	int k;
	int l;
	Decalage* result;
	result = (Decalage*) mallocBis(nombreImage * sizeof(Decalage));
	for (l = 0; l < nombreImage; l += 1)
	{
		result[l].valeur.valeur = 0;
		for (i = 0; i < 2; i += 1)
		{
			for (j = 0; j < 4; j += 1)
			{
				if(!decalageAPasCalculer[l][j])
				{	for (k = 0; k < nombreImage; k += 1)
					{
						if(k!=l)
						{
							printf(" . ");
							calculerTousLesDecalageBis(l,i,j,k,tab, &result[l]);
						}
					}
				}
			}
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

Image couleurVersDilatation(Image image, int cylindre,  int* bool_erreur)
{
	int i;
	Image tmp;

	tmp = applicationConvolution(image, creationFiltre(), 3, bool_erreur);
	libererImage(image);
	image = creationImage(tmp.type, tmp.width, tmp.height, tmp.teinteMax, tmp.teinte);
	
/*	if(cylindre){*/
/*	newTeinte = transformationCylidrique(image);*/
/*	recopieDesPoints(image, newTeinte);*/
/*	}	*/
	image = applicationBinaire(image,1, bool_erreur);
	
/*	if(cylindre)*/
/*	{*/
/*		transformationCylidriqueBis(image);*/
/*	}*/
	
	for (i = 0; i < 5; i += 1)
	{
		image = applicationBinaire(image,19, bool_erreur);
		image = applicationBinaire(image,2, bool_erreur);
		
	}
	return (image);
}

void egalisationImages (Image image1, Image image2, int* bool_erreur)
{
	int decalageIm1Im2;
	int* m1supm2;
	m1supm2 = malloc(sizeof(int));	
	decalageIm1Im2 = calculDecalage(image1, image2, m1supm2, bool_erreur);
	remplirNouvellesTeintes (image1, *m1supm2 * decalageIm1Im2);
	remplirNouvellesTeintes (image2, - *m1supm2 * decalageIm1Im2);
}

Image creerTemporaire(Image origine, int cylindre, int* bool_erreur)
{
	Image temporaire;
	
	if(!strcmp(origine.type,"P3"))
		temporaire =  creerGrayScale(origine);
	else
		temporaire =  copieImage(origine);

	temporaire = couleurVersDilatation(temporaire,cylindre, bool_erreur);
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
		tableauImageCouleur[i] = chargerImage(imageOrigine[i], bool_erreur);
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
		printf(" . ");
		fflush(stdout);
		tableauImageTemporaire[i][0] = creerTemporaire(imageOrigine[i],0, bool_erreur);
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
		printf("%d\n",i);
			fflush(stdout);
		for (j = 0; j < 2; j += 1)
		{
			for (k = 0; k < 4; k += 1)
			{			
				printf("\t\t%d\n",k);
				fflush(stdout);
				tableauCoupe[i][j][k] = coupe(imageTemporaires[i][j], k);
				while(compterPointsBlanc(tableauCoupe[i][j][k])>7000)
					tableauCoupe[i][j][k] = applicationBinaire(tableauCoupe[i][j][k],2, bool_erreur);

			}
		}
	}
	return (tableauCoupe);
}


void afficherDecalage(Decalage decalage)
{
	printf("Decalage : %dx%d valeur %f\nImage %d \nCylindre %d\n Direction %d\n",decalage.valeur.x, decalage.valeur.y, decalage.valeur.valeur, decalage.positionImage, decalage.cylindre, decalage.direction);
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

ListePoints* initialisationTableauOrigine(Image* tableauImageCouleur, int nombreImage)
{
	ListePoints* origine;
	int i;
	origine = mallocBis(sizeof(ListePoints)*nombreImage);
	for (i = 0; i < nombreImage; i += 1)
	{
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

void collerToutesLesImages(Decalage* decalages, Image* tableauImageCouleur, int nombreImage)
{
	int i;
	int bool_erreur;
	ListePoints* origine;
	Image tmp;
	bool_erreur=0;

	origine = initialisationTableauOrigine(tableauImageCouleur, nombreImage);
	for (i = 0; i < nombreImage-1; i += 1)
	{
		decalages[i].valeur.x+=origine[i].x;
		decalages[i].valeur.y+=origine[i].y;
		tmp = imageCollee(tableauImageCouleur[i], tableauImageCouleur[decalages[i].positionImage], &decalages[i].valeur);
/*		liberer tableauImageCouleur[i], tableauImageCouleur[decalages[i].positionImage]*/
		tableauImageCouleur[i] = tmp;
		tableauImageCouleur[decalages[i].positionImage]=tmp;
		nouvellesOrigines(decalages, origine, i);
	}
	save(tableauImageCouleur[nombreImage-2],"test",&bool_erreur);
}


int panorama(char** input, int nombreInput, char* output, int* bool_erreur)
{
	Image* tableauImagesCouleur;
	Image** tableauImagesTemporaire;
	Image*** tabCoupes;
	Decalage* decalages;
	int** decalageAPasCalculer;
	tableauImagesCouleur = creationTableauImageCouleur(input, nombreInput, bool_erreur);
	
	printf("chargement Image effectué \n");
	fflush(stdout);
	tableauImagesTemporaire = creationTableauImageTemporaire(tableauImagesCouleur, nombreInput, bool_erreur);
	printf("chargement Temporaire effectué\n");
	fflush(stdout);
/*suImagesTemporaire[2],"out3",bool_erreur);*/
	tabCoupes = creerTableauCoupe(tableauImagesTemporaire, nombreInput, bool_erreur);
	printf("chargement coupe \n");
	fflush(stdout);
	
	decalageAPasCalculer = genererTableauDecalageAPasCalculer(nombreInput);
	decalages = calculerTousLesDecalage(tabCoupes, decalageAPasCalculer, nombreInput);

		
	collerToutesLesImages(decalages,tableauImagesCouleur, nombreInput);
/*	for (i = 0; i < nombreInput; i += 1)*/
/*	{*/
/*		printf("\n****Decalage %d*****\n",i);*/
/*		afficherDecalage(decalages[i]);*/
/*	}*/
	
/*	libererTableauImages(tableauImagesCouleur, nombreInput);*/
/*	libererTableauImages2(tableauImagesTemporaire, nombreInput);*/

	


















	
	
	
	
	
	
	
/*	int i;*/
/*	i = 1;*/
/*	origine1 = chargerImage(input[0], bool_erreur);*/
/*	while (i < nombreInput)*/
/*	{*/
/*		origine2 = chargerImage(input[i], bool_erreur);*/
/*		if(!strcmp(origine1.type,"P3")&&!strcmp(origine2.type,"P3"))*/
/*		{*/
/*			temporaire1 =  creerGrayScale(origine1);*/
/*			temporaire2 =  creerGrayScale(origine2);*/
/*		}*/
/*		else*/
/*		{*/
/*			temporaire1 =  copieImage(origine1);*/
/*			temporaire2 =  copieImage(origine2);*/
/*		}*/
/*		if(!strcmp(temporaire1.type,"P2")&&!strcmp(temporaire2.type,"P2"))*/
/*		{*/
/*			egalisationImages (temporaire1, temporaire2, bool_erreur);*/
/*			temporaire1 = couleurVersDilatation(temporaire1, bool_erreur);*/
/*			temporaire2 = couleurVersDilatation(temporaire2, bool_erreur);*/
/*			*/
/*			enleverPointImage(temporaire1, 0);*/
/*			enleverPointImage(temporaire2, 1);*/
/*			*/
/*			while(compterPointsBlanc(temporaire1)>7000)*/
/*				temporaire1 = applicationBinaire(temporaire1,2, bool_erreur);*/
/*			while(compterPointsBlanc(temporaire2)>7000)*/
/*				temporaire2 = applicationBinaire(temporaire2,2, bool_erreur);	*/
/*			*/
/*			ptsImage1 = recuperationPixelsBlanc(temporaire1);*/
/*			ptsImage2 = recuperationPixelsBlanc(temporaire2);*/
/*			*/

/*	fprintf(stdout,"Avant comparer, taille : %d",tailleListe(ptsImage1,0));*/
/*			listeDecalage = comparer(ptsImage1, ptsImage2, temporaire2, bool_erreur);*/


/*			if(!*bool_erreur)*/
/*			{*/
/*				decalage = maxListe(listeDecalage->suivant, listeDecalage);*/
/*				afficherCoordonnees(decalage);*/
/*printf("test");*/
/*fflush(stdout);*/
/*				newTeinte = transformationCylidrique(origine2);*/
/*				recopieDesPoints(origine2, newTeinte);*/
/*		*/
/*				newTeinte = transformationCylidrique(origine1);*/
/*				recopieDesPoints(origine1, newTeinte);	*/
/*		*/
/*				tmp = imageCollee(origine1,origine2,decalage);*/
/*				printf("test");*/
/*fflush(stdout);*/
/*				save(tmp, "out1", bool_erreur);*/
/*			}*/
/*		}*/
/*		libererImage(origine1);*/
/*		libererImage(origine2);*/
/*		i++;*/
/*	}*/
	printf("Appel de la fonction Panorama\n");
	return 0;
}
