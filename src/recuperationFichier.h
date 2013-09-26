#include "header.h"

void allerAlaLigne (FILE* fichier);
void sauterCommentaire(FILE* fichier);
void recupType(char* tab, FILE* image);
int parametrage(FILE* image);
int teinteMax(char type[3], FILE* image);
void recuperationPixels(FILE* fichier, int* tab, int tailleTotale);
int* recupPixel(FILE* fichier, int largeur, int hauteur, char* type);
Image chargerImage(char* nomImage);
int save(Image image, char* output);
