#ifndef TRABALHOPRATICO_METROMANAGER_H
#define TRABALHOPRATICO_METROMANAGER_H

#include "FRoute.h"
#include "RouteList.h"
#include "StationList.h"

#define STATION_CODE_LENGTH 4

typedef struct FMetroManager
{
    TLinkedList RouteList;
    TDynamicArray StationList;

} FMetroManager;

FMetroManager FMetroManagerCreate();

// Visuals
void PrintStations(FMetroManager* self);
void PrintRoutes(FMetroManager* self);

// Routes
int AddRoute(FMetroManager* self, FRoute* NewRoute);
int DeleteRoute(FMetroManager* self, int Index);
int UpdateRoutes(FMetroManager* self);
// Todo:
int AddStationToRoute(FMetroManager* self, char* StationCode, char* RouteName);

// Stations
FStation* AddStation(FMetroManager* self, char* StationName);
int DeleteStation(FMetroManager* self, char* StationCode);
int SaveAllStations(FMetroManager* self, char* filename);
int LoadStations(FMetroManager* self, char* filename);
int GenerateValidStationCode(FMetroManager* self, char* OutCode);

// Todo: Implement function below
FRoute FMetroManagerCalculateRoute(FMetroManager* self, const char* StationCode1, const char* StationCode2);

#endif //TRABALHOPRATICO_METROMANAGER_H
