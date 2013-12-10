#ifndef __ROTATE_H__
#define __ROTATE_H__

#include <math.h>
#include "header.h"
#include "gestionFichier.h"




int** transformation(Image image);
Image rotate (char* str_input, char* str_output, int bool_save, int* bool_erreur);


#endif /* __ROTATE_H__ */


