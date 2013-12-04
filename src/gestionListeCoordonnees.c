#include "gestionListeCoordonnees.h"

/*Coordonnées*/

ListePoints nouveauListePoints (int x, int y, int valeur)
{
	ListePoints list_m;
	list_m.x = x;
	list_m.y = y;
	list_m.valeur = valeur;
	list_m.suivant = NULL;
	return(list_m);
}



/*GERER LISTE*/

ListePoints* creerlisteCoordonnees (int x, int y, int valeur)
{
	ListePoints* list_p_maillon;
	list_p_maillon = malloc(sizeof(ListePoints));
	*list_p_maillon = nouveauListePoints(x, y, valeur);
	return (list_p_maillon);
}


ListePoints* dernierListePoints(ListePoints* list_p_listeCoordonnees)
{
	if (list_p_listeCoordonnees -> suivant == NULL)
	{
		return(list_p_listeCoordonnees);
	}
	else
	{
		return(dernierListePoints(list_p_listeCoordonnees -> suivant));
	}
}


void ajoutFin(ListePoints* list_p_listeCoordonnees, int x, int y, int valeur)
{
	ListePoints* list_p_fin;
	ListePoints* list_p_nouveau;
	list_p_fin = dernierListePoints(list_p_listeCoordonnees);
	list_p_nouveau = malloc (sizeof(ListePoints));
	*list_p_nouveau = nouveauListePoints(x, y, valeur);
	list_p_fin->suivant = list_p_nouveau;
}
/*Ajout d'une coordonnée*/

ListePoints* ajoutCoordonnee (ListePoints* list_p_listeCoordonnees, int x, int y, int valeur)
{
	if (list_p_listeCoordonnees == NULL)
	{
		return (creerlisteCoordonnees(x, y, valeur));
	}
	else
	{
		ajoutFin(list_p_listeCoordonnees, x, y, valeur);
		return (list_p_listeCoordonnees);		
	}
}

void afficherCoordonnees(ListePoints* liste)
{
	if (liste != NULL)
	{
		printf("(x = %d, y = %d, valeur = %d) -> ", liste -> x, liste -> y, liste -> valeur);
		afficherCoordonnees(liste -> suivant);
	}
	else printf("fin de liste\n");
}

void libererListe(ListePoints* list_p_liste)
{
	if (list_p_liste != NULL){
		if (list_p_liste -> suivant != NULL)
		{
			libererListe(list_p_liste->suivant);
		}
		free(list_p_liste);
	}
}

int tailleListe(ListePoints* liste)
{
	int i;
	i=0;
	while(liste!=NULL)
	{	
		i++;
		liste=liste->suivant;
	}
	
	return(i);
}

ListePoints* positionListe(ListePoints* liste, int position)
{
	int i;
	i=1;
	
	while(liste!=NULL && i==position)
	{	
		liste=liste->suivant;
		i++;
	}
	
	return(liste);
}

	
	
