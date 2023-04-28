#include <malloc.h>
#include <stdio.h>
#include "MetroManager.h"


FMetroManager FMetroManagerCreate() {
    FMetroManager result;
    TDynamicArrayCreate(&result.StationList);
    TLinkedListCreate(&result.RouteList);
    return result;
}

void FMetroManagerDestroy(FMetroManager* self)
{
    TDynamicArrayDestroy(&self->StationList);
    TLinkedListDestroy(&self->RouteList);
}

void PrintStations(FMetroManager* self)
{
    if (self->StationList.Length == 0)
    {
        printf("Nao existem estacoes\n");
    }

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
    if (self->RouteList.Length == 0)
    {
        printf("Nao existem rotas\n");
    }

    printf("\n");
    for (int i = 0; i < self->RouteList.Length; ++i)
    {
        FRoute* CurrentRoute = TLinkedListGet(&self->RouteList, i);
        printf("------------------\n");
        printf("Nome: %s\n", CurrentRoute->RouteName);
        printf("Numero de Estacoes: %d\n", CurrentRoute->StationLength);

        for (int j = 0; j < CurrentRoute->StationLength; ++j)
        {
            FStation* CurrentStation = CurrentRoute->StationList[j];
            char* Name = CurrentStation->StationName;
            char* Code = CurrentStation->StationCode;
            printf("%d-> Nome: %s | Codigo: %s\n", j + 1, Name, Code);
        }
        printf("------------------\n");
    }
    printf("\n");
}

void PrintMetro(FMetroManager *self)
{
    if (self->RouteList.Length == 0)
    {
        printf("Nao existem rotas\n");
    }
    else
    {
        printf("*** ROTAS ***");
        PrintRoutes(self);
    }

    printf("\n");

    if (self->StationList.Length == 0)
    {
        printf("Nao existem estacoes\n");
    }
    else
    {
        printf("\n");
        printf("*** ESTACOES SEM ROTAS ASSOCIADAS ***\n");

        for (int i = 0; i < self->StationList.Length; ++i)
        {
            FStation* Current = &self->StationList.Array[i];

            if (strcmp(Current->RouteName, "N/A") == 0)
            {
                printf("------------------\n");
                printf("Nome: %s\n", Current->StationName);
                printf("Codigo: %s\n", Current->StationCode);
                printf("------------------\n");
            }
        }

        printf("\n");
    }
}

int AddRoute(FMetroManager* self, FRoute* NewRoute)
{
    char* NewRouteName = NewRoute->RouteName;
    if (strlen(NewRouteName) < 3)
    {
        return 0;
    }

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

int DeleteRoute(FMetroManager* self, char* RouteName)
{
    for (int i = 0; i < self->RouteList.Length; ++i)
    {
        FRoute* Current = TLinkedListGet(&self->RouteList, i);
        if (strcmp(Current->RouteName, RouteName) == 0)
        {
            for (int j = 0; j < Current->StationLength; ++j)
            {
                strcpy(Current->StationList[j]->RouteName, "N/A");
            }

            TLinkedListRemove(&self->RouteList, i);
            return 1;
        }
    }

    return 0;
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
                AddStationToRouteByReference(CurrentStation, CurrentRoute);
            }
        }
    }

    return 1;
}

