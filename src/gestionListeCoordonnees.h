#include "header.h"

typedef struct sListe
{
	int x;
	int y;
	int valeur;
	struct sListe* suivant;
}ListePoints;

/*!
       \fn ListePoints nouveauListePoints(int x, int y, int valeur)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Thu 07 Nov 2013
       \brief permet de creer un point avec une abscisse x, une ordonnées y et une valeur
       \param x : (int) l'abscisse du point
       \param y : (int) l'ordonnées du point
       \param valeur : (int) la valeur de ce point
       \return renvoie une structure de point
               
       \remarks 

*/
ListePoints nouveauListePoints (int x, int y, int valeur);

/*!
       \fn ListePoints* creerlisteCoordonnees(int x, int y, int valeur)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Thu 07 Nov 2013
       \brief creer un maillon d'une chaine, ce maillon represente une coordonnée               
       \param x : (int) l'abscisse du point
       \param y : (int) l'ordonnées du point
       \param valeur : (int) la valeur de ce point
       \return un pointeur vers NULL qui contient les informations d'un point
               
       \remarks 

*/
ListePoints* creerlisteCoordonnees (int x, int y, int valeur);

/*!
       \fn ListePoints* dernierListePoints(ListePoints* listeCoordonnees)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Thu 07 Nov 2013
       \brief permet de récuperer le dernier maillon d'une chaine               
       \param listecoordonnees : (listepoints*) une liste de coordonnée
       \return le dernier point de la liste de point
               
       \remarks 

*/
ListePoints* dernierListePoints(ListePoints* listeCoordonnees);

/*!
       \fn void ajoutFin(ListePoints* listeCoordonnees, int x, int y, int valeur)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Thu 07 Nov 2013
       \brief ajoute un point a la fin d'une liste de point               
       \param listecoordonnees : (listepoints*) la liste de points
       \param x : (int) l'abscisse du nouveau point
       \param y : (int) l'ordonnées du nouveau point
       \param valeur : (int) la valeur du nouveau point
       
               
       \remarks 

*/
void ajoutFin(ListePoints* listeCoordonnees, int x, int y, int valeur);

/*!
       \fn ListePoints* ajoutCoordonnee(ListePoints* listeCoordonnees, int x, int y, int valeur)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Thu 07 Nov 2013
       \brief ajoute un point a une liste de point si cette liste existe, sinon la fonction creer cette liste               
       \param listecoordonnees : (listepoints*) la liste de points
       \param x : (int) l'abscisse du nouveau point
       \param y : (int) l'ordonnées du nouveau point
       \param valeur : (int) la valeur du nouveau point
       \return une liste de points
               
       \remarks 

*/
ListePoints* ajoutCoordonnee (ListePoints* listeCoordonnees, int x, int y, int valeur);

void afficherCoordonnees(ListePoints* liste);

/*!
       \fn void libererListe(ListePoints* liste)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Thu 07 Nov 2013
       \brief supprime les points et efface les pointeurs de la mémoire               
       \param liste : (listepoints*) une liste de points
       
               
       \remarks 

*/
void libererListe(ListePoints* liste);
