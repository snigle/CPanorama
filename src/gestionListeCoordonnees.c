#include "gestionListeCoordonnees.h"

/*Coordonnées*/
ListePoints nouveauListePoints (int int_x, int int_y, int int_valeur)
{
	ListePoints list_m;
	list_m.int_x = int_x;
	list_m.int_y = int_y;
	list_m.int_valeur = int_valeur;
	list_m.suivant = NULL;
	return(list_m);
}



/*GERER LISTE*/
ListePoints* creerlisteCoordonnees (int int_x, int int_y, int int_valeur)
{
	ListePoints* list_p_maillon;
	list_p_maillon = malloc(sizeof(ListePoints));
	*list_p_maillon = nouveauListePoints(int_x, int_y, int_valeur);
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

void ajoutFin(ListePoints* list_p_listeCoordonnees, int int_x, int int_y, int int_valeur) 
{
	ListePoints* list_p_fin;
	ListePoints* list_p_nouveau;
	list_p_fin = dernierListePoints(list_p_listeCoordonnees);
	list_p_nouveau = malloc (sizeof(ListePoints));
	*list_p_nouveau = nouveauListePoints(int_x, int_y, int_valeur);
	list_p_fin->suivant = list_p_nouveau;
}
/*Ajout d'une coordonnée*/
ListePoints* ajoutCoordonnee (ListePoints* list_p_listeCoordonnees, int int_x, int int_y, int int_valeur)
{
	if (list_p_listeCoordonnees == NULL)
	{
		return (creerlisteCoordonnees(int_x, int_y, int_valeur));
	}
	else
	{
		ajoutFin(list_p_listeCoordonnees, int_x, int_y, int_valeur);
		return (list_p_listeCoordonnees);		
	}
}

void afficherCoordonnees(ListePoints* liste)
{
	if (liste != NULL)
	{
		printf("(x = %d, y = %d, valeur = %d) -> ", liste -> int_x, liste -> int_y, liste -> int_valeur);
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
