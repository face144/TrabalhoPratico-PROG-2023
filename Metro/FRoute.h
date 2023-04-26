#ifndef TRABALHOPRATICO_FROUTE_H
#define TRABALHOPRATICO_FROUTE_H

#include "Station.h"

#define FILE_LINE_MAX_CHAR 64
#define ROUTE_MAXCHAR 64
#define ROUTE_MAX_STATIONS 128

typedef struct FRoute
{
    char RouteName[ROUTE_MAXCHAR];
    FStation* StationList[ROUTE_MAX_STATIONS];
    unsigned StationLength;

} FRoute;

FRoute FRouteCreate();
int AddStationReference(FRoute* self, FStation* NewStation);
int UpdateStationReferences(FRoute* self);

int GetRouteFromTextFile(FRoute* self, const char* Filename);

#endif //TRABALHOPRATICO_FROUTE_H
