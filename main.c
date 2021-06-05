int main(int argc, char *argv[])
{
if (argc < 2){
fprintf(stderr, "ERRO: faltou parametro\n");
return(1);
}
    if (strcmp(argv[1], "-open") == 0)
    {
        char *check;
        check = strstr(argv[2], ".");
        if (strcmp(check, ".txt") == 0)
        {
            printf("Abre uma imagem (formato texto) e mostra os valores dos pixels na tela.");
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