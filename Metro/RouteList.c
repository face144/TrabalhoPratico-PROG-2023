#include "RouteList.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

int TLinkedListAddAtFront(TLinkedList* self, FRoute* Data)
{
    if (self == NULL)
    {
        TLinkedListNode Node;
        Node.Next = NULL;
        // Node.Data = NULL;
        return 0;
    }

    TLinkedListNode* NewNode = malloc(sizeof(TLinkedListNode));
    NewNode->Data = *Data;
    // malloc(sizeof(FRoute*));
    // memcpy(NewNode->Data, &Data, sizeof(FRoute));
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

int TLinkedListAddAtBack(TLinkedList *self, FRoute *Data)
{
    if (self == NULL)
    {
        TLinkedListNode Node;
        Node.Next = NULL;
        // Node.Data = NULL;
        return 0;
    }

    TLinkedListNode* NewNode = malloc(sizeof(TLinkedListNode));
    NewNode->Data = *Data;
    // malloc(sizeof(FRoute));
    // memcpy(NewNode->Data, &Data, sizeof(FRoute*));
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

            // free(Current->Data);
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

FRoute* TLinkedListGet(TLinkedList* self, int Index)
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
            return &Current->Data;
        }

        Current = Current->Next;
    }

    return NULL;
}

int TLinkedListSerialize(TLinkedList* self, char* FileName)
{
    FILE* File = fopen(FileName, "wb");
    if (File == NULL)
    {
        return 0;
    }

    unsigned Length = self->Length;
    fwrite(&Length, sizeof(unsigned), 1, File);

    for (TLinkedListNode* node = self->Head; node != NULL; node = node->Next)
    {
        fwrite(&node->Data, sizeof(FRoute), 1, File);
    }

    fclose(File);

    return 1;
}

int TLinkedListDeserialize(TLinkedList* self, char* FileName)
{
    FILE* File = fopen(FileName, "rb");
    if (File == NULL)
    {
        return 0;
    }

    unsigned length;
    fread(&length, sizeof(unsigned ), 1, File);

    for (unsigned i = 0; i < length; i++)
    {
        FRoute Data;
        fread(&Data, sizeof(FRoute), 1, File);

        Data.StationLength = 0;
        TLinkedListAddAtBack(self, &Data);
    }

    fclose(File);

    return 1;
}

