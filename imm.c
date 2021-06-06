//Objetivos a serem feitos:
//Passar as mensagens de erro para ingles.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TMat2D.h" //TAD da matriz

int main(int argc, char *argv[])
{
    //Aqui faz a verificação se os argumentos de entrada na linha de comando são menores que 2;
    if (argc < 2)
    {
        printf("Error, missing parameter!\n");
        return 0;
    }
    //Caso o primeiro argumento seja igual a -open
    if (strcmp(argv[1], "-open") == 0)
    {
        char *check;                    //Variável utilizada para saber a extensão do arquivo.
        check = strstr(argv[2], ".");   //Joga para dentro do check, todo o texto depois do ".", incluindo o mesmo, por exemplo ".txt"
        if (strcmp(check, ".txt") == 0) //Verifica se o check é igual a .txt
        {
            FILE *file;//Abre o arquivo, e o chama de file
            file = fopen(argv[2], "r"); //Aqui abre o arquivo passado como parâmetro.
            if (file == NULL)
            {
                printf("Error, file not found!");
                return 0;
            }
            //Aqui ta testando quantas linhas tem o arquivo.
            char c;
            int nLinha = 1, nColuna = 0;
            ;
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
            char aux[50];
            while (!feof(file))
            {
                fscanf(file, "%s", &aux);
                nColuna++;
            }
            nColuna /= nLinha; //Pego quantos itens tem dentro do texto, e divido pelo numero de linhas, assim me resulta o número de colunas.
            matriz *matriz = matriz_create(nLinha, nColuna);
            if (matriz == NULL)
            {
                printf("Não foi possível fazer a alocação da matriz.");
                return 0;
            }
            rewind(file); //Para voltar o arquivo ao início.

            double aux2=0;
            while (!feof(file))
            {
                for (int i = 0; i < nColuna; i++)
                {
                    for (int j = 0; j < nLinha; j++)
                    {
                        fscanf(file,"%lf", &aux2);
                        matriz_set(matriz, i, j,aux2);
                    }
                }
            }
            matriz_print(matriz);//Essa função vai imprimir na tela a matriz.
            fclose(file);//Fecha o arquivo.
            matriz_free(matriz);//Desaloca da memória a matriz
        }

        else if (strcmp(check, ".imm") == 0)
        {
            printf("Abra uma imagem (formato binária) e mostra os valores dos pixels na tela.");
        }
        else
        {
            printf("file extension not found or not suported!");
            exit(1);
        }
    }
    else if (strcmp(argv[1], "-convert") == 0)
    {
        printf("Converte uma imagem no formato file.txt para o formato file.imm.");
    }
    else if (strcmp(argv[1], "-segment") == 0)
    {
        printf("Faz o thresholding (limiarização da imagem) com um valor thr da imagem file.imm e escreve o resultado em segfile.imm");
    }
    else if (strcmp(argv[1], "-cc") == 0)
    {
        printf("Detecta os componentes conexos de uma imagem");
    }
    else if (strcmp(argv[1], "-lab") == 0)
    {
        printf("Mostra o caminho a ser percorrido em um labirinto");
    }
    else
    {
        printf("Opção não Existente.");
        exit(1);
    }

    return 0;
}