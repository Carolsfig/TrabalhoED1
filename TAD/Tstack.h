#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include"TQueue.h"
#define MAX 100
typedef struct TStack TStack;

TStack *stack_create();
int stack_free(TStack *st);                //Usado e testado
int stack_push(TStack *st, Ponto pont);        //Usado e testado
Ponto stack_pop(TStack *st);                //Usado e testado
Ponto stack_top(TStack *st);                //Usado e testado
int stack_empty(TStack *st);               //Usado e testado
int stack_full(TStack *st);                //Usado e testado
int stack_print(TStack *st);
