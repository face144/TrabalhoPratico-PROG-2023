#ifndef TRABALHOPRATICO_FROUTE_H
#define TRABALHOPRATICO_FROUTE_H

#include "../Generic/DynamicArray.h"
#include "Station.h"

typedef struct FRoute
{
    TDynamicArray StationList;

} FRoute;

int AddStation(FRoute* self, FStation* NewStation);
int RemoveStation(FRoute* self, const FString* StationCode);
FStation* GetStation(FRoute *self, const int Index);

#endif //TRABALHOPRATICO_FROUTE_H
