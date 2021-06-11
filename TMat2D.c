#include <stdio.h>
#include <stdlib.h>
#include "TMat2D.h"

struct matriz
{

    int nrow;
    int ncol;
    double *data;
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
        auxiliar->data = malloc(ncol * nrow * sizeof(double));
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

int matriz_set(matriz *auxliar, int i, int j, double val)
{
    int aux;
    aux = j * auxliar->ncol + i;
    auxliar->data[aux] = val;
    return 0;
}
int matriz_get(matriz *auxiliar, int i, int j, double *val)
{
    int pos;
    pos = j * auxiliar->ncol + i;
    *val = auxiliar->data[pos];
    return 0;
}

int matriz_sum(matriz *mat1, matriz *mat2, matriz *sum, int i, int j)
{
    if (mat1->ncol != mat2->ncol || mat2->nrow != mat1->nrow)
    {
        return -1;
    }
    for (int cont = 0; cont < i * j; cont++)
    {
        sum->data[cont] = mat1->data[cont] + mat2->data[cont];
    }

    return 0;
}
int matriz_multiplication(matriz *mat1, matriz *mat2, matriz *multiplication, int i, int j)
{
    if (mat1->ncol != mat2->ncol || mat2->nrow != mat1->nrow)
    {
        return -1;
    }
    for (int cont = 0; cont < i * j; cont++)
    {
        multiplication->data[cont] = mat1->data[cont] * mat2->data[cont];
    }
    return 0;
}

int matriz_escalar(matriz *mat, matriz *escalar, float val)
{
    for (int i = 0; i < mat->nrow * mat->ncol; i++)
    {
        escalar->data[i] = mat->data[i] * val;
    }
    return 0;
}

int matriz_rastro(matriz *mat, double *sum)
{
    for (int i = 0; i < mat->nrow; i++)
    {
        *sum += mat->data[i * mat->ncol + i];
    }
    return 0;
}

int matriz_sum_linha(matriz *mat, double *sum)
{
    if (mat == NULL)
        return -1;
    for (int i = 0; i < mat->nrow; i++)
    {
        sum[i] = 0;
        for (int j = 0; j < mat->ncol; j++)
            sum[i] = sum[i] + mat->data[j * mat->nrow + i];
    }
    return 0;
}

int matriz_sum_coluna(matriz *mat, double *sum)
{
    if (mat == NULL)
        return -1;
    for (int i = 0; i < mat->ncol; i++)
    {
        sum[i] = 0;
        for (int j = 0; j < mat->nrow; j++)
            sum[i] = sum[i] + mat->data[i * mat->nrow + j];
    }
    return 0;
}

void matriz_print(matriz *mat)
{
double aux;
    printf("\nImprimindo a  matriz\n");

    for (int i = 0; i < mat->ncol; i++)
    {
        for (int j = 0; j < mat->nrow; j++)
        {
            matriz_get(mat, i, j, &aux);
            printf("%0.lf\t ", aux);
        }
        printf("\n");
    }
}