#include "TQueue.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct list_node list_node;

struct list_node
{
  struct Ponto Ponto;
  list_node *next;
};

struct DQNode
{
  int qtd;
  list_node *begin;
  list_node *end;
};
DQNode *queue_create()
{
  DQNode *queue;
  queue = malloc(sizeof(DQNode));
  if (queue != NULL)
  {
    queue->begin = NULL;
    queue->end = NULL;
    queue->qtd = 0;
  }
  return queue;
}
//Return 1 caso vazio
int queue_empty(DQNode *queue)
{
  if (queue->begin == NULL)
    return 1;
  else
    return 0;
}

int queue_free(DQNode *queue)
{
  if (queue == NULL)
    return INVALID_NULL_POINTER;

  list_node *aux;
  aux = queue->begin;
  while (aux != NULL)
  {
    queue->begin = aux->next;
    free(aux);
    aux = queue->begin;
  }
  free(queue);
  return SUCCESS;
}

int queue_push(DQNode *queue, Ponto ponto)
{
  if (queue == NULL)
    return INVALID_NULL_POINTER;

  list_node *node;
  node = malloc(sizeof(list_node));
  if (node == NULL)
    return OUT_OF_MEMORY;
  node->Ponto = ponto;
  node->next = NULL;

  if (queue->begin == NULL)
  { // a lista está vazia
    queue->begin = node;
    queue->end = node;
  }
  else
  { // a lista tem pelo menos um nó
    list_node *aux;

    aux = queue->end;
    queue->end = node;
    aux->next = queue->end;
    queue->qtd++;
    return SUCCESS;
  }
}

int queue_pop(DQNode *queue, Ponto *ponto)
{
  if (queue == NULL)
    return INVALID_NULL_POINTER;
  if (ponto == NULL)
    return INVALID_NULL_POINTER;
  if (queue->begin == NULL)
    return OUT_OF_RANGE;
  list_node *aux;
  aux = queue->begin;
  *ponto = aux->Ponto;
  aux = aux->next;
  free(queue->begin);
  queue->begin = aux;
  queue->qtd--;
  return SUCCESS;
}

int queue_size(DQNode *queue)
{
  if (queue == NULL)
    return INVALID_NULL_POINTER;
  return queue->qtd;
}
/*
int queue_print(DQNode *queue)
{
  if (queue == NULL)
    return INVALID_NULL_POINTER;

  list_node *aux;
  aux = queue->begin;
  printf("\nImprimindo a lista \n");

  while (aux != NULL)
  {
    printf("\n------------------\n");
    printf("Matricula: %d\n", aux->data.matricula);
    printf("Nome: %s\n", aux->data.nome);
    printf("Notas: %.1f; %.1f; %.1f;\n", aux->data.n1, aux->data.n2,
           aux->data.n3);

    aux = aux->next;
  }
  printf("\nFim da lista \n");
}*/