#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TMat2D.h"  //TAD da matriz
#include "TQueue.h"  //TAD da fila
#include "TADoer.h"  //TAD da leitura e escrita
#include "TADmain.h" //TAD das funções principais

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
            
            matriz *mat = read_file_txt(argv[2]);
            matriz_print(mat); //Essa função vai imprimir na tela a matriz.       //Fecha o arquivo.
            matriz_free(mat);  //Desaloca da memória a matriz
        }

        else if (strcmp(check, ".imm") == 0)
        {
            matriz *mat = read_file_imm(argv[2]);
            matriz_print(mat); //Imprimindo a matriz.
            matriz_free(mat);
        }
        else //Caso a opção "-open" seja escolhida, mas não tenha achado a extensão.
        {
            printf("\nfile extension not found or not suported!\n");
            exit(1);
        }
    }
    else if (strcmp(argv[1], "-convert") == 0)
    {
        /*
        if (argc < 4)
        {
            printf("SEM argumentos suficientes");
            exit(1);
        }
        int res;//Só para verificar o resultado.
        res=convert(argv[2],argv[3]);
        if(res==1){
            printf("Conversão feita com sucesso!");
        }
        */
    }
    else if (strcmp(argv[1], "-segment") == 0)
    {

        FILE *file;                  //Abre o arquivo, e o chama de file
        file = fopen(argv[3], "rb"); //Aqui abre o arquivo passado como parâmetro.
        if (file == NULL)            //Se o arquivo não for encontrado, vai retornar NULL
        {
            printf("\nError, file not found1!\n"); //caso o arquivo não seja encontrado.
            return 0;
        }

        int nColuna, nLinha; //Iniciei essas váriaveis, e vou pegar do arquivo com um fread. Já é sabido quais são os tres primeiros valores do arquivo.
        fread(&nColuna, sizeof(float), 1, file);
        fread(&nLinha, sizeof(float), 1, file);
        matriz *matriz = matriz_create(nLinha, nColuna); //Criando a matriz com os valores colhidos.

        if (matriz == NULL) //Se não foi possível criar a matriz.
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
                matriz_set(matriz, j, i, aux);     //Essa linha pega o valor da variável aux, e joga pra dentro da matriz.
            }
        }

        fclose(file);
        FILE *file2;

        file2 = fopen(argv[4], "wb"); //Aqui abre o arquivo passado como parâmetro.
        if (file2 == NULL)            //Se o arquivo não for encontrado, vai retornar NULL
        {
            printf("\nError, file not found2!\n"); //caso o arquivo não seja encontrado.
            return 0;
        }
        int thr = atoi(argv[2]);
        fwrite(&nColuna, sizeof(int), 1, file2); //pega o valor da coluna e coloca no arquivo
        fwrite(&nLinha, sizeof(int), 1, file2);  //pega o valor da linha e coloca no arquivo
        for (int i = 0; i < nLinha; i++)
        {
            for (int j = 0; j < nColuna; j++)
            {
                matriz_get(matriz, j, i, &aux);
                if (aux > thr)
                {
                    aux = 1;
                    fwrite(&aux, sizeof(int), 1, file2);
                }
                else
                {
                    aux = 0;
                    fwrite(&aux, sizeof(int), 1, file2);
                }
            }
        }
        printf("fim");

        return 0;
    }
    else if (strcmp(argv[1], "-cc") == 0)
    {
        printf("Detecta os componentes conexos de uma imagem\n");
        if (argc < 4)
        {
            printf("SEM argumentos suficientes");
            exit(1);
            ////////////////COLOCAR UM RETURN AQUI
        }

        FILE *file;                  //Abre o arquivo, e o chama de file
        file = fopen(argv[2], "rb"); //Aqui abre o arquivo passado como parâmetro.
        if (file == NULL)            //Se o arquivo não for encontrado, vai retornar NULL
        {
            printf("\nError, file not found1!\n"); //caso o arquivo não seja encontrado.
            return 0;
        }

        int nColuna, nLinha; //Iniciei essas váriaveis, e vou pegar do arquivo com um fread. Já é sabido quais são os tres primeiros valores do arquivo.
        fread(&nColuna, sizeof(float), 1, file);
        fread(&nLinha, sizeof(float), 1, file);
        matriz *mat = matriz_create(nLinha, nColuna); //Criando a matriz com os valores colhidos.
        matriz *mat_rot = matriz_create(nLinha, nColuna);
        if (mat == NULL) //Se não foi possível criar a matriz.
        {
            printf("\nIt was not possible to allocate the matriz.\n");
            return 0;
        }
        int aux = 0;                     //Variável auxiliar.
        for (int i = 0; i < nLinha; i++) //zerando a segunda matriz
        {
            for (int j = 0; j < nColuna; j++)
            {
                matriz_set(mat_rot, i, j, aux); //Essa linha pega o valor da variável aux, e joga pra dentro da matriz.
            }
        }

        for (int i = 0; i < nLinha; i++)
        {
            for (int j = 0; j < nColuna; j++)
            {
                fread(&aux, sizeof(int), 1, file); //Pega os valores do arquivo imm que é está alocado na forma de binário.
                matriz_set(mat, i, j, aux);        //Essa linha pega o valor da variável aux, e joga pra dentro da matriz.
            }
        }
        matriz_print(mat_rot);
        printf("\n");
        matriz_print(mat);
        fclose(file);
        // considerando que a borda da imagem são zeros
        // im - imagem original
        // im_rot - imagem rotulada - inicialmente zerada
        aux = 0;
        int aux2 = 0;
        int label = 1;
        DQNode *lista_proximos = queue_create();
        struct Ponto p, p_atual;
        /*
        for (int i = 1; i < nLinha - 1; i++)
        {
            for (int j = 1; j < nColuna - 1; j++)
            {

                // percorre toda a imagem em busca de um pixel foreground (valor 1)
                p.x = i;
                p.y = j;
                matriz_get(mat, i, j, &aux);
                matriz_get(mat_rot, i, j, &aux2);
                if (aux == 1 && aux2 == 0)
                {
                    // atribui o label a posição (i,j)

                    
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
                        matriz_get(mat, p.x,p.y, &aux);
                        matriz_get(mat_rot, p.x,p.y, &aux2);
                        if (aux == 1 && aux2 == 0){
                            // atribui o label a posição atual
                            matriz_set(mat_rot, i, j, label);
                            // adiciona o ponto na lista para verificar vizinhos posteriormente
                            queue_push(lista_proximos, p);
                        }
                        // ponto abaixo
                        p.x = p_atual.x + 1;
                        p.y = p_atual.y;
                        matriz_get(mat, p.x,p.y, &aux);
                        matriz_get(mat_rot, p.x,p.y, &aux2);
                        if (aux == 1 && aux2 == 0){
                            // atribui o label a posição atual
                            matriz_set(mat_rot, i, j, label);
                            // adiciona o ponto na lista para verificar vizinhos posteriormente
                            queue_push(lista_proximos, p);
                        }
                        // ponto à esquerda
                        p.x = p_atual.x;
                        p.y = p_atual.y - 1;
                        matriz_get(mat, p.x,p.y, &aux);
                        matriz_get(mat_rot, p.x,p.y, &aux2);
                        if (aux == 1 && aux2 == 0){
                            // atribui o label a posição atual
                            matriz_set(mat_rot, i, j, label);
                            // adiciona o ponto na lista para verificar vizinhos posteriormente
                            queue_push(lista_proximos, p);
                        }
                        // ponto à direita
                        p.x = p_atual.x;
                        p.y = p_atual.y + 1;
                        matriz_get(mat, p.x,p.y, &aux);
                        matriz_get(mat_rot, p.x,p.y, &aux2);
                        if (aux == 1 && aux2 == 0){
                            // atribui o label a posição atual
                            matriz_set(mat_rot, i, j, label);
                            // adiciona o ponto na lista para verificar vizinhos posteriormente
                            queue_push(lista_proximos, p);
                        }
                    } // enquanto
                    label = label + 1;
                } // if
            }
        }
        


    matriz_print(mat);
    printf("\n");
    matriz_print(mat_rot);



*/
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