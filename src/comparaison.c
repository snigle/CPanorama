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
 
 
ListePoints* pointsRandom(ListePoints* liste)
 {
 	int i;
 	ListePoints** tab;
 	
 	tab=mallocBis(3*sizeof(ListePoints*));
 	/*Verifier random pas deux fois pareil*/
 	for(i=0;i<3;i++)
 	{
 		tab[i]=positionListe(liste,(rand()%(tailleListe(liste))));	
 	}
	
	return(tab);
 }
 
 
ListePoints** points(ListePoints* Harris)
{	
	ListePoints** tab;
	ListePoints** Points;
	Points=mallocBis(3*sizeof(ListePoints*));
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
	result = ajoutCoordonnee(result,pointB->x-pointA->x,pointB->y-pointA->y);
	return result;
}

ListePoints* chercherAutour(ListePoints* liste, ListePoints* pointA, ListePoints* vect)
{
	ListePoints* result;
	int decalage;
	int i;
	decalage=4;
	result = NULL;
	while(liste !=NULL)
	{
		if(liste->x < pointA->x+vect->x+decalage && liste->x > pointA->x+vect->x-decalage && liste->y < pointA->y+vect->y+decalage && liste->y > pointA->y+vect->y-decalage)
		{
			if(result == NULL || pow(result->x - (pointA->x+vect->x),2) + pow(result->y -(pointA->y+vect->y),2) < pow(liste->x,2) - (pointA->x+vect->x) + liste->y -(pointA->y+vect->y)
			result = liste;
		}
		liste=liste->suivant;
	}
	
	return result;
}

ListePoints Comparaison(ListePoints* liste1, ListePoints* liste2, int* bool_erreur)	
{	
	int k;
	int i;
	int trouvePas;
	ListePoints result;
	ListePoints* parcoutListe2;
	ListePoints* tmp;
	ListePoints** ptsImage1;
	k=0;
	while(trouvePas AND k < 10000)
	{
		ptsImage1=points(liste1);
		parcoutListe2 = liste2;
		while(parcoutListe2!=NULL AND trouvePas)
		{
			i=0;
			tmp = parcoutListe2;
			/**Parcourt de la liste tant qu'on trouve une egalite*/
			while (i<2 && !trouvePas)
			{
				vect = vecteur( ptsImage1[i],ptsImage1[i+1]);
				tmp = chercherAutour(liste2,tmp,vect);
				trouvePas = (tmp ==NULL);
				i++;
			}
		
			parcoutListe2=parcoutListe2->suivant;
		}
		free(ptsImage1);
		k++;
	}
	if(trouvePas)
		exit("pas de points");
	else
		decalage(&result,tab[2]->x,tab[2]->y,tmp->x,tmp->y);
	return result;	
	
}	

