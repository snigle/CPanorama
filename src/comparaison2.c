#include "comparaison2.h"


int pasDansTableau(ListePoints** tab, int taille, ListePoints* point)
{
	int i;
	int result;
	result=1;
	i=0;
	while(result && i<taille)
	{
		result = result && !(tab[i]->x==point->x && tab[i]->y==point->y);
		i++;
	}
	return result;
}

void creerListePointsProche(ListePoints* tete, ListePoints* liste, int n)
{
	if(liste!=NULL)
	{
		if(abs(liste->x-tete->x)< n && abs(liste->y-tete->y) < n)
			ajoutFin(tete,liste->x,liste->y,liste->valeur);
		creerListePointsProche(tete,liste->suivant,n);
	}
}

ListePoints* vecteur(ListePoints* pointA,ListePoints* pointB )
{
	ListePoints* result;
	result = NULL;
	result = ajoutCoordonnee(result,pointB->x-pointA->x,pointB->y-pointA->y,0);
	return result;
}

ListePoints* comparerVecteurs(ListePoints** tableauPoints,int tailleTableau, ListePoints* liste2, Image image2)
{
	/*
		|Parcourt de la liste 2 tant que trouvePas 200
		->	|Parcourt du tableauPoints tant que Trouve 10
			->|calculer vecteur tab[0],tab[i] 2000
				|chercher un point de tmp vers le vecteur.
	*/
	int trouvePas;
	int i;
	ListePoints* vect;
	trouvePas=1;
	while(liste2 != NULL && trouvePas)
	{
		i = 1;
		trouvePas = 0;
		while (!trouvePas && i<tailleTableau)
		{
			vect = vecteur(tableauPoints[0],tableauPoints[i]);
			if(liste2->y+vect->y>=0 && liste2->y+vect->y < image2.height && liste2->x+vect->x>=0 && liste2->x+vect->x < image2.width)
			{
				trouvePas = image2.teinte[liste2->y+vect->y][liste2->x+vect->x];
			}
			else
				trouvePas = 1;
			
			i++;
			libererListe(vect);
		}
		if(trouvePas)
		{
			liste2=liste2->suivant;
		}

	}
	
	return liste2;
}

ListePoints** tableauPointsAutour(ListePoints* point1, ListePoints* liste1, int n, int* bool_erreur)
{
	ListePoints** result;
	int i;
	ListePoints* tmp;
	result=mallocBis(sizeof(ListePoints*)*n);
	result[0] = ajoutCoordonnee(NULL,point1->x,point1->y,point1->valeur);
	point1 = ajoutCoordonnee(NULL,point1->x,point1->y,point1->valeur);
	creerListePointsProche(point1,liste1,15);
	liste1 = point1;
	if(tailleListe(liste1,0)>n)
	{
		for (i = 1; i < n; i += 1)
		{
			do
			{
/*				printf("t");*/
/*				fflush(stdout);*/
				tmp = positionListe(liste1,(rand()%(tailleListe(liste1,0))));
			}while(!pasDansTableau(result,i,tmp));
			result[i] = ajoutCoordonnee(NULL,tmp->x,tmp->y,tmp->valeur);
		}
	}
	else
		*bool_erreur = 1;
	libererListe(liste1);
	return result;
}

ListePoints calculerDecalage(int xA, int yA, int xB, int yB, double valeur)
{
	ListePoints result;
	result.x = xA - xB;
	result.y = yA - yB;
	result.valeur = valeur;
	return result;
} 

ListePoints* ajouterDecalage(ListePoints* tete, ListePoints* liste, ListePoints decalage)
{
	if(tete==NULL)
		return ajoutCoordonnee(NULL,decalage.x, decalage.y, 1);
	else if(decalage.x == liste->x && decalage.y == liste->y)
	{
		liste->valeur++;
		return tete;
	}
	else if(liste->suivant == NULL)
	{
		ajoutFin(liste,decalage.x,decalage.y,1);
		return tete;
	}
	else
		return ajouterDecalage(tete,liste->suivant, decalage);
}

ListePoints* comparer(ListePoints* liste1, ListePoints* liste2, Image image2, int* bool_erreur)
{
	/*
	Parcourt de la liste 1 tant que TrouvePas								2000
		|On prend un tableau de N points autour à M pixel près		4000
		bool comparerVecteurs()
	Calculer décalage
	*/
	ListePoints* result;
	int k;
	ListePoints* parcourtListe1;
	ListePoints* dernierPointValide;
	ListePoints** tabRandom;
	parcourtListe1=liste1;
	dernierPointValide=NULL;
	k=0;
	result = NULL;
	while(parcourtListe1!=NULL)
	{
		*bool_erreur=0;
/*		fprintf(stdout," . ");*/
/*		fflush(stdout);*/
/*		parcourtListe1 = positionListe(liste1,(rand()%(tailleListe(liste1,0))));*/

		tabRandom = tableauPointsAutour(parcourtListe1, liste1, 20, bool_erreur);
		if(!*bool_erreur)
		{
			dernierPointValide = comparerVecteurs(tabRandom,20,liste2,image2);

	/*		for (i = 0; i < 10; i += 1)*/
	/*		{*/
	/*			printf("Tab %d : %dx%d - ",i,tabRandom[i]->x,tabRandom[i]->y);*/
	/*		}*/
			if(dernierPointValide!=NULL)
			{	
				result = ajouterDecalage(result, result, calculerDecalage(tabRandom[0]->x,tabRandom[0]->y,dernierPointValide->x,dernierPointValide->y,0));
			}
			free(tabRandom);
		}
		parcourtListe1=parcourtListe1->suivant;
		k++;
	}
	if(result == NULL)
	{
/*		erreur(ERREUR_PARAMETRE,1);*/
		*bool_erreur=1;
	}
	else
		*bool_erreur=0;
	
	return result;
}

/*
	2000*4000 + 2000*2000*10= 8 000 000 000 => 14s * 10 = 2mn
	
*/
