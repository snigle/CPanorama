#include "gestionListeCoordonnees.h"

/*Coordonnées*/

ListePoints nouveauListePoints (int x, int y, double valeur)
{
	ListePoints list_m;
	list_m.x = x;
	list_m.y = y;
	list_m.valeur = valeur;
	list_m.suivant = NULL;
	return(list_m);
}



/*GERER LISTE*/

ListePoints* copieListe(ListePoints* liste)
{
	ListePoints* result;
	result = NULL;
	result = ajoutCoordonnee(result,liste->x,liste->y,liste->valeur);
	return result;
}

ListePoints* creerlisteCoordonnees (int x, int y, double valeur)
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


void ajoutFin(ListePoints* list_p_listeCoordonnees, int x, int y, double valeur)
{
	ListePoints* list_p_fin;
	ListePoints* list_p_nouveau;
	list_p_fin = dernierListePoints(list_p_listeCoordonnees);
	list_p_nouveau = malloc (sizeof(ListePoints));
	*list_p_nouveau = nouveauListePoints(x, y, valeur);
	list_p_fin->suivant = list_p_nouveau;
}
/*Ajout d'une coordonnée*/

ListePoints* ajoutCoordonnee (ListePoints* list_p_listeCoordonnees, int x, int y, double valeur)
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

ListePoints* positionListe (ListePoints* list, int position)
{
	if(list == NULL || position < 1)
		return list;
	else
		return positionListe(list->suivant,position-1);
}

int tailleListe (ListePoints* list, int position)
{
	if(list == NULL)
		return position;
	else
		return tailleListe(list->suivant,position+1);
}

void afficherCoordonnees(ListePoints* liste)
{
	if (liste != NULL)
	{
		printf("(x = %d, y = %d, valeur = %f) -> ", liste -> x, liste -> y, liste -> valeur);
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
