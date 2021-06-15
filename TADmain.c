#include "TADmain.h"
#include <stdio.h>

int convert(char name1[], char name2[])
{
    matriz *mat = read_file_txt(name1);
    printf("%s,%s", name1, name2);
    FILE *file;                //Arquivo binario
    file = fopen(name2, "wb"); //Aqui abre o arquivo passado como parâmetro.
    if (file == NULL)
    {
        printf("Error, file bin  not found or not created!");
        return 0;
    }
    int nLinha, nColuna;
    matriz_get_dados(mat, &nColuna, &nLinha);
    fwrite(&nLinha, sizeof(int), 1, file);
    fwrite(&nColuna, sizeof(int), 1, file);

    int aux = 0;
    for (int i = 0; i < nLinha; i++)
    {
        for (int j = 0; j < nColuna; j++)
        {
            matriz_get(mat, j, i, &aux);        //pega o valor da matriz
            fwrite(&aux, sizeof(int), 1, file); //E joga para dentro do arquivo no tipo binario.
        }
    }

    fclose(file);     //Fecha o arquivo.
    matriz_free(mat); //Desaloca da memória a matriz
    return 1;
}