#ifndef TRABALHOPRATICO_METROMANAGER_H
#define TRABALHOPRATICO_METROMANAGER_H

#include "FRoute.h"
#include "../Generic/LinkedList.h"

#define STATION_CODE_LENGTH 4

typedef struct FMetroManager
{
    TLinkedList RouteList;

} FMetroManager;

FString FMetroManagerGenerateValidStationCode(FMetroManager* self);
void FMetroManagerAddNewRoute(FMetroManager* self, FRoute NewRoute);
FRoute* FMetroManagerGetRoute(FMetroManager* self, int Index);
FRoute FMetroManagerCalculateRoute(FMetroManager* self, const FString* StationCode1, const FString* StationCode2);

#endif //TRABALHOPRATICO_METROMANAGER_H
