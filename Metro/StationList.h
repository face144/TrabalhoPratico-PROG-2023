#ifndef TRABALHOPRATICO_STATIONLIST_H
#define TRABALHOPRATICO_STATIONLIST_H

#include "Station.h"

typedef struct TDynamicArray
{
    FStation* Array;
    unsigned Length;

} TDynamicArray;

void TDynamicArrayCreate(TDynamicArray* self);
void TDynamicArrayDestroy(TDynamicArray *self);
FStation* TDynamicArrayAddElement(TDynamicArray *self, FStation *Data);
int TDynamicArrayRemoveElement(TDynamicArray *self, int Index);
FStation* TDynamicArrayGetElement(TDynamicArray *self, int Index);
int TDynamicArraySerialize(TDynamicArray* self, char* FileName);
int TDynamicArrayDeserialize(TDynamicArray* self, char* FileName);

#endif //TRABALHOPRATICO_STATIONLIST_H
