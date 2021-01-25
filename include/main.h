#ifndef BUBBLESORT_MAIN_H
#define BUBBLESORT_MAIN_H

#define LARGER 1
#define SIMILAR 0
#define SMALLER -1

typedef struct _TEXT {
    char *szText;
    int iLength;
    struct _TEXT **ptxArray;
} TEXT;

void sort(TEXT **ptxArray, int iSize);
int compare(TEXT *txText0, TEXT *txText1);
void swap(TEXT **ptxArray, int i, int j);
void printArray(TEXT **ptxArray, int iSize);
int getIndex(TEXT *txText);

#endif //BUBBLESORT_MAIN_H
