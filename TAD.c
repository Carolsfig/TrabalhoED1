#include <stdio.h>
#include <stlib.h>
#include <TAD.h>


typedef struct Dados{
    char tipo[3];
    struct{
        int nLinhas;
        int nColunas;
    };
    int profundidade;
}PGM;



void abrirArquivo(PGM *imagem, FILE *file, int nLinhas, int nColunas) {
    int m[imagem.nLinhas][imagem.nColunas];
    int i;
    int z;

    for (i = 0; i < imagem.nLinhas ; i++ ) {
        for (z = 0; z < imagem.nColunas ; z++ ) {
            fscanf(file, "%d", &m[i][z]);
            printf("%3d ", m[i][z]);
        }
        putchar('\n');

    }

    fclose ( file );
}