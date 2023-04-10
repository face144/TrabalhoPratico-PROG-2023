#ifndef TRABALHOPRATICO_DYNAMICARRAY_H
#define TRABALHOPRATICO_DYNAMICARRAY_H

#include "String.h"

typedef struct TDynamicArray
{
    void** Array;
    unsigned Length;

} TDynamicArray;

void TDynamicArrayCreate(TDynamicArray* self);
void TDynamicArrayDestroy(TDynamicArray *self);
int TDynamicArrayAddElement(TDynamicArray *self, void *Data);
int TDynamicArrayRemoveElement(TDynamicArray *self, int Index);
void* TDynamicArrayGetElement(TDynamicArray *self, int Index);
int TDynamicArraySerialize(TDynamicArray* self, FString* FileName);
int TDynamicArrayDeserialize(TDynamicArray* self, FString* FileName);

#endif //TRABALHOPRATICO_DYNAMICARRAY_H