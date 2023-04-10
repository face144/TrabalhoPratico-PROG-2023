#include "MetroManager.h"


FString FMetroManagerGenerateValidStationCode(FMetroManager *self)
{
    if (self == NULL)
    {
        FString Invalid;
        FStringCreate(&Invalid, "Invalid");
        return Invalid;
    }

    while (1)
    {
        FString Code = FStringGenerateRandom(STATION_CODE_LENGTH);
        for (int i = 0; i < self->RouteList.Length; ++i)
        {
            TLinkedListNode *Route = TLinkedListGet(&self->RouteList, i);
            if (Route == NULL) continue;

            FStation *Station = Route->Data;
            if (Station == NULL) continue;

            if (FStringCompare(&Station->StationCode, &Code) == 0)
            {
                FStringDestroy(&Code);
                break;
            }
        }
        return Code;
    }
}

void FMetroManagerAddNewRoute(FMetroManager *self, FRoute NewRoute)
{
    TLinkedListAddAtBack(&self->RouteList, &NewRoute);
}

FRoute* FMetroManagerGetRoute(FMetroManager *self, int Index)
{
    return TLinkedListGet(&self->RouteList, Index);
}
