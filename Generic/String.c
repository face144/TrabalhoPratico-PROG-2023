#include <malloc.h>

#include <string.h>
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

    FStringDestroy(self);
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
    char Code[Length + 1];
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
    Code[Length] = '\0';

    FString Result;
    FStringCreate(&Result, Code);
    return Result;
}

int FStringAppend(FString *self, const char *InCharArray)
{
    unsigned Size = strlen(InCharArray) + self->Length + 1;
    char NewString[Size];

    unsigned Index = 0;
    for (unsigned i = 0; i < self->Length; ++i)
    {
        NewString[Index++] = self->String[i];
    }
    for (unsigned i = 0; i < strlen(InCharArray); ++i)
    {
        NewString[Index++] = InCharArray[i];
    }
    NewString[Size - 1] = '\0';

    FStringDestroy(self);
    return FStringCreate(self, NewString);
}

int FStringContainsExtension(FString *self, const char *ExtensionToCheck) {
    unsigned ExtensionLength = strlen(ExtensionToCheck);

    for (int i = (int) self->Length - 1; i >= 0; --i) {
        if (self->String[i] == '.')
        {
            unsigned StringIndex = i, ExtensionIndex = 0;
            while (ExtensionIndex < ExtensionLength && StringIndex < self->Length)
            {
                char StringChar = self->String[StringIndex];
                char ExtensionChar = ExtensionToCheck[ExtensionIndex];

                if (StringChar != ExtensionChar)
                {
                    return 0;
                }

                ExtensionIndex++;
                StringIndex++;
            }

            if (StringIndex == self->Length && ExtensionIndex == ExtensionLength)
            {
                return 1;
            }

            return 0;
        }
    }

    return 0;
}