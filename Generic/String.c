/*
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

FString FStringNew(const char *InCharArray)
{
    FString Result;

    unsigned CharArraySize = 0;
    for (int i = 0; InCharArray[i] != '\0' && InCharArray[i] != '\n'; ++i)
    {
        CharArraySize++;
    }

    Result.String = calloc(CharArraySize, sizeof (char));
    if (Result.String == NULL)
    {
        Result.Length = -1;
    }

    for (int i = 0; i < CharArraySize; ++i)
    {
        Result.String[i] = InCharArray[i];
    }

    Result.String[CharArraySize] = '\0';
    Result.Length = CharArraySize;

    return Result;
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

    unsigned Length = 0;
    for (int i = 0; i < strlen(InCharArray); ++i)
    {
        if (InCharArray[i] == '\n' || InCharArray[i] == '\0')
        {
            Length = i + 1;
            break;
        }
    }

    char* NewString = calloc(Length, sizeof(char));
    if (self->Length > 0)
    {
        free(self->String);
    }

    for (int i = 0; i < strlen(InCharArray); ++i)
    {
        NewString[i] = InCharArray[i];
    }

    self->Length = strlen(InCharArray);
    self->String = NewString;
    self->String[Length] = '\0';
}

int FStringDestroy(FString *self)
{
    if (self == NULL)
    {
        return 0;
    }

    if (self->Length > 0)
    {
        free(self->String);
        self->Length = 0;
    }
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

int FStringSplit(FString *self, FString *other, char Token)
{
    // char FirstPart[self->Length];

    for (int i = 0; i < self->Length; ++i)
    {
        // FirstPart[i] = self->String[i];

        if (self->String[i] == Token)
        {
            if (i + 1 >= self->Length)
            {
                return 0;
            }

            // Terminate the first part with a null character
            self->String[i] = '\0';
            // Skip the token character
            i++;

            // FStringAppend(other, &self->String[i]);
            other->String = &self->String[i];
            other->Length = self->Length - i;

            // FStringDestroy(self);
            // FStringCreate(self, FirstPart);
            self->Length = i - 1;

            return 1;
        }
    }

    return 0;
}
*/
