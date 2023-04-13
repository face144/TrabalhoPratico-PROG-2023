#include "FRoute.h"

int AddStation(FRoute *self, FStation *NewStation)
{
    if (self == NULL)
    {
        return 0;
    }

    return TDynamicArrayAddElement(&self->StationList, NewStation, sizeof(FStation));
}

int RemoveStation(FRoute *self, const FString *StationCode)
{
    if (self == NULL)
    {
        return 0;
    }

    for (int i = 0; i < self->StationList.Length; ++i)
    {
        FStation* Temp = TDynamicArrayGetElement(&self->StationList, i);
        if (FStringCompare(StationCode,&Temp->StationCode) == 0)
        {
            return TDynamicArrayRemoveElement(&self->StationList, i);
        }
    }
    return 0;
}

FStation* GetStation(FRoute *self, const int Index)
{
    if (self == NULL)
    {
        return NULL;
    }

    TDynamicArray* StationList = &self->StationList;
    return TDynamicArrayGetElement(StationList, Index);
}
