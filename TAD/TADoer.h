#ifndef _TADoer_
#define _TADoer_
#include "TMat2D.h"
#include <stdio.h>
#include <stdlib.h>

matriz *read_file_txt(char name[]);
matriz *read_file_imm(char name[]);
FILE *create_file_imm(char name[]);
int write(FILE *file, char name[], int aux);

#endif