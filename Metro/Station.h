#ifndef TRABALHOPRATICO_STATION_H
#define TRABALHOPRATICO_STATION_H

#include "string.h"
#include "../Generic/String.h"

typedef struct FStation
{
    FString StationName;
    FString StationCode;

} FStation;

void SetStationCode(FStation* self, const FString* StationCode);
FString GetStationCode(const FStation* self);
void SetStationName(FStation* self, const FString* StationName);
FString GetStationName(const FStation* self);

#endif //TRABALHOPRATICO_STATION_H
