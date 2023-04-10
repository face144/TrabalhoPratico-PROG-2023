#include "stdio.h"

#include "Generic/DynamicArray.h"

int main() {
    TDynamicArray DynamicArray;
    TDynamicArrayCreate(&DynamicArray);

    for (int i = 0; i < 3; ++i) {
        TDynamicArrayAddElement(&DynamicArray, &i);
    }

    for (int i = 0; i < 3; ++i) {
        int* Element = DynamicArray.Array[i];
        printf("%d ", *Element);
    }
    printf("\n");

    FString Filename;
    FStringCreate(&Filename, "file.bin");

    TDynamicArraySerialize(&DynamicArray, &Filename);

    TDynamicArray DynamicArray2;
    TDynamicArrayDeserialize(&DynamicArray, &Filename);

    for (int i = 0; i < DynamicArray.Length; ++i) {
        int* Element = TDynamicArrayGetElement(&DynamicArray2, i);
        printf("%d ", *Element);
    }

    return 0;
}
