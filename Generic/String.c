#include <malloc.h>

#include <string.h>
#include <time.h>
#include "String.h"

int FStringCreate(FString *self, const char *InCharArray)
{
    if (self == NULL)
    {
        return 0;
    }

    unsigned CharArraySize = 0;
    for (int i = 0; InCharArray[i] != '\0'; ++i) {
        CharArraySize++;
    }

    self->String = calloc(CharArraySize, sizeof (char));
    if (self->String == NULL)
    {
        return 0;
    }

    for (int i = 0; i < CharArraySize; ++i) {
        self->String[i] = InCharArray[i];
    }

    self->String[CharArraySize] = '\0';
    self->Length = CharArraySize;
    return 1;
}

int FStringEdit(FString *self, char *InCharArray)
{
    if (self == NULL)
    {
        return 0;
    }

    if (strcmp(self->String, InCharArray) == 0)
    {
        return 1;
    }

    free(self->String);
    self->Length = 0;

    return FStringCreate(self, InCharArray);
}

int FStringDestroy(FString *self)
{
    if (self == NULL)
    {
        return 0;
    }

    free(self->String);
    self->Length = 0;
}

unsigned FStringGetLength(const FString *self)
{
    if (self == NULL)
    {
        return 0;
    }

    return self->Length;
}

char *FStringGetCharArray(const FString *self)
{
    if (self == NULL)
    {
        return 0;
    }

    return self->String;
}

int FStringCompare(const FString *self, const FString *other)
{
    if (self == NULL || other == NULL)
    {
        return 0;
    }

    return strcmp(self->String, other->String);
}

FString FStringGenerateRandom(const int Length)
{
    char Code[Length];
    for (int i = 0; i < Length; i++)
    {
        int RandNum = rand() % 36;
        if (RandNum < 26)
        {
            Code[i] = (char) ('A' + RandNum);
        }
        else
        {
            Code[i] = (char) ('0' + RandNum - 26);
        }
    }

    FString Result;
    FStringCreate(&Result, Code);
    return Result;
}