FStation* AddStation(FMetroManager *self, char* StationName)
{
    FStation New;

    if (self == NULL || strlen(StationName) < 3)
    {
        return NULL;
    }

    for (int i = 0; i < self->StationList.Length; ++i)
    {
        if (strcmp(self->StationList.Array[i].StationName, StationName) == 0)
        {
            return NULL;
        }
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
    FStation* Station = NULL;
    for (int i = 0; i < self->StationList.Length; ++i)
    {
        if (strcmp(self->StationList.Array[i].StationCode, StationCode) == 0)
        {
            Station = &self->StationList.Array[i];
            break;
        }
    }

    if (Station == NULL)
    {
        return 0;
    }

    unsigned Length = self->RouteList.Length;
    if (Length >= ROUTE_MAX_STATIONS)
    {
        return 0;
    }

    TLinkedList* List = &self->RouteList;
    for (int i = 0; i < Length; ++i)
    {
        FRoute* CurrentRoute = TLinkedListGet(List, i);
        if (strcmp(CurrentRoute->RouteName, RouteName) == 0)
        {
            CurrentRoute->StationList[CurrentRoute->StationLength] = Station;
            CurrentRoute->StationLength++;
            strcpy(Station->RouteName, CurrentRoute->RouteName);
            return 1;
        }
    }

    return 0;
}

int AddStationToRouteByReference(FStation *Station, FRoute *Route)
{
    if (Route->StationLength >= ROUTE_MAX_STATIONS)
    {
        return 0;
    }

    Route->StationList[Route->StationLength] = Station;
    Route->StationLength++;
    strcpy(Station->RouteName, Route->RouteName);
    return 1;
}

int RemoveStationFromRoute(FMetroManager *self, char *StationCode, char *RouteName)
{
    unsigned Length = self->RouteList.Length;
    TLinkedList* List = &self->RouteList;
    FRoute* RouteReference = NULL;
    for (int i = 0; i < Length; ++i)
    {
        FRoute* CurrentRoute = TLinkedListGet(List, i);
        if (strcmp(CurrentRoute->RouteName, RouteName) == 0)
        {
            RouteReference = CurrentRoute;
            break;
        }
    }

    if (RouteReference == NULL)
    {
        return 0;
    }

    for (int i = 0; i < RouteReference->StationLength; ++i)
    {
        if (strcmp(RouteReference->StationList[i]->StationCode, StationCode) == 0)
        {
            for (int j = i; j < RouteReference->StationLength - 1; ++j)
            {
                RouteReference->StationList[i] = RouteReference->StationList[i + 1];
            }

            unsigned LastIndex = RouteReference->StationLength - 1;
            strcpy(RouteReference->StationList[LastIndex]->RouteName, "N/A");
            RouteReference->StationLength--;
            return 1;
        }
    }

    return 0;
}

int AddRouteFromTextFile(FMetroManager* self, const char *Filename)
{
    if (self == NULL || Filename == NULL)
    {
        return 0;
    }

    FILE* File = fopen(Filename, "r");
    if (File == NULL)
    {
        return 0;
    }

    FRoute NewRoute = FRouteCreate();
    char Line[FILE_LINE_MAX_CHAR];

    fgets(Line, sizeof(Line), File);
    Line[strlen(Line) - 1] = '\0';
    strcpy(NewRoute.RouteName, Line);

    // Verificar se a rota ja existe
    if (FindRoute(self, NewRoute.RouteName) != NULL)
    {
        fclose(File);
        return 0;
    }

    for (int i = 0; fgets(Line, sizeof(Line), File) != NULL; ++i)
    {
        char* StationName = strtok(Line, "#");
        if (StationName[strlen(StationName) - 1] == '\n' ||
            StationName[strlen(StationName) - 1] == ' ')
        {
            StationName[strlen(StationName) - 1] = '\0';
        }

        // Cleanup the string
        char* StationCode = strtok(NULL, " ");
        if (StationCode[strlen(StationCode) - 1] == '\n' ||
            StationCode[strlen(StationCode) - 1] == ' ')
        {
            StationCode[strlen(StationCode) - 1] = '\0';
        }

        // Verifica se a estacao existe
        FStation* Station = FindStation(self, StationCode);
        if (Station == NULL)
        {
            // Estacao nao existe
            fclose(File);
            return 0;
        }

        NewRoute.StationList[NewRoute.StationLength] = Station;
        NewRoute.StationLength++;
    }

    fclose(File);

    AddRoute(self, &NewRoute);
    for (int i = 0; i < NewRoute.StationLength; ++i)
    {
        FStation* Current = NewRoute.StationList[i];
        strcpy(Current->RouteName, NewRoute.RouteName);
    }

    return 1;
}

FRoute* FindRoute(FMetroManager* self, const char* RouteName)
{
    for (int i = 0; i < self->RouteList.Length; ++i)
    {
        FRoute* Current = TLinkedListGet(&self->RouteList, i);
        if (strcmp(Current->RouteName, RouteName) == 0)
        {
            return Current;
        }
    }

    return NULL;
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

FStation* FindStation(FMetroManager *self, char* Code)
{
    for (int i = 0; i < self->StationList.Length; ++i)
    {
        if (strcmp(self->StationList.Array[i].StationCode, Code) == 0)
        {
            return &self->StationList.Array[i];
        }
    }

    return NULL;
}
