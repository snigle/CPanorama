/*! \file gestionListeCoordonnees.h
 *  \author Perales Quentin <peralesque@eisti.eu>
 *  \version 0.1
 *  \date  Wed 13 Nov 2013
 *
 *  \brief gère une liste de coordonnées et d'un valeur asociée à chaque couple de coordonnées
 *
 *
 */
 
#ifndef __GESTIONLISTECOORDONNEES_H__
#define __GESTIONLISTECOORDONNEES_H__


#include "header.h"

typedef struct sListe
{
	int x;
	int y;
	double valeur;
	struct sListe* suivant;
}ListePoints;

/*!
       \fn ListePoints* maxListe(ListePoints* liste, ListePoints* max)
       \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
       \date dim. 19 janv. 2014
       \brief Renvoie le noeud ou la valeur de la liste est le maximum               
       \param liste : (listepoints*) Liste à tester
       \param max : (listepoints*) Premier noeud de la liste
       \return retourne le noeud maximum
               
       \remarks 

*/
ListePoints* maxListe(ListePoints* liste, ListePoints* max);

/*!
       \fn ListePoints copieListe(ListePoints* liste)
       \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
       \date dim. 19 janv. 2014
       \brief Fait une copie de la liste en mémoire               
       \param liste : (listepoints*) Liste à copier
       \return retourne l'adresse de la nouvelle liste
               
       \remarks 

*/
ListePoints* copieListe(ListePoints* liste);

/*!
       \fn ListePoints* positionListe(ListePoints* list, int position)
       \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
       \date dim. 19 janv. 2014
       \brief Renvoie le n ème noeud de la liste               
       \param list : (listepoints*) liste à tester
       \param position : (int) position du noeud à rechercher
       \return retourne le nème noeud
               
       \remarks 

*/
ListePoints* positionListe (ListePoints* list, int position);

/*!
       \fn int tailleListe(ListePoints* list, int position)
       \author LAMARCHE Ludovic <lamarchelu@eisti.eu>
       \date dim. 19 janv. 2014
       \brief Renvoie la taille d'une liste               
       \param list : (listepoints*) Liste à tester
       \param position : (int) incrémenteur de récursivité, mettre à 0
       \return retourne la taille de la liste
               
       \remarks 

*/
int tailleListe (ListePoints* list, int position);



/*!

       \fn ListePoints nouveauListePoints (int x, int y, double valeur)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Thu 07 Nov 2013
       \brief permet de creer un point avec une abscisse x, une ordonnées y et une valeur
       \param x : (int) l'abscisse du point
       \param y : (int) l'ordonnées du point
       \param valeur : (double) la valeur de ce point
       \return renvoie une structure de point
               
       \remarks 

*/

ListePoints nouveauListePoints (int x, int y, double valeur);

/*!
       \fn ListePoints* creerlisteCoordonnees (int x, int y, double valeur)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Thu 07 Nov 2013
       \brief creer un maillon d'une chaine, ce maillon represente une coordonnée               
       \param x : (int) l'abscisse du point
       \param y : (int) l'ordonnées du point
       \param valeur : (double) la valeur de ce point
       \return un pointeur vers NULL qui contient les informations d'un point
               
       \remarks 

*/

ListePoints* creerlisteCoordonnees (int x, int y, double valeur);


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
       \fn void ajoutFin(ListePoints* list_p_listeCoordonnees, int x, int y, double valeur) 
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Thu 07 Nov 2013
       \brief ajoute un point a la fin d'une liste de point               

       \param list_p_listecoordonnees : (listepoints*) la liste de points
       \param x : (int) l'abscisse du nouveau point
       \param y : (int) l'ordonnées du nouveau point
       \param valeur : (double) la valeur du nouveau point

       
               
       \remarks 

*/

void ajoutFin(ListePoints* list_p_listeCoordonnees, int x, int y, double valeur);


/*!
       \fn ListePoints* ajoutCoordonnee (ListePoints* list_p_listeCoordonnees, int x, int y, double valeur)
       \author PERALES Quentin <peralesque@eisti.eu>
       \date Thu 07 Nov 2013
       \brief ajoute un point a une liste de point si cette liste existe, sinon la fonction creer cette liste               

       \param list_p_listecoordonnees : (listepoints*) la liste de points
       \param x : (int) l'abscisse du nouveau point
       \param y : (int) l'ordonnées du nouveau point
       \param valeur : (double) la valeur du nouveau point

       \return une liste de points
               
       \remarks 

*/

ListePoints* ajoutCoordonnee (ListePoints* list_p_listeCoordonnees, int x, int y, double valeur);


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


	

#endif /* __GESTIONLISTECOORDONNEES_H__ */
