#include "StationList.h"

#include <malloc.h>
#include <stdio.h>
#include <memory.h>


void TDynamicArrayCreate(TDynamicArray* self)
{
    if (self == NULL)
    {
        return;
    }

    self->Length = 0;
    self->Array = NULL;
}

void TDynamicArrayDestroy(TDynamicArray *self)
{
    free(self->Array);
}

FStation* TDynamicArrayAddElement(TDynamicArray *self, FStation *Data)
{
    if (self == NULL || Data == NULL)
    {
        return NULL;
    }

    void* NewLocation = realloc(self->Array, (self->Length + 1) * sizeof(FStation));
    if (NewLocation == NULL)
    {
        return NULL;
    }

    self->Array = NewLocation;
    memcpy(&self->Array[self->Length], Data, sizeof(FStation));
    self->Length++;

    return &self->Array[self->Length - 1];
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

    free(&self->Array[self->Length - 1]);
    self->Length--;

    return 1;
}

FStation* TDynamicArrayGetElement(TDynamicArray *self, int Index)
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

int TDynamicArraySerialize(TDynamicArray* self, char* FileName)
{
    FILE* File = fopen(FileName, "wb");
    if (File == NULL)
    {
        return 0;
    }

    fwrite(&self->Length, sizeof(unsigned ), 1, File);
    for (unsigned i = 0; i < self->Length; i++)
    {
        fwrite(&self->Array[i], sizeof(FStation), 1, File);
    }

    fclose(File);
    return 1;
}

int TDynamicArrayDeserialize(TDynamicArray *self, char *FileName)
{
    FILE* File = fopen(FileName, "rb");
    if (File == NULL)
    {
        return 0;
    }

    fread(&self->Length, sizeof(unsigned), 1, File);
    self->Array = calloc(self->Length, sizeof(FStation));

    for (unsigned i = 0; i < self->Length; i++)
    {
        fread(&self->Array[i], sizeof(FStation), 1, File);
    }

    fclose(File);
    return 1;
}

