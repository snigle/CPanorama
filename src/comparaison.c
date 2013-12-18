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

ListePoints** pointsRandom(ListePoints* liste, int n)
 {
 	int i;
 	int ok;
 	int k;
 	ListePoints** tab;
 	ListePoints* tmp;
 	
 	tab=mallocBis(n*sizeof(ListePoints*));
 	tmp = positionListe(liste,(rand()%(tailleListe(liste,0))));
 	for(i=0;i<n;i++)
 	{
 		ok = 0;

 		while(!ok && i && k<10000)
 		{
 			tmp = positionListe(liste,(rand()%(tailleListe(liste,0))));
 			ok = pasDansTableau(tab,i,tmp) && (distance(tmp,tab[i-1]) < 8 );
 			k++;
 		}
 		if(k>=10000){
 			tmp = positionListe(liste,(rand()%(tailleListe(liste,0))));
 			i=0;
 			k=0;
 			/*Créer une liste contenant seulement les points autour du premier point pour éviter de tourner en rond a cause du random, vérifier que la taille de la liste est supérieur à n, de plus il faut arreter la boucle à un moment si il trouve rien*/
 		}
 		tab[i]=tmp;	
 	}

	return (tab);
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
	result = NULL;
	while(liste !=NULL && result==NULL)
	{
		if(liste->x == pointA->x+vect->x && liste->y == pointA->y+vect->y)
		{
			result = liste;
		}
		liste=liste->suivant;
	}
	
	return result;
}


ListePoints* chercheMotif(int* trouvePas, ListePoints* parcourtListe, ListePoints* liste2, ListePoints** ptsImage1, int n)
{
	int i;
	ListePoints* tmp;
	ListePoints* vect;
	i=0;
	tmp = parcourtListe;
	*trouvePas = 0;
	while (i<n-1 && !*trouvePas)
	{
		/* Au lieu de prendre le vecteur pour la première itération, il faut tester tout les points et calculer la matrice de transformation puis le nouveaux vecteur en fonction de cette matrice
		*/
		vect = vecteur( ptsImage1[i],ptsImage1[i+1]);
		tmp = chercherAutour(liste2,tmp,vect);
		*trouvePas = (tmp ==NULL);
		if(!*trouvePas)
			*trouvePas = ptsImage1[i+1]->valeur != tmp->valeur;
		i++;
	}
	return tmp;
}

ListePoints* parcourtListe2(int* trouvePas, ListePoints* liste, ListePoints** tableauPoints, int n)	
{
	ListePoints* dernierPointValide;
	ListePoints* parcourtListe;
	parcourtListe = liste;
	while(parcourtListe!=NULL && *trouvePas)
	{
		dernierPointValide = chercheMotif(trouvePas, parcourtListe,liste,tableauPoints,n);
		parcourtListe=parcourtListe->suivant;
	}
	return dernierPointValide;
}	
		
ListePoints comparaison(ListePoints* liste1, ListePoints* liste2, int* bool_erreur)	
{	
	int k;
	int n;
	int trouvePas;
	ListePoints result;
	ListePoints* dernierPointValide;
	ListePoints** ptsImage1;
	k=0;
	n=30;
	trouvePas = 1;
	printf("Comparaison des points : ");
	while(trouvePas && k < 20)
	{	
		printf(" . ");
		ptsImage1=pointsRandom(liste1,n);
		dernierPointValide = parcourtListe2(&trouvePas,liste2, ptsImage1,n);
/*		fprintf(stderr,"Le dernier point : x %d, y %d\n",dernierPointValide->x,dernierPointValide->y);*/
		if(!trouvePas)
			calculerDecalage(&result,ptsImage1[n-1]->x,ptsImage1[n-1]->y,dernierPointValide->x,dernierPointValide->y,0);
		free(ptsImage1);
		k++;
	}
	if(trouvePas)
		erreur(ERREUR_FILTRE,1);
	printf("\n");
	return result;
}	

