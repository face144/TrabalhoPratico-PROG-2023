#include "Station.h"

void SetStationCode(FStation *self, const FString *StationCode)
{
    if (self == NULL)
    {
        return;
    }

    self->StationName = *StationCode;
}

FString GetStationCode(const FStation *self)
{
    if (self == NULL) {
        FString Result;
        FStringCreate(&Result, "Invalid");
        return Result;
    }

    return self->StationCode;
}

void SetStationName(FStation *self, const FString *StationName)
{
    if (self == NULL)
    {
        return;
    }

    self->StationName = *StationName;
}

FString GetStationName(const FStation *self)
{
    if (self == NULL) {
        FString Result;
        FStringCreate(&Result, "Invalid");
        return Result;
    }

    return self->StationName;
}
