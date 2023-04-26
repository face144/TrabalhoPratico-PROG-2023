#ifndef TRABALHOPRATICO_LINKEDLIST_H
#define TRABALHOPRATICO_LINKEDLIST_H

#include "../Generic/String.h"

typedef struct TLinkedListNode
{
    void* Data;
    struct TLinkedListNode* Next;

} TLinkedListNode;

typedef struct TLinkedList
{
    TLinkedListNode* Head;
    TLinkedListNode* Tail;
    unsigned Length;

} TLinkedList;

typedef unsigned long long int size_t;

void TLinkedListCreate(TLinkedList* self);
int TLinkedListAddAtFront(TLinkedList* self, void* Data);
int TLinkedListAddAtBack(TLinkedList* self, void* Data);
int TLinkedListRemove(TLinkedList* self, const int Index);
void TLinkedListDestroy(TLinkedList* self);
void* TLinkedListGet(TLinkedList* self, int Index);
int TLinkedListSerialize(TLinkedList* list, char* FileName, size_t ElementSize);
int TLinkedListDeserialize(TLinkedList* self, char* FileName, size_t ElementSize);

#endif //TRABALHOPRATICO_LINKEDLIST_H
