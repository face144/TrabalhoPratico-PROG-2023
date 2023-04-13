#include <malloc.h>
#include <stdio.h>
#include <memory.h>
#include "DynamicArray.h"


void TDynamicArrayCreate(TDynamicArray* self, const size_t ElementSize)
{
    if (self == NULL)
    {
        return;
    }

    self->Length = 0;
    self->Array = malloc(sizeof(void*));
    self->Array = NULL;
    self->ElementSize = ElementSize;
}

void TDynamicArrayDestroy(TDynamicArray *self)
{
    free(self->Array);
}

int TDynamicArrayAddElement(TDynamicArray *self, void *Data)
{
    if (self == NULL || Data == NULL)
    {
        return 0;
    }

    void* NewLocation = realloc(self->Array, (self->Length + 1) * self->ElementSize);
    if (NewLocation == NULL)
    {
        return 0;
    }

    self->Array = NewLocation;
    memcpy(&self->Array[self->Length], Data, sizeof(Data));

    self->Array[self->Length + 1] = NULL;
    self->Length++;

    return 1;
}

int TDynamicArrayRemoveElement(TDynamicArray *self, const int Index)
{
    if (self == NULL)
    {
        return 0;
    }

    if (Index >= self->Length)
    {
        return 0;
    }

    for (int i = Index; i < self->Length - 1; i++) {
        self->Array[i] = self->Array[i + 1];
    }

    free(self->Array[self->Length]);
    self->Length--;
    self->Array[self->Length] = NULL;

    return 1;
}

void* TDynamicArrayGetElement(TDynamicArray *self, int Index)
{
    if (self == NULL)
    {
        return NULL;
    }

    if (Index >= self->Length) {
        return NULL;
    }

    return &self->Array[Index];
}

int TDynamicArraySerialize(TDynamicArray* self, FString* FileName)
{
    FILE* File = fopen(FStringGetCharArray(FileName), "wb");
    if (File == NULL)
    {
        return 0;
    }

    fwrite(&self->Length, sizeof(unsigned ), 1, File);
    for (unsigned i = 0; i < self->Length; i++)
    {
        fwrite(&self->Array[i], sizeof(self->ElementSize), 1, File);
    }

    fclose(File);
}

int TDynamicArrayDeserialize(TDynamicArray *self, FString *FileName)
{
    FILE* File = fopen(FStringGetCharArray(FileName), "rb");
    if (File == NULL)
    {
        return 0;
    }

    fread(&self->Length, sizeof(unsigned), 1, File);
    self->Array = calloc(self->Length, sizeof(void*));

    for (unsigned i = 0; i < self->Length; i++) {
        fread(&self->Array[i], sizeof(self->ElementSize), 1, File);
    }

    fclose(File);
}
