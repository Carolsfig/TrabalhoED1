#include "TADmain.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TQueue.h"
#include "Tstack.h"
int convert(char name1[], char name2[])
{
    matriz *mat = read_file_txt(name1);
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

int segment(int thr, char name1[], char name2[])
{
    matriz *mat = read_file_imm(name1); //verificar o retorno

    if (mat == NULL) //Se não foi possível criar a matriz.
    {
        printf("\nIt was not possible to allocate the matriz.\n");
        return 0;
    }

    FILE *file;                //Arquivo binario
    file = fopen(name2, "wb"); //Aqui abre o arquivo passado como parâmetro.
    if (file == NULL)
    {
        printf("Error, file bin  not found or not created!");
        return 0;
    }

    int aux = 0; //esqueci o que esse atoi faz
    int nLinha, nColuna;
    matriz_get_dados(mat, &nColuna, &nLinha);
    fwrite(&nLinha, sizeof(int), 1, file);
    fwrite(&nColuna, sizeof(int), 1, file);
    for (int i = 0; i < nLinha; i++)
    {
        for (int j = 0; j < nColuna; j++)
        {
            matriz_get(mat, j, i, &aux);
            if (aux > thr)
            {
                aux = 1;
                fwrite(&aux, sizeof(int), 1, file);
            }
            else
            {
                aux = 0;
                fwrite(&aux, sizeof(int), 1, file);
            }
        }
    }

    matriz_free(mat); //Desaloca da memória a matriz
    fclose(file);
    return 1;
}
int cc(char name1[], char name2[])
{
    matriz *mat = read_file_imm(name1); //verificar o retorno

    if (mat == NULL) //Se não foi possível criar a matriz.
    {
        printf("\nIt was not possible to allocate the first matriz.\n");
        return INVALID_NULL_POINTER;
    }

    int nLinha, nColuna;
    matriz_get_dados(mat, &nColuna, &nLinha);
    matriz *mat_rot = matriz_create(nLinha, nColuna); //verificar o retorno
    if (mat_rot == NULL)                              //Se não foi possível criar a matriz.
    {
        printf("\nIt was not possible to allocate the second matriz.\n");
        free(mat);
        return INVALID_NULL_POINTER;
    }
    int aux = 0;                     //Variável auxiliar.
    for (int i = 0; i < nLinha; i++) //zerando a segunda matriz
    {
        for (int j = 0; j < nColuna; j++)
        {
            matriz_set(mat_rot, j, i, aux); //Essa linha pega o valor da variável aux, e joga pra dentro da matriz.
        }
    }
    aux = 0;
    int aux2 = 0;
    int label = 1;

    DQNode *lista_proximos = queue_create();
    struct Ponto p, p_atual;

    for (int i = 1; i < nLinha - 1; i++)
    {
        for (int j = 1; j < nColuna - 1; j++)
        {
            // percorre toda a imagem em busca de um pixel foreground (valor 1)
            p.x = i;
            p.y = j;

            matriz_get(mat, j, i, &aux);
            matriz_get(mat_rot, j, i, &aux2);

            if (aux == 1 && aux2 == 0)
            {

                // atribui o label a posição (i,j)
                matriz_set(mat_rot, p.y, p.x, label);
                // inclui na lista de busca dos vizinhos

                queue_push(lista_proximos, p);
                while (!queue_empty(lista_proximos))
                {
                    // busca o próximo ponto da lista
                    queue_pop(lista_proximos, &p_atual); //tem que fazer o pop e retornar o que foi popado

                    // buscando por pixels na vizinhança do ponto atual que são iguais a 1
                    // ponto acima
                    p.x = p_atual.x - 1;
                    p.y = p_atual.y;
                    // verifica if o ponto acima não é um e não foi rotulado

                    matriz_get(mat, p.y, p.x, &aux);
                    matriz_get(mat_rot, p.y, p.x, &aux2);

                    if (aux == 1 && aux2 == 0)
                    {
                        // atribui o label a posição atual
                        matriz_set(mat_rot, p.y, p.x, label);
                        // adiciona o ponto na lista para verificar vizinhos posteriormente
                        queue_push(lista_proximos, p);
                    }
                    // ponto abaixo
                    p.x = p_atual.x + 1;
                    p.y = p_atual.y;
                    // verifica if o ponto acima não é um e não foi rotulado
                    matriz_get(mat, p.y, p.x, &aux);
                    matriz_get(mat_rot, p.y, p.x, &aux2);

                    if (aux == 1 && aux2 == 0)
                    {
                        // atribui o label a posição atual
                        matriz_set(mat_rot, p.y, p.x, label);
                        // adiciona o ponto na lista para verificar vizinhos posteriormente
                        queue_push(lista_proximos, p);
                    }
                    // ponto à esquerda
                    p.x = p_atual.x;
                    p.y = p_atual.y - 1;
                    // verifica if o ponto acima não é um e não foi rotulado
                    matriz_get(mat, p.y, p.x, &aux);
                    matriz_get(mat_rot, p.y, p.x, &aux2);

                    if (aux == 1 && aux2 == 0)
                    {
                        // atribui o label a posição atual
                        matriz_set(mat_rot, p.y, p.x, label);
                        // adiciona o ponto na lista para verificar vizinhos posteriormente
                        queue_push(lista_proximos, p);
                    }
                    // ponto à direita
                    p.x = p_atual.x;
                    p.y = p_atual.y + 1;
                    // verifica if o ponto acima não é um e não foi rotulado
                    matriz_get(mat, p.y, p.x, &aux);
                    matriz_get(mat_rot, p.y, p.x, &aux2);

                    if (aux == 1 && aux2 == 0)
                    {
                        // atribui o label a posição atual
                        matriz_set(mat_rot, p.y, p.x, label);
                        // adiciona o ponto na lista para verificar vizinhos posteriormente
                        queue_push(lista_proximos, p);
                    }
                } // enquanto*/
                label++;
            } // if
        }
    }
    FILE *file;                //Arquivo binario
    file = fopen(name2, "wb"); //Aqui abre o arquivo passado como parâmetro.
    if (file == NULL)
    {
        printf("Error, file bin  not found or not created!");
        return 0;
    }
    aux = 0;
    fwrite(&nLinha, sizeof(int), 1, file);
    fwrite(&nColuna, sizeof(int), 1, file);
    for (int i = 0; i < nLinha; i++)
    {
        for (int j = 0; j < nColuna; j++)
        {
            matriz_get(mat_rot, j, i, &aux);
            fwrite(&aux, sizeof(int), 1, file);
        }
    }

    free(mat);
    free(mat_rot);
    fclose(file);
    return SUCCESS;
}

int lab(char name1[], char name2[])
{

    matriz *mat = read_file_txt(name1); //verificar o retorno

    if (mat == NULL) //Se não foi possível criar a matriz.
    {
        printf("\nIt was not possible to allocate the matriz.\n");
        return 0;
    }
    int nLinha, nColuna, check = 0;
    matriz_get_dados(mat, &nColuna, &nLinha);

    
    int aux = 0;                     //Variável auxiliar.
    
    int aux2 = 0;
    Ponto p_inicio, p_fim, p;
    for (int i = 0; i < nLinha; i++) //isso tudo só para achar o fim e início
    {
        for (int j = 0; j < nColuna; j++)
        {
            matriz_get(mat, j, i, &aux);
            //é para fazer com que o ponto inicial não seja uma borda

            if (aux == 1 && j == 0)
            {
                if (check == 0) //pra saber se já peguei o início
                {
                    matriz_set(mat, j, i, 2);
                    p_inicio.x = i;
                    p_inicio.y = j + 1;
                    check = 1;
                }
                p_fim.x = i;
                p_fim.y = j;
            }
            if (aux == 1 && i == 0)
            {
                if (check == 0)
                {
                    matriz_set(mat, j, i, 2);
                    p_inicio.x = i + 1;
                    p_inicio.y = j;
                    check = 1;
                }
                p_fim.x = i;
                p_fim.y = j;
            }
            if (aux == 1 && i == nLinha - 1)
            {
                if (check == 0)
                {
                    matriz_set(mat, j, i, 2);
                    p_inicio.x = i - 1;
                    p_inicio.y = j;
                    check = 1;
                }
                p_fim.x = i;
                p_fim.y = j;
            }
            if (aux == 1 && j == nColuna - 1)
            {
                if (check == 0)
                {
                    matriz_set(mat, j, i, 2);
                    p_inicio.x = i;
                    p_inicio.y = j - 1;
                    check = 1;
                }
                p_fim.x = i;
                p_fim.y = j;
            }
        }
    }
    matriz_set(mat, p_inicio.y, p_inicio.x, 2);
    //TEM QUE POR NO OUTRO ARQUIVO PARA O PROGRAMA NÃO VOLTAR PARA TRÁS,.

    int pc, pb, pd, pe, pcr, pbr, pdr, per; //p cima, p baixo, p esquerda, p direita
    p = p_inicio;
    //matriz_set(mat_rot, p.y, p.x, 1);
    //matriz_set(mat_rot, p_fim.y, p_fim.x, 1);

    //printf("(%d,%d,%d,%d)(%d,%d,%d,%d)",pc, pb, pd, pe, pcr, pbr, pdr, per);
    //matriz_print(mat);

    TStack *stack = stack_create();
    stack_push(stack, p);                    //COLOCA O PRIMEIRO PONTO NA MATRIZ
    while (p.x != p_fim.x && p.y != p_fim.y) //VAI ATÉ ACHAR O PONTO FINAL
    {
        matriz_get(mat, p.y, p.x - 1, &pc); //Pega o vizinho de cima da matriz principal
        matriz_get(mat, p.y, p.x + 1, &pb); //Pega o vizinho de baixo da matriz principal
        matriz_get(mat, p.y - 1, p.x, &pe); //Pega o vizinho de esquerda da matriz principal
        matriz_get(mat, p.y + 1, p.x, &pd); //Pega o vizinho de direita da matriz principal

        if (pc == 1)
        {
            p.x -= 1;
            matriz_set(mat, p.y, p.x, 2);
            stack_push(stack, p);
        }
        else if (pd == 1)
        {
            p.y += 1;
            matriz_set(mat, p.y, p.x, 2);
            stack_push(stack, p);
        }
        else if (pe == 1)
        {
            p.y -= 1;
            matriz_set(mat, p.y, p.x, 2);
            stack_push(stack, p);
        }
        else if (pb == 1)
        {
            p.x += 1;
            matriz_set(mat, p.y, p.x, 2);
            stack_push(stack, p);
        }
        else
        {
            matriz_set(mat, p.y, p.x, 3);
            p = stack_pop(stack);
        }
    }
    
    matriz_set(mat, p_fim.y, p_fim.x, 2);

    FILE* file=fopen(name2,"w");
    if (file == NULL)
        {
            printf("Erro");
            exit(1);
        }
    for (int i = 0; i < nLinha; i++)
    {
        for (int j = 0; j < nColuna; j++)
        {   
            matriz_get(mat,j,i,&aux);
            fprintf(file,"%d ",aux);
        }
        fprintf(file,"\n",aux);
    }
    
    fclose(file);
    matriz_print(mat);
    free(mat);
    return SUCCESS;
}