/* - Prendre 3 points random, calculer les vecteurs AB, BC et AC. 
 prendre 3 points random dans l'autre image et voir si les autres points tombent dans la même zone. 
 D'abord 3 nombre aléatoire entre 0 et taille de la liste de points
 Puis calculer les vecteurs
 
 Pour chaque point de harris
 	B'=calculerVecteur (A,B)
 	si(B"=charcherautour(B')=vrai)
 		Ajouter dans la liste
 	sinon on recommance			
 	
 */
#include "comparaison.h"
 
int distance(ListePoints* pointA, ListePoints* pointB)
{
	return sqrt(pow((float) (pointB->x - pointA->x),2) + pow((float) (pointB->y - pointA->y),2));
}

ListePoints** pointsRandom(ListePoints* liste)
 {
 	int i;
 	int ok;
 	ListePoints** tab;
 	ListePoints* tmp;
 	
 	tab=mallocBis(5*sizeof(ListePoints*));
 	/*Verifier random pas deux fois pareil*/
/* 	printf("****RECHERCHE POINTS***\n");*/
 	tmp = positionListe(liste,(rand()%(tailleListe(liste,0))));
 	for(i=0;i<5;i++)
 	{
 		ok = 0;
 		while(!ok && i)
 		{
 			tmp = positionListe(liste,(rand()%(tailleListe(liste,0))));
/* 			printf("Distance : %d\n",distance(tmp,tab[i-1]));*/
 			ok = distance(tmp,tab[i-1]) < 80;
 		}
 		tab[i]=tmp;	
 	}
/* 	printf("****************Affichage points**********\n");*/
/*	for (i = 0; i < 4; i += 1)*/
/*	{*/
/*		printf("Point %d : x %d y %d\n",i,tab[i]->x,tab[i]->y);*/
/*	}*/
/*	printf("Distance %d\n",distance(tab[2],tab[1]));*/
	return (tab);
 }
 
 
ListePoints** points(ListePoints* Harris)
{	
	ListePoints** tab;
	tab=pointsRandom(Harris);
	
	return(tab);
	/*Tableau de coordonnées de points.*/
}
 
/*Faire fonction chercher autour*/
int vecteurX(ListePoints* liste)
{
	int xA;
	xA=((liste->x)-(liste->suivant->x));
	return(xA);
}

int vecteurY(ListePoints* liste)
{
	int yA;
	yA=((liste->y)-(liste->suivant->y));
	return(yA);
}

ListePoints* vecteur(ListePoints* pointA,ListePoints* pointB )
{
	ListePoints* result;
	result = NULL;
	result = ajoutCoordonnee(result,pointB->x-pointA->x,pointB->y-pointA->y,0);
	return result;
}

ListePoints* chercherAutour(ListePoints* liste, ListePoints* pointA, ListePoints* vect)
{
	ListePoints* result;
	int decalage;
	decalage=1;
	result = NULL;
	while(liste !=NULL)
	{
/*		if(liste->x < pointA->x+vect->x+decalage && liste->x > pointA->x+vect->x-decalage && liste->y < pointA->y+vect->y+decalage && liste->y > pointA->y+vect->y-decalage)*/
/*		{*/
/*			if(result == NULL || pow(result->x - (pointA->x+vect->x),2) + pow(result->y -(pointA->y+vect->y),2) < pow(liste->x,2) - (pointA->x+vect->x) + liste->y -(pointA->y+vect->y))*/
/*			result = liste;*/
/*		}*/
		if(liste->x == pointA->x+vect->x && liste->y == pointA->y+vect->y)
		{
			if(result == NULL || pow(result->x - (pointA->x+vect->x),2) + pow(result->y -(pointA->y+vect->y),2) == pow(liste->x,2) - (pointA->x+vect->x) + liste->y -(pointA->y+vect->y))
			{
				result = liste;
			}
		}
		liste=liste->suivant;
	}
	
	return result;
}

ListePoints comparaison(ListePoints* liste1, ListePoints* liste2, int* bool_erreur)	
{	
	int k;
	int i;
	int trouvePas;
	ListePoints result;
	ListePoints* parcoutListe2;
	ListePoints* tmp;
	ListePoints* vect;
	ListePoints** ptsImage1;
	k=0;
	trouvePas = 1;
/*	printf("**********TMP***********\n");*/
	while(trouvePas && k < 10000)
	{
		ptsImage1=points(liste1);
		parcoutListe2 = liste2;
		while(parcoutListe2!=NULL && trouvePas)
		{
			i=0;
			tmp = parcoutListe2;
			/**Parcourt de la liste tant qu'on trouve une egalite*/		trouvePas = 0;
/*			printf("Tmp %d : x %d y %d\n",i,tmp->x,tmp->y);*/
			while (i<4 && !trouvePas)
			{
				vect = vecteur( ptsImage1[i],ptsImage1[i+1]);
				tmp = chercherAutour(liste2,tmp,vect);
				trouvePas = (tmp ==NULL);
/*				if(!trouvePas)*/
/*					printf("Tmp %d : x %d y %d\n",i+1,tmp->x,tmp->y);*/
				i++;
			}
			parcoutListe2=parcoutListe2->suivant;
		}
		if(trouvePas)
			free(ptsImage1);
		k++;
	}
	if(trouvePas)
		erreur(ERREUR_FILTRE,1);
	else
		calculerDecalage(&result,ptsImage1[3]->x,ptsImage1[3]->y,tmp->x,tmp->y,0);
	
	return result;
	
}	

