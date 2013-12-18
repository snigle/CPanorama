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
	newTeinte = initMatrice(image.width, image.height);
	for (i = 0; i < image.height; i += 1)
	{
		for (j = 0; j < image.width; j += 1)
		{
			transformationCoordonnee(&xp, &yp,image,i,j);
			if(yp>0 && xp>0 && yp<image.height && xp<image.width)
				newTeinte[yp][xp] = image.teinte[i][j];

		}
	}
	return newTeinte;
}

void recopieDesPoints(Image image, int** newTeinte)
{
	int i;
	int j;
	for (i = 0; i < image.width; i += 1)
	{
		for (j = 0; j < image.height; j += 1)
		{
			image.teinte[j][i] = newTeinte[j][i];
		}
	}
	libererMatrice((void**)newTeinte, image.height);
}

Image copieImage(Image image)
{
	int** result;
	int i;
	int j;
	result = initMatrice(image.width, image.height);
	for (i = 0; i < image.height; i += 1)
	{
		for (j = 0; j < image.width; j += 1)
		{
			result[i][j] = image.teinte[i][j];
		}
	}
	return (creationImage(image.type,image.width,image.height,image.teinteMax, result));
}

int** creationFiltre(void)
{
	int** filtre;
	filtre = initMatrice(3,3);
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

Image couleurVersDilatation(Image image, int* bool_erreur)
{
	int** newTeinte;
	Image temporaire;
	Image tmp;

	tmp = applicationConvolution(image, creationFiltre(), 3, bool_erreur);
	libererImage(image);
	image = creationImage(tmp.type, tmp.width, tmp.height, tmp.teinteMax, tmp.teinte);

	newTeinte = remplirMatriceBinaire(image, 100);

	tmp = creationImage("P1", image.width, image.height, image.teinteMax, newTeinte);
	libererImage(image);
/*	image=copieImage(tmp);*/
/*	libererImage(tmp);*/
/*	*/
/*	newTeinte = genererMatriceDilate(image);*/
/*	tmp = creationImage("P1", image.width, image.height, image.teinteMax, newTeinte);*/
/*	libererImage(image);*/

	
	image=copieImage(tmp);
	libererImage(tmp);
	
	newTeinte = genererMatriceErode(image);
	tmp = creationImage("P1", image.width, image.height, image.teinteMax, newTeinte);
	
	
	save(tmp, "out1", bool_erreur);
	printf("Ecriture de tempo");
/*	newTeinte = transformationCylidrique(image);*/
/*	recopieDesPoints(image, newTeinte);*/
/*	newTeinte = transformationCylidrique(temporaire);*/
/*	recopieDesPoints(temporaire, newTeinte);	*/
	return (tmp);
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

int panorama(char** input, int nombreInput, char* output, int* bool_erreur)
{

/*	Image result;*/
	ListePoints* ptsImage1;
	ListePoints* ptsImage2;
	ListePoints decalage;
	Image origine1;/*la premiere image d'origine puis le collage de deux images d'origine*/
	Image origine2;/*La nouvelle image à coller à chaque tour de boucle */
	Image temporaire1;/*l'image origine1 modifiée successivement par les opérations*/
	Image temporaire2;/*l'image origine modifiée successivement par les opérations*/
	Image collageOrigine;/*Les images d'origines collées après calculs*/
	Image collageTemporaire;/*collage des images traitées (après convolution et dilatation)*/
	int i;
	i = 1;


	origine1 = chargerImage(input[0], bool_erreur);
	while (i < nombreInput)
	{
		origine2 = chargerImage(input[i], bool_erreur);
		if(!strcmp(origine1.type,"P3")&&!strcmp(origine2.type,"P3"))
		{
			temporaire1 =  creerGrayScale(origine1);
			temporaire2 =  creerGrayScale(origine2);
		}
		else
		{
			temporaire1 =  copieImage(origine1);
			temporaire2 =  copieImage(origine2);
		}

		temporaire1 = couleurVersDilatation(temporaire1, bool_erreur);
		temporaire2 = couleurVersDilatation(temporaire2, bool_erreur);
		
/*		tompo2 = traitement*/
/*		liste1 = recuperationPixelsBlanc*/
/*		liste2 = recuperationPixelsBlanc*/
/*		decalage = comparer*/
/*		o1 = coller(o1,o2,dec)*/
/*		t1 = coller(t1,t2,dec)*/
		i++;
	}
	/*	decalage = comparaison(harris(im_image1,bool_erreur), harris(im_image2,bool_erreur), bool_erreur);
		printf(" x -> %d, y -> %d", decalage.x, decalage.y);
		
		imageFin=imageCollee(imageInput,imageInput2,decalage);
		save(imageFin,output, bool_erreur);
		printf("Image enregistrée dans %s \n",output);*/		
		/*
		
		
Vars : 
	Origine1
	Origine2
	Tempo1
	Tempo2
	
	Sphérique
	Si PPM
		Grayscale
	Si PGM
		Convolution
		-b médiane ou un peu plus
	Si PBM
		Dilate
		Erode
		(Dilate tant que le nombre de points est supérieur à N)
	SINON
		boom
		
		
	recup pixel blanc

	
	decalage
	
	Collage Origine1 et Origine2
	Collage Tempo1 et Tempo2
	*/


/*decalage = comparaison(image1, image2, bool_erreur);
	printf("Decalage : x-> %d y-> %d zncc-> %f \n" ,decalage.x,decalage.y,decalage.valeur);*/


/*	decalage=NULL;*/
/*	decalage=ajoutCoordonnee(decalage, 100, 400, 0);*/
/*	*/
/*	size=taille(decalage,imageInput.height,imageInput2.height,imageInput.width, imageInput2.width);*/
/*	*/
/*	printf("Largeur: %d hauteur : %d\n ",size[0], size[1]);*/
/*	printf("decalage en x : %d , decalage en y : %d \n", decalage->x, decalage->y);*/
/*	*/
/*	imageFin=imageCollee(imageInput,imageInput2,decalage);*/
/*	save(imageFin,output, bool_erreur);*/


	printf("Appel de la fonction Panorama\n");
	
	return 0;
}



/*
prendre un tableau d'image
charger les deux premieres

VERIFIER LES TYPES

égaliser leurs histogrammes
***2 SOLUTIONS***
	1- Utiliser Harris pour les points d'interets
	
	2- Convolution +  dilatation

*****************
algo de recherche des points avec homothétie, rotation etc... Bombage de l'image

OU

Trouver un algorithme de comparaison efficace


*/




