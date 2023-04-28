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
void FMetroManagerDestroy(FMetroManager* self);

// Visuals
void PrintStations(FMetroManager* self);
void PrintRoutes(FMetroManager* self);
void PrintMetro(FMetroManager* self);

// Routes
int AddRoute(FMetroManager* self, FRoute* NewRoute);
int DeleteRoute(FMetroManager* self, char* RouteName);
int UpdateRoutes(FMetroManager* self);
int AddStationToRoute(FMetroManager* self, char* StationCode, char* RouteName);
int AddStationToRouteByReference(FStation* Station, FRoute* Route);
int RemoveStationFromRoute(FMetroManager* self, char* StationCode, char* RouteName);
int AddRouteFromTextFile(FMetroManager* self, const char* Filename);
FRoute* FindRoute(FMetroManager* self, const char* RouteName);

// Stations
FStation* AddStation(FMetroManager* self, char* StationName);
int DeleteStation(FMetroManager* self, char* StationCode);
int SaveAllStations(FMetroManager* self, char* filename);
int LoadStations(FMetroManager* self, char* filename);
int GenerateValidStationCode(FMetroManager* self, char* OutCode);
FStation* FindStation(FMetroManager* self, char* Code);

// Todo: Implement function below
FRoute FMetroManagerCalculateRoute(FMetroManager* self, const char* StationCode1, const char* StationCode2);

#endif //TRABALHOPRATICO_METROMANAGER_H
