#ifndef TRABALHOPRATICO_ROUTELIST_H
#define TRABALHOPRATICO_ROUTELIST_H

#include "FRoute.h"

typedef struct TLinkedListNode
{
    FRoute* Data;
    struct TLinkedListNode* Next;

} TLinkedListNode;

typedef struct TLinkedList
{
    TLinkedListNode* Head;
    TLinkedListNode* Tail;
    unsigned Length;

} TLinkedList;

void TLinkedListCreate(TLinkedList* self);
int TLinkedListAddAtFront(TLinkedList* self, FRoute* Data);
int TLinkedListAddAtBack(TLinkedList* self, FRoute* Data);
int TLinkedListRemove(TLinkedList* self, int Index);
void TLinkedListDestroy(TLinkedList* self);
FRoute* TLinkedListGet(TLinkedList* self, int Index);
int TLinkedListSerialize(TLinkedList* list, char* FileName);
int TLinkedListDeserialize(TLinkedList* self, char* FileName);

#endif //TRABALHOPRATICO_ROUTELIST_H
