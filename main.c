#include "stdio.h"

#include "Generic/DynamicArray.h"
#include "Generic/LinkedList.h"

void DynamicArrayTest()
{
    TDynamicArray DynamicArray;
    TDynamicArrayCreate(&DynamicArray);

    for (int i = 0; i < 3; ++i) {
        TDynamicArrayAddElement(&DynamicArray, &i);
    }

    for (int i = 0; i < 3; ++i) {
        int* Element = TDynamicArrayGetElement(&DynamicArray, i);
    }
    printf("\n");

    FString Filename;
    FStringCreate(&Filename, "file.bin");

    TDynamicArraySerialize(&DynamicArray, &Filename);

    TDynamicArray DynamicArray2;
    TDynamicArrayDeserialize(&DynamicArray2, &Filename);

    printf("Length: %d | ", DynamicArray2.Length);
    for (int i = 0; i < DynamicArray2.Length; ++i) {
        int* Element = TDynamicArrayGetElement(&DynamicArray2, i);
        printf("%d ", *Element);
    }
}

void LinkedListTest()
{
    TLinkedList List;
    TLinkedListCreate(&List);

    for (int i = 0; i < 3; ++i) {
        TLinkedListAddAtBack(&List, &i);
    }

    printf("Printing...\n");
    for (int i = 0; i < 3; ++i) {
        int* Element = TLinkedListGet(&List, i);
        printf("%d ", *Element);
    }
    printf("\n");
    printf("Printing complete\n");

    FString Filename;
    FStringCreate(&Filename, "file.bin");

    TLinkedListSerialize(&List, &Filename, sizeof(int));

    TLinkedList List2;
    TLinkedListDeserialize(&List, &Filename, sizeof(int));

    printf("Size = %d | ", List2.Length);
    for (int i = 0; i < List2.Length; ++i) {
        int* Element = TLinkedListGet(&List2, i);
        printf("%d ", *Element);
    }
}

int main()
{

    return 0;
}
