#include "Station.h"

void SetStationCode(FStation *self, char *StationCode)
{
    if (self == NULL)
    {
        return;
    }

    strcpy(self->StationCode, StationCode);
}

void SetStationName(FStation *self, char *StationName)
{
    if (self == NULL)
    {
        return;
    }

    strcpy(self->StationName, StationName);
}

FStation FStationCreate() {
    FStation result;
    strcpy(result.StationName, "StationName\0");
    strcpy(result.StationCode, "StationCode\0");
    strcpy(result.RouteName, "RouteName\0");
    return result;
}
