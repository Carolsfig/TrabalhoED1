#ifndef _TMat2dh_
#define _TMat2dh_
//Matriz de inteiros.
typedef struct matriz matriz;

matriz *matriz_create(int nrow, int ncol);
int matriz_free(matriz *auxiliar);
int matriz_set(matriz *auxiliar, int i, int j, int val);
int matriz_get(matriz *auxiliar, int i, int j, int *val);
int matriz_print(matriz *mat);

int matriz_get_dados(matriz *mat, int *column, int *line);
int matriz_get_column(matriz *mat, int *column);
int matriz_get_line(matriz *mat, int *line);

#endif