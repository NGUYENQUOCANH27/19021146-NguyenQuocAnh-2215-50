#include <iostream>

int* merge(int* firstArr, int lenArr1, int* secondArr, int lenArr2) {
    int* mergeArr = new int[lenArr1 + lenArr2];
    int firstIndex = 0, secondIndex = 0, mergeIndex = 0;

    bool ascending = (lenArr1 > 1 && firstArr[0] < firstArr[1]) || (lenArr2 > 1 && secondArr[0] < secondArr[1]);

    if (ascending) {
        while (firstIndex < lenArr1 && secondIndex < lenArr2) {
            if (firstArr[firstIndex] <= secondArr[secondIndex]) {
                mergeArr[mergeIndex++] = firstArr[firstIndex++];
            } else {
                mergeArr[mergeIndex++] = secondArr[secondIndex++];
            }
        }
    } else {
        while (firstIndex < lenArr1 && secondIndex < lenArr2) {
            if (firstArr[firstIndex] >= secondArr[secondIndex]) {
                mergeArr[mergeIndex++] = firstArr[firstIndex++];
            } else {
                mergeArr[mergeIndex++] = secondArr[secondIndex++];
            }
        }
    }

    while (firstIndex < lenArr1) {
        mergeArr[mergeIndex++] = firstArr[firstIndex++];
    }

    while (secondIndex < lenArr2) {
        mergeArr[mergeIndex++] = secondArr[secondIndex++];
    }

    return mergeArr;
}


