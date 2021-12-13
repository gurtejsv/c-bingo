#ifndef LIST_H
#define LIST_H

typedef struct {
        int currentIndex;
        int *list;
} Array;

void INITIALIZE(Array *, int);
int CHECK(Array *, int);
void ADD(Array *, int);
void PRINT(Array *);
int GET(Array *, int);
int INDEX_OF(Array *, int);
void SET(Array *, int, int);
int CURRENT_INDEX(Array *);

#endif