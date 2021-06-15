#ifndef _TQueue_
#define _TQueue_
struct Ponto {
    int x;
    int y;
};
#define SUCCESS 0
#define INVALID_NULL_POINTER -1
#define OUT_OF_MEMORY -2
#define OUT_OF_RANGE -3
#define ELEM_NOT_FOUND -4
typedef struct DQNode DQNode;
typedef struct Ponto Ponto;
DQNode* queue_create();
int queue_free(DQNode* queue);                        // Usado e testado
int queue_push(DQNode* queue,Ponto ponto);  // Usado e testado
int queue_size(DQNode* queue);                        // Usado e testado
int queue_pop(DQNode* queue,Ponto *ponto);                   // Usado e testado
int queue_empty(DQNode* queue);                       // Usado e testado
//int queue_print(DQNode* queue);                       // Usado e testado
#endif