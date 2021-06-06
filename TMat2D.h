typedef struct matriz matriz;


matriz *matriz_create(int nrow, int ncol);
int matriz_free(matriz *auxliar);
int matriz_set(matriz *auxliar,int i, int j,double val);
int matriz_get(matriz *auxiliar,int i,int j,double *val);
int matriz_sum(matriz *mat1,matriz *mat2,matriz *sum,int i,int j);
int matriz_multiplication(matriz *mat1,matriz *mat2,matriz *multiplication,int i,int j);
int matriz_escalar(matriz *mat,matriz *escalar, float val);
int matriz_rastro(matriz *mat,double *sum);
int matriz_sum_linha(matriz *mat,double *sum);
int matriz_sum_coluna(matriz *mat,double *sum);
void matriz_print(matriz *mat);