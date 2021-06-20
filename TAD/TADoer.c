#include "TADoer.h"
#include <stdio.h>

matriz *read_file_txt(char nome[])
{
    FILE *file;              //Abre o arquivo, e o chama de file
    file = fopen(nome, "r"); //Aqui abre o arquivo passado como parâmetro.
    if (file == NULL)
    {
        printf("Error, file not found!");
        return 0;
    }
    //Aqui ta testando quantas linhas tem o arquivo.
    char c;
    int nLinha = 1, nColuna = 0;

    while (!feof(file))
    {
        c = fgetc(file);
        if (c == '\n')
        {
            nLinha++;
        }
    }
    rewind(file); //Para voltar o arquivo ao início.
    //Agora calcula quantas colunas tem
    int aux;

    while (!feof(file))
    {
        fscanf(file, "%d", &aux);
        nColuna++;
    }
    nColuna /= nLinha; //Pego quantos itens tem dentro do texto, e divido pelo numero de linhas, assim me resulta o número de colunas.

    matriz *mat = matriz_create(nLinha, nColuna);
    if (mat == NULL)
    {
        printf("Não foi possível fazer a alocação da matriz.");
        return 0;
    }
    rewind(file); //Para voltar o arquivo ao início.

    int aux2 = 0;
    while (!feof(file))
    {
        for (int i = 0; i < nLinha; i++)
        {
            for (int j = 0; j < nColuna; j++)
            {
                fscanf(file, "%d", &aux2);   //Pega os valores do txt
                matriz_set(mat, j, i, aux2); //E joga para dentro da matriz
            }
        }
    }

    fclose(file);
    return mat;
}

matriz *read_file_imm(char name[])
{
    FILE *file;               //Declara o file com o tipo de arquivo.
    file = fopen(name, "rb"); //Aqui abre o arquivo passado como parâmetro.
    if (file == NULL)         //Se o arquivo não for encontrado, vai retornar NULL
    {
        printf("\nError, file not found!\n"); //caso o arquivo não seja encontrado.
        return 0;
    }
    int nColuna, nLinha; //Iniciei essas váriaveis, e vou pegar do arquivo com um fread. Já é sabido quais são os tres primeiros valores do arquivo.
    fread(&nLinha, sizeof(float), 1, file);
    fread(&nColuna, sizeof(float), 1, file);
    matriz *mat = matriz_create(nLinha, nColuna); //Criando a matriz com os valores colhidos.

    if (mat == NULL) //Se não foi possível criar a matriz.
    {
        printf("\nIt was not possible to allocate the matriz.\n");
        return 0;
    }
    int aux = 0; //Variável auxiliar.
    for (int i = 0; i < nLinha; i++)
    {
        for (int j = 0; j < nColuna; j++)
        {
            fread(&aux, sizeof(int), 1, file); //Pega os valores do arquivo imm que é está alocado na forma de binário.

            matriz_set(mat, j, i, aux); //Essa linha pega o valor da variável aux, e joga pra dentro da matriz.
        }
    }
    fclose(file);

    return mat;
}

FILE *create_file_imm(char name[])
{

    FILE *file;

    file = fopen(name, "wb"); //Aqui abre o arquivo passado como parâmetro.
    if (file == NULL)         //Se o arquivo não for encontrado, vai retornar NULL
    {
        printf("\ncould not open the file!\n"); //caso o arquivo não seja encontrado.
        return NULL;
    }
    return file;
}

int write(FILE *file, char name[], int aux)
{

    file = fopen(name, "ab"); //Aqui abre o arquivo passado como parâmetro.
    if (file == NULL)         //Se o arquivo não for encontrado, vai retornar NULL
    {
        printf("\nfile not found!\n"); //caso o arquivo não seja encontrado.

        return 0;
    }
    fwrite(&aux, sizeof(int), 1, file); //pega o valor da coluna e coloca no arquivo
    //fechar o arquivo
    return 1;
}