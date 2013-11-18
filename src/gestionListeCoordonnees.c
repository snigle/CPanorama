#include "gestionListeCoordonnees.h"

/*Coordonnées*/
ListePoints nouveauListePoints (int x, int y, float valeur)
{
	ListePoints m;
	m.x = x;
	m.y = y;
	m.valeur = valeur;
	m.suivant = NULL;
	return(m);
}



/*GERER LISTE*/
ListePoints* creerlisteCoordonnees (int x, int y, float valeur)
{
	ListePoints* maillon;
	maillon = malloc(sizeof(ListePoints));
	*maillon = nouveauListePoints(x, y, valeur);
	return (maillon);
}


ListePoints* dernierListePoints(ListePoints* listeCoordonnees)
{
	if (listeCoordonnees -> suivant == NULL)
	{
		return(listeCoordonnees);
	}
	else
	{
		return(dernierListePoints(listeCoordonnees -> suivant));
	}
}

void ajoutFin(ListePoints* listeCoordonnees, int x, int y, float valeur) 
{
	ListePoints* fin;
	ListePoints* nouveau;
	fin = dernierListePoints(listeCoordonnees);
	nouveau = malloc (sizeof(ListePoints));
	*nouveau = nouveauListePoints(x, y, valeur);
	fin->suivant = nouveau;
}
/*Ajout d'une coordonnée*/
ListePoints* ajoutCoordonnee (ListePoints* listeCoordonnees, int x, int y, float valeur)
{
	if (listeCoordonnees == NULL)
	{
		return creerlisteCoordonnees(x, y, valeur);
	}
	else
	{
		ajoutFin(listeCoordonnees, x, y, valeur);
		return listeCoordonnees;		
	}
}

void afficherCoordonnees(ListePoints* liste)
{
	if (liste != NULL)
	{
		printf("(x = %d, y = %d, valeur = %f)\n ", liste->x, liste->y, liste->valeur);
		afficherCoordonnees(liste->suivant);
	}
	else printf("fin de liste\n");
}

void libererListe(ListePoints* liste)
{
	if (liste != NULL){
		if (liste -> suivant != NULL)
		{
			libererListe(liste->suivant);
		}
		free(liste);
	}
}
