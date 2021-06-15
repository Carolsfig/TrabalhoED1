#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TMat2D.h"

struct matriz
{
  
    int nrow;
    int ncol;
    int *data;
};

matriz *matriz_create(int nrow, int ncol)
{
    matriz *auxiliar;
    auxiliar = malloc(sizeof(matriz));
    if (auxiliar == NULL)
    {
        return NULL;
    }
    else
    {
        auxiliar->nrow = nrow;
        auxiliar->ncol = ncol;
        auxiliar->data = malloc((ncol * nrow) * sizeof(int));
        if (auxiliar->data == NULL)
        {
            free(auxiliar);
            return NULL;
        }
        return auxiliar;
    }
    return NULL;
}

int matriz_free(matriz *auxliar)
{
    if (auxliar == NULL)
    {
        return -1;
    }
    else
    {
        free(auxliar->data);
        free(auxliar);
        return 0;
    }
}

int matriz_set(matriz *auxliar, int i, int j, int val)
{
    int aux;
    aux = j * auxliar->ncol + i;
    auxliar->data[aux] = val;
    return 0;
}
int matriz_get(matriz *auxiliar, int i, int j, int *val)
{
    int pos;
    pos = j * auxiliar->ncol + i;
    *val = auxiliar->data[pos];
    return 0;
}



void matriz_print(matriz *mat)
{       
    
    int aux;
    for (int i = 0; i <  mat->nrow; i++)
    {
        for (int j = 0; j <mat->ncol; j++)
        {
            matriz_get(mat, j,i, &aux);
            printf("%d\t ", aux);
        }
        printf("\n");
    }
}

int matriz_get_dados(matriz *mat, int *column, int *line)
{
    *column = mat->ncol;
    *line = mat->nrow;
}

int matriz_get_column(matriz *mat, int *column)
{
    *column = mat->ncol;
}
int matriz_get_line(matriz *mat, int *line)
{
    *line = mat->nrow;
}