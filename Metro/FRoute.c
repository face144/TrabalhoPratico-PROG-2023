#include "FRoute.h"

#include <stdio.h>

FRoute FRouteCreate()
{
    FRoute result;

    strcpy(result.RouteName, "RouteName");
    result.StationLength = 0;

    return result;
}

int AddStationReference(FRoute *self, FStation *NewStation)
{
    if (self == NULL || NewStation == NULL)
    {
        return 0;
    }

    self->StationList[self->StationLength] = NewStation;
    self->StationLength++;

    return 1;
}

int UpdateStationReferences(FRoute *self)
{
    if (self == NULL)
    {
        return 0;
    }

    for (int i = 0; i < self->StationLength; ++i)
    {
        if (self->StationList[i] == NULL)
        {
            for (int j = i; j < self->StationLength; j++)
            {
                self->StationList[j] = self->StationList[j + 1];
            }

            self->StationLength--;
        }
    }

    return 1;
}
