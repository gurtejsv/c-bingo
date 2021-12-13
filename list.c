#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void INITIALIZE(Array *A, int size) {
    A->list=(int *)malloc(sizeof(int)*size);
    A->currentIndex=0;
}

int CHECK(Array *A, int num) {
    for (int i=0; i<A->currentIndex; i++) {
        if (A->list[i] == num) {
            return 0;
        }
    }
    return 1;
}

void ADD(Array *A, int num) {
    A->list[A->currentIndex]=num;
    A->currentIndex++;
}

void PRINT(Array *A) {
    for (int i=0; i<A->currentIndex; i++) {
        printf("%i ", A->list[i]);
    }
    printf("\n");
}

int GET(Array *A, int index) {
    return A->list[index];
}

int INDEX_OF(Array *A, int num) {
    for (int i=0; i<A->currentIndex; i++) {
        if (A->list[i] == num) {
            return i;
        }
    }
    return -1;
}

void SET(Array *A, int index, int num) {
    if (A->currentIndex > index) {
        A->list[index]=num;
    }
}

int CURRENT_INDEX(Array *A) {
    return A->currentIndex;
}