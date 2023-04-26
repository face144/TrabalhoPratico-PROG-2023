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

int GetRouteFromTextFile(FRoute *self, const char *Filename)
{
    // Todo: Retornar erro se estacoes do ficheiro nao existem

    if (self == NULL || Filename == NULL)
    {
        return 0;
    }

    FILE* File = fopen(Filename, "r");
    if (File == NULL)
    {
        return 0;
    }

    char Line[FILE_LINE_MAX_CHAR];

    fgets(Line, sizeof(Line), File);
    strcpy(self->RouteName, Line);
    // printf("Got route name: %s", self->RouteName);

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

        FStation New;
        strcpy(New.StationName, StationName);
        strcpy(New.StationCode, StationCode);
    }

    fclose(File);

    return 1;
}

