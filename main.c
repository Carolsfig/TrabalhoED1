#include <stdio.h>
#include <stlib.h>
#include <TAD.h>

int main() {
    PGM imagem;
    FILE *file;
    file = fopen ("GIMP.pgm", "rt");

    //Tipo imagem
    fscanf(file, "%s", imagem.tipo);
    printf("%s\n", imagem.tipo);

    //Dimensão imagem
    fscanf(file, "%d %d", &imagem.nColunas, &imagem.nLinhas);
    printf("%d %d\n", imagem.nColunas, imagem.nLinhas);

    //Profundidade de cor
    fscanf(file, "%d", &imagem.profundidade);
    printf("%d\n", imagem.profundidade);
    
    abrirArquivo();

    return 0;
}
