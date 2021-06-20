#include "Tstack.h"
#include "TMat2D.h"
#include "TQueue.h"
#include<stdio.h>
#include<stdlib.h>
struct TStack
{
   int qtd, tamanho_maximo ;
   Ponto *data;
};

TStack *stack_create()
{
   TStack *st;
   st = malloc(sizeof(TStack));
   if (st != NULL)
   {
      st->qtd = 0;
      st->tamanho_maximo== MAX;
      st->data = malloc(MAX * sizeof(double));
      if (st->data == NULL)
      {
         free(st);
         return NULL;
      }
      return st;
   }
}
int stack_free(TStack *st)
{
   if (st == NULL)
      return INVALID_NULL_POINTER;
   free(st->data);
   free(st);
   st = NULL;
   return SUCCESS;
}
int stack_empty(TStack *st)
{
   if (st == NULL)
      return INVALID_NULL_POINTER;
   if (st->qtd == 0)
      return 1;
   else
      return 0;
}
Ponto stack_top(TStack *st)
{
   /*Não consigo fazer as verificações
   if (st == NULL)
      return NULL;
*/
   Ponto aux = st->data[st->qtd - 1];
   return aux;
}
//Essa função retora qual é o valor que foi deletado
Ponto stack_pop(TStack *st)
{
   /*Não consigo fazer as verificações
   if (st == NULL)
      return NULL;
   if (st->qtd == 0)
      return NULL;]
      */
   st->qtd--;
   return st->data[st->qtd];
}
int stack_push(TStack *st, Ponto aux)
{
   if (st == NULL)
      return INVALID_NULL_POINTER;
   if (st->qtd == st->tamanho_maximo)
      return OUT_OF_RANGE;
   st->data[st->qtd] = aux;
   st->qtd++;
   return SUCCESS;
}