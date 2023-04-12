#ifndef TRABALHOPRATICO_STRING_H
#define TRABALHOPRATICO_STRING_H

typedef struct FString
{
    char* String;
    unsigned Length;

} FString;

int FStringCreate(FString* self, const char* InCharArray);
int FStringEdit(FString* self, char* InCharArray);
int FStringDestroy(FString* self);
unsigned FStringGetLength(const FString* self);
char* FStringGetCharArray(const FString* self);
int FStringCompare(const FString* self, const FString* other);
FString FStringGenerateRandom(const int Length);
int FStringAppend(FString* self, const char* InCharArray);
int FStringContainsExtension(FString* self, const char* ExtensionToCheck);

#endif //TRABALHOPRATICO_STRING_H
