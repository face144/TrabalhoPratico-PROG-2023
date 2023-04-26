#include <malloc.h>
#include <stdio.h>
#include "MetroManager.h"


FMetroManager FMetroManagerCreate() {
    FMetroManager result;
    TDynamicArrayCreate(&result.StationList);
    TLinkedListCreate(&result.RouteList);
    return result;
}


void PrintStations(FMetroManager* self)
{
    printf("\n");
    for (int i = 0; i < self->StationList.Length; ++i)
    {
        FStation* Current = &self->StationList.Array[i];
        printf("------------------\n");
        printf("Estacao %d\n", i + 1);
        printf("Nome: %s\n", Current->StationName);
        printf("Codigo: %s\n", Current->StationCode);
        printf("Linha: %s\n", Current->RouteName);
        printf("------------------\n");
    }
    printf("\n");
}


void PrintRoutes(FMetroManager *self)
{
    printf("\n");
    for (int i = 0; i < self->RouteList.Length; ++i)
    {
        FRoute* CurrentRoute = TLinkedListGet(&self->RouteList, i);
        printf("------------------\n");
        printf("Nome: %s\n", CurrentRoute->RouteName);
        printf("Numero de Estacoes: %d\n", CurrentRoute->StationLength);

        for (int j = 0; j < CurrentRoute->StationLength; ++j)
        {
            FStation* CurrentStation = CurrentRoute->StationList[i];
            char* Name = CurrentStation->StationName;
            char* Code = CurrentStation->StationCode;
            printf("Nome: %s | Codigo: %s\n", Name, Code);
        }
        printf("------------------\n");
    }
    printf("\n");
}

int AddRoute(FMetroManager* self, FRoute* NewRoute)
{
    char* NewRouteName = NewRoute->RouteName;
    for (int i = 0; i < self->RouteList.Length; ++i)
    {
        char* CurrentRouteName = TLinkedListGet(&self->RouteList, i)->RouteName;
        if (strcmp(NewRouteName, CurrentRouteName) == 0)
        {
            return 0;
        }
    }

    return TLinkedListAddAtBack(&self->RouteList, NewRoute);
}

int DeleteRoute(FMetroManager* self, int Index)
{
    return TLinkedListRemove(&self->RouteList, Index);
}

int UpdateRoutes(FMetroManager *self)
{
    for (int i = 0; i < self->StationList.Length; ++i)
    {
        FStation* CurrentStation = &self->StationList.Array[i];
        for (int j = 0; j < self->RouteList.Length; ++j)
        {
            FRoute* CurrentRoute = TLinkedListGet(&self->RouteList, j);
            if (strcmp(CurrentStation->RouteName, CurrentRoute->RouteName) == 0)
            {

            }
        }
    }
}

FStation* AddStation(FMetroManager *self, char* StationName)
{
    FStation New;

    if (self == NULL)
    {
        return NULL;
    }

    char Code[STATION_CODE_LENGTH + 1];
    GenerateValidStationCode(self, Code);

    strcpy(New.StationName, StationName);
    strcpy(New.StationCode, Code);
    strcpy(New.RouteName, "N/A");

    return TDynamicArrayAddElement(&self->StationList, &New);
}

int DeleteStation(FMetroManager *self, char* StationCode)
{
    if (self == NULL)
    {
        return 0;
    }

    for (int i = 0; i < self->StationList.Length; ++i)
    {
        if (strcmp(self->StationList.Array[i].StationCode, StationCode) == 0)
        {
            return TDynamicArrayRemoveElement(&self->StationList, i);
        }
    }

    return 0;
}

int SaveAllStations(FMetroManager* self, char* filename)
{
    return TDynamicArraySerialize(&self->StationList, filename);
}

int LoadStations(FMetroManager* self, char* filename)
{
    return TDynamicArrayDeserialize(&self->StationList, filename);
}

int AddStationToRoute(FMetroManager *self, char *StationCode, char *RouteName)
{
    return 0;
}

int GenerateValidStationCode(FMetroManager *self, char* OutCode)
{
    char Code[STATION_CODE_LENGTH + 1];
    int bIsCodeValid = 1;
    do
    {
        for (int i = 0; i < STATION_CODE_LENGTH; i++)
        {
            int RandNum = rand() % 36;
            if (RandNum < 26) {
                Code[i] = (char) ('A' + RandNum);
            } else {
                Code[i] = (char) ('0' + RandNum - 26);
            }
        }
        Code[STATION_CODE_LENGTH] = '\0';

        bIsCodeValid = 1;
        for (int i = 0; i < self->StationList.Length; ++i)
        {
            char* CurrentCode = self->StationList.Array[i].StationCode;
            if (strcmp(CurrentCode, Code) == 0)
            {
                bIsCodeValid = 0;
                break;
            }
        }

    } while (bIsCodeValid == 0);

    strcpy(OutCode, Code);
    return 1;
}
