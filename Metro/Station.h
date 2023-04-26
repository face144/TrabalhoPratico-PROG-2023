#ifndef TRABALHOPRATICO_STATION_H
#define TRABALHOPRATICO_STATION_H

#include <string.h>

#define STATION_MAXCHAR 64

typedef struct FStation
{
    char StationName[STATION_MAXCHAR];
    char StationCode[STATION_MAXCHAR];
    char RouteName[STATION_MAXCHAR];

} FStation;

FStation FStationCreate();
void SetStationCode(FStation* self, char* StationCode);
void SetStationName(FStation* self, char* StationName);

#endif //TRABALHOPRATICO_STATION_H
