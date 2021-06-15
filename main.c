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
            FILE *file;                 //Abre o arquivo, e o chama de file
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
            int aux;

            int profundidade = 0;
            while (!feof(file))
            {
                fscanf(file, "%d", &aux);
                nColuna++;
                if (aux > profundidade) //Profundidade vai assumir o maior valor que tem no arquivo.
                {
                    profundidade = aux;
                }
            }
            nColuna /= nLinha; //Pego quantos itens tem dentro do texto, e divido pelo numero de linhas, assim me resulta o número de colunas.

            matriz *matriz = matriz_create(nLinha, nColuna, profundidade);
            if (matriz == NULL)
            {
                printf("Não foi possível fazer a alocação da matriz.");
                return 0;
            }
            rewind(file); //Para voltar o arquivo ao início.

            int aux2 = 0;
            while (!feof(file))
            {
                for (int i = 0; i < nColuna; i++)
                {
                    for (int j = 0; j < nLinha; j++)
                    {
                        fscanf(file, "%d", &aux2);      //Pega os valores do txt
                        matriz_set(matriz, i, j, aux2); //E joga para dentro da matriz
                    }
                }
            }
            matriz_print(matriz); //Essa função vai imprimir na tela a matriz.
            fclose(file);         //Fecha o arquivo.
            matriz_free(matriz);  //Desaloca da memória a matriz
        }

        else if (strcmp(check, ".imm") == 0)
        {
            FILE *file;                  //Abre o arquivo, e o chama de file
            file = fopen(argv[2], "rb"); //Aqui abre o arquivo passado como parâmetro.
            if (file == NULL)            //Se o arquivo não for encontrado, vai retornar NULL
            {
                printf("\nError, file not found!\n"); //caso o arquivo não seja encontrado.
                return 0;
            }

            int nColuna, nLinha, profundidade; //Iniciei essas váriaveis, e vou pegar do arquivo com um fread. Já é sabido quais são os tres primeiros valores do arquivo.
            fread(&nColuna, sizeof(float), 1, file);
            fread(&nLinha, sizeof(float), 1, file);
            fread(&profundidade, sizeof(float), 1, file);
            matriz *matriz = matriz_create(nLinha, nColuna, profundidade); //Criando a matriz com os valores colhidos.

            if (matriz == NULL) //Se não foi possível criar a matriz.
            {
                printf("\nIt was not possible to allocate the matriz.\n");
                return 0;
            }
            int aux = 0; //Variável auxiliar.
            for (int i = 0; i < nColuna; i++)
            {
                for (int j = 0; j < nLinha; j++)
                {
                    fread(&aux, sizeof(int), 1, file); //Pega os valores do arquivo imm que é está alocado na forma de binário.
                    matriz_set(matriz, i, j, aux);     //Essa linha pega o valor da variável aux, e joga pra dentro da matriz.
                }
            }
            matriz_print(matriz); //Imprimindo a matriz.
        }
        else //Caso a opção "-open" seja escolhida, mas não tenha achado a extensão.
        {
            printf("\nfile extension not found or not suported!\n");
            exit(1);
        }
    }
    else if (strcmp(argv[1], "-convert") == 0)
    {
        printf("Converte uma imagem no formato file.txt para o formato file.imm.\n");

        FILE *file;                 //Abre o arquivo, e o chama de file
        file = fopen(argv[2], "r"); //Aqui abre o arquivo passado como parâmetro.
        if (file == NULL)
        {
            printf("Error, file txt  not found!"); //Se não achar o arquivo.
            return 0;
        }
        //Aqui ta testando quantas linhas tem o arquivo.
        char c;                      //Vai ser usado para verificar quantas linhas tem.
        int nLinha = 1, nColuna = 0; //criando as variáveis de linha e coluna, o nLinha começa com +1 porque o código não vai considerar o final do arquivo, pois não tem \n, mas sim o eof.
        while (!feof(file))
        {
            c = fgetc(file);
            if (c == '\n')//Se o c for igual a \n, significa que achou final de linha, logo linha++.
            {
                nLinha++;
            }
        }
        rewind(file); //Para voltar o arquivo ao início para fazer outra verificação.
        //Agora calcula quantas colunas tem
        int profundidade = 0,aux;
        while (!feof(file))
        {
            fscanf(file, "%d", &aux);//Sempre que achar um dado, vai salvar.
            nColuna++;
            if (aux > profundidade) //Profundidade vai assumir o maior valor que tem no arquivo.
            {
                profundidade = aux;
            }
        }
        nColuna /= nLinha; //Pego quantos itens tem dentro do texto, e divido pelo numero de linhas, assim me resulta o número de colunas.

        matriz *matriz = matriz_create(nLinha, nColuna, profundidade);//Criação de matriz
        if (matriz == NULL)
        {
            printf("Não foi possível fazer a alocação da matriz.");//Caso haja algum erro com a matriz.
            return 0;
        }
        rewind(file); //Para voltar o arquivo ao início para agora pegar os dados do arquivo e jogar para a matriz.

        aux = 0;
        while (!feof(file))
        {
            for (int i = 0; i < nColuna; i++)
            {
                for (int j = 0; j < nLinha; j++)
                {
                    fscanf(file, "%d", &aux);      //Pega os valores do txt
                    matriz_set(matriz, i, j, aux); //E joga para dentro da matriz
                }
            }
        }
        fclose(file);                 //Fecha o arquivo TXT.
        FILE *file2;                  //Arquivo binario
        file2 = fopen(argv[3], "wb"); //Aqui abre o arquivo passado como parâmetro.
        if (file2 == NULL)
        {
            printf("Error, file bin  not found or not created!");
            return 0;
        }

        matriz_get_dados(matriz, &nColuna, &nLinha, &profundidade);


        fwrite(&nColuna, sizeof(int), 1, file2);//pega o valor da coluna e coloca no arquivo
        fwrite(&nLinha, sizeof(int), 1, file2);//pega o valor da linha e coloca no arquivo
        fwrite(&profundidade, sizeof(int), 1, file2);//pega o valor da profundidade e coloca no arquivo
        aux = 0;
        for (int i = 0; i < nColuna; i++)
        {
            for (int j = 0; j < nLinha; j++)
            {
                matriz_get(matriz, i, j, &aux);//pega o valor da matriz
                fwrite(&aux, sizeof(int), 1, file2);//E joga para dentro do arquivo no tipo binario.
            }
        }

        fclose(file2);//Fecha o arquivo.
        matriz_free(matriz); //Desaloca da memória a matriz
    }
    else if (strcmp(argv[1], "-segment") == 0)
    {
       
    return 0;
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