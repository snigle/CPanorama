/*! \file gestionListeCoordonnees.h
 *  \author Perales Quentin <peralesque@eisti.eu>
 *  \version 0.1
 *  \date  Wed 13 Nov 2013
 *
 *  \brief gère une liste de coordonnées et d'un valeur asociée à chaque couple de coordonnées
 *
 *
 */

#include "header.h"

typedef struct sListe
{
	int int_x;
	int int_y;
	int int_valeur;
	struct sListe* suivant;
}ListePoints;

/*!
       \fn ListePoints nouveauListePoints (int int_x, int int_y, int int_valeur)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Thu 07 Nov 2013
       \brief permet de creer un point avec une abscisse x, une ordonnées y et une valeur
       \param int_x : (int) l'abscisse du point
       \param int_y : (int) l'ordonnées du point
       \param int_valeur : (int) la valeur de ce point
       \return renvoie une structure de point
               
       \remarks 

*/
ListePoints nouveauListePoints (int int_x, int int_y, int int_valeur);

/*!
       \fn ListePoints* creerlisteCoordonnees (int int_x, int int_y, int int_valeur)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Thu 07 Nov 2013
       \brief creer un maillon d'une chaine, ce maillon represente une coordonnée               
       \param int_x : (int) l'abscisse du point
       \param int_y : (int) l'ordonnées du point
       \param int_valeur : (int) la valeur de ce point
       \return un pointeur vers NULL qui contient les informations d'un point
               
       \remarks 

*/
ListePoints* creerlisteCoordonnees (int int_x, int int_y, int int_valeur);

/*!
       \fn ListePoints* dernierListePoints(ListePoints* list_p_listeCoordonnees)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Thu 07 Nov 2013
       \brief permet de récuperer le dernier maillon d'une chaine               
       \param list_p_listecoordonnees : (listepoints*) une liste de coordonnée
       \return le dernier point de la liste de point
               
       \remarks 

*/
ListePoints* dernierListePoints(ListePoints* list_p_listeCoordonnees);

/*!
       \fn void ajoutFin(ListePoints* list_p_listeCoordonnees, int int_x, int int_y, int int_valeur) 
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Thu 07 Nov 2013
       \brief ajoute un point a la fin d'une liste de point               
       \param list_p_listecoordonnees : (listepoints*) la liste de points
       \param int_x : (int) l'abscisse du nouveau point
       \param int_y : (int) l'ordonnées du nouveau point
       \param int_valeur : (int) la valeur du nouveau point
       
               
       \remarks 

*/
void ajoutFin(ListePoints* list_p_listeCoordonnees, int int_x, int int_y, int int_valeur);

/*!
       \fn ListePoints* ajoutCoordonnee (ListePoints* list_p_listeCoordonnees, int int_x, int int_y, int int_valeur)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Thu 07 Nov 2013
       \brief ajoute un point a une liste de point si cette liste existe, sinon la fonction creer cette liste               
       \param list_p_listecoordonnees : (listepoints*) la liste de points
       \param int_x : (int) l'abscisse du nouveau point
       \param int_y : (int) l'ordonnées du nouveau point
       \param int_valeur : (int) la valeur du nouveau point
       \return une liste de points
               
       \remarks 

*/
ListePoints* ajoutCoordonnee (ListePoints* list_p_listeCoordonnees, int int_x, int int_y, int int_valeur);

void afficherCoordonnees(ListePoints* liste);

/*!
       \fn void libererListe(ListePoints* list_p_liste)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Thu 07 Nov 2013
       \brief supprime les points et efface les pointeurs de la mémoire               
       \param list_p_liste : (listepoints*) une liste de points
       
               
       \remarks 

*/
void libererListe(ListePoints* list_p_liste);
