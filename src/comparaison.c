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
		if(pow(liste->x-tete->x,2)+pow(liste->y-tete->y,2) < pow(n,2))
			ajoutFin(tete,liste->x,liste->y,liste->valeur);
		creerListePointsProche(tete,liste->suivant,n);
	}
}


ListePoints* reduireListe(ListePoints* liste, int n, int distance, int* bool_erreur)
{
	ListePoints* tmp;
	int k;
	int nombreMaxDeTest;
	nombreMaxDeTest = tailleListe(liste,0);
	k=0;
	tmp = NULL;
	while(tailleListe(tmp,0)<n && k< nombreMaxDeTest)
	{
		tmp = copieListe(positionListe(liste,(rand()%(tailleListe(liste,0)))));
		creerListePointsProche(tmp,liste,n*distance);
		k++;
	}
	if(k==nombreMaxDeTest)
	{
		*bool_erreur=1;
		erreur(NO_POINT_CLE,0);
	}
	return tmp;
 			/*Créer une liste contenant seulement les points autour du premier point pour éviter de tourner en rond a cause du random, vérifier que la taille de la liste est supérieur à n, de plus il faut arreter la boucle à un moment si il trouve rien*/
}

ListePoints** pointsRandom(ListePoints* liste, int n, int* bool_erreur)
 {
 	int i;
 	int ok;
 	int distanceMax;
 	ListePoints** tab;
 	ListePoints* tmp;
 	ListePoints* listeReduite;
 	distanceMax = 8;
 	tab=mallocBis(n*sizeof(ListePoints*));
 	tmp = reduireListe(liste,n,distanceMax, bool_erreur);
 	if(!*bool_erreur)
 	{
	 	listeReduite = tmp;	
	 	for(i=0;i<n;i++)
	 	{
	 		ok = 0;
	 		while(!ok && i)
	 		{
	 			tmp = positionListe(listeReduite,(rand()%(tailleListe(listeReduite,0))));
	 			ok = pasDansTableau(tab,i,tmp);
	 		}
	 		tab[i]=tmp;	
	 	}
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
	n=10;
	trouvePas = 1;
	printf("Comparaison des points : ");
	while(trouvePas && k < 20 && !*bool_erreur)
	{	
		fprintf(stdout," . ");
		ptsImage1=pointsRandom(liste1,n,bool_erreur);
		dernierPointValide = parcourtListe2(&trouvePas,liste2, ptsImage1,n);
		if(!trouvePas)
			calculerDecalage(&result,ptsImage1[n-1]->x,ptsImage1[n-1]->y,dernierPointValide->x,dernierPointValide->y,0);
		free(ptsImage1);
		k++;
	}
	if(trouvePas){
		erreur(NO_CORRESPONDANCE,0);
		*bool_erreur=1;
	}
	printf("\n");
	return result;
}	

