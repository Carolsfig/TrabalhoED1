#ifndef _TMat2dh_
#define _TMat2dh_
//Matriz de inteiros.
typedef struct matriz matriz;

matriz *matriz_create(int nrow, int ncol, int profundidade, char tipo[3]);
int matriz_free(matriz *auxliar);
int matriz_set(matriz *auxliar, int i, int j, int val);
int matriz_get(matriz *auxiliar, int i, int j, int *val);
int matriz_sum(matriz *mat1, matriz *mat2, matriz *sum, int i, int j);
int matriz_multiplication(matriz *mat1, matriz *mat2, matriz *multiplication, int i, int j);
int matriz_escalar(matriz *mat, matriz *escalar, float val);
int matriz_rastro(matriz *mat, int *sum);
int matriz_sum_linha(matriz *mat, int *sum);
int matriz_sum_coluna(matriz *mat, int *sum);
void matriz_print(matriz *mat);
#endif