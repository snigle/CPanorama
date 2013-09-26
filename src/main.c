 /*! \file main.c
  *  \author Lamarche Ludovic <lamarchelu@eisti.eu>
  *  \version 0.1
  *  \date Mon 23 Sep 2013
  *
  *  \brief Projet panorama
  *
  *
  */
  
#include "ordonanceur.h"

 

 
 int main (int argc, char** argv)
 {
 	int num;
 	printf("Debut du programme");
 	num = gererOptions(argc,argv);
 	if (num)
 		erreur(num);
 	return 0;
 }
 
