#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <memory.h>

void TLinkedListCreate(TLinkedList* self)
{
    if (self == NULL)
    {
        return;
    }

    self->Head = NULL;
    self->Tail = NULL;
    self->Length = 0;
}

int TLinkedListAddAtFront(TLinkedList* self, void* Data)
{
    if (self == NULL)
    {
        return 0;
    }

    TLinkedListNode* NewNode = malloc(sizeof(TLinkedListNode));
    NewNode->Data = Data;
    NewNode->Next = NULL;

    if (self->Head == NULL)
    {
        self->Head = NewNode;
        self->Tail = NewNode;
    }
    else
    {
        NewNode->Next = self->Head;
        self->Head = NewNode;
    }

    self->Length++;
    return 1;
}

int TLinkedListAddAtBack(TLinkedList *self, void *Data)
{
    if (self == NULL)
    {
        return 0;
    }

    TLinkedListNode* NewNode = malloc(sizeof(TLinkedListNode));
    NewNode->Data = malloc(sizeof(Data));
    memcpy(NewNode->Data, Data, sizeof(Data));
    NewNode->Next = NULL;

    if (self->Head == NULL)
    {
        self->Head = NewNode;
        self->Tail = NewNode;
    }
    else
    {
        self->Tail->Next = NewNode;
        self->Tail = NewNode;
    }

    self->Length++;
    return 1;
}

int TLinkedListRemove(TLinkedList* self, const int Index)
{
    if (self == NULL)
    {
        return 0;
    }

    TLinkedListNode* Current = self->Head;
    TLinkedListNode* Previous = NULL;

    for (int i = 0; i < self->Length; ++i)
    {
        if (i == Index)
        {
            if (Previous == NULL)
            {
                self->Head = Current->Next;
            }
            else
            {
                Previous->Next = Current->Next;
            }

            if (Current == self->Tail)
            {
                self->Tail = Previous;
            }

            free(Current);
            break;
        }

        Previous = Current;
        Current = Current->Next;
    }

    self->Length--;
    return 1;
}

void TLinkedListDestroy(TLinkedList* self)
{
    if (self == NULL)
    {
        return;
    }

    TLinkedListNode* Current = self->Head;

    for (int i = 0; i < self->Length; ++i)
    {
        TLinkedListNode* next = Current->Next;
        free(Current);
        Current = next;
    }

    self->Head = NULL;
    self->Tail = NULL;
}

void* TLinkedListGet(TLinkedList* self, int Index)
{
    if (self == NULL)
    {
        return NULL;
    }

    TLinkedListNode* Current = self->Head;

    for (int i = 0; i < self->Length; ++i)
    {
        if (i == Index)
        {
            return Current->Data;
        }

        Current = Current->Next;
    }

    return NULL;
}

int TLinkedListSerialize(TLinkedList* self, FString* FileName, size_t ElementSize)
{
    FILE* File = fopen(FStringGetCharArray(FileName), "wb");
    if (File == NULL)
    {
        return 0;
    }

    unsigned Length = self->Length;
    fwrite(&Length, sizeof(unsigned), 1, File);

    for (TLinkedListNode* node = self->Head; node != NULL; node = node->Next)
    {
        fwrite(&node->Data, ElementSize, 1, File);
    }

    fclose(File);

    return 1;
}

int TLinkedListDeserialize(TLinkedList* self, FString* FileName, size_t ElementSize)
{
    FILE* File = fopen(FStringGetCharArray(FileName), "rb");
    if (File == NULL)
    {
        return 0;
    }

    unsigned length;
    fread(&length, sizeof(unsigned ), 1, File);

    TLinkedListCreate(self);

    for (unsigned i = 0; i < length; i++)
    {
        void* Data = malloc(ElementSize);
        fread(&Data, ElementSize, 1, File);

        TLinkedListAddAtBack(self, Data);
    }

    fclose(File);

    return 1;
}
