#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "main.h"

/* -- BUBBLESORT -- */
/* This program takes an array of a struct type and sorts it using bubbleSort */
int main(int argc, char **argv) {
    int i;
    int j;
    int failedMalloc = 0;
    int iArrSize = argc - 1;
    int indexOfElem;
    TEXT **ptxArray = malloc(sizeof(TEXT) * argc);

    if(argc == 1) {
        printf("Cannot create table without data. Please write some text as arguments\r\n");
    } else {
        if(ptxArray == NULL) {
            printf("ERROR in malloc: ptxArray\r\n");
        } else {
            memset(ptxArray, 0, sizeof(TEXT) * argc);

            for(i = 0; i < argc; i++) {
                ptxArray[i] = malloc(sizeof(TEXT));
                if(ptxArray[i] == NULL) {
                    //If one malloc were to fail -> break and quit
                    printf("ERROR in malloc: ptxArray[%i]\r\n", i);
                    failedMalloc = 1;
                    break;
                } else {
                    //Filling the TEXT struct
                    memset(ptxArray[i], 0, sizeof(TEXT));
                    ptxArray[i]->szText = argv[i+1];
                    ptxArray[i]->iLength = sizeof(argv[i+1]);
                    ptxArray[i]->ptxArray = ptxArray;
                }
            }

            if(failedMalloc) {
                //One malloc failed
                //Freeing only the allocated indexes
                for(j = 0; j < i; j++) {
                    free(ptxArray[j]);
                }

            } else {
                //If all goes well -> this is were we are
                //SORTING the array
                printf("Initial table:\r\n");
                printArray(ptxArray, iArrSize);

                sort(ptxArray, iArrSize);

                printf("Sorted table:\r\n");
                printArray(ptxArray, iArrSize);

                //Getting the INDEX of a struct
                indexOfElem = getIndex(ptxArray[iArrSize / 2]);
                printf("Index of elem in the middle: %i\r\n", indexOfElem);

                //Freeing all indexes
                for(j = 0; j < iArrSize; j++) {
                    free(ptxArray[j]);
                }
            }
            //Freeing the array itself
            free(ptxArray);
        }
    }

    return 0;
}
/* SORTS USING BUBBLESORT */
void sort(TEXT **ptxArray, int iSize) {
    int i;
    int isSorted = 0;
    int didASwap;

    while(isSorted == 0) {
        //reset every loop
        didASwap = 0;

        for (i = 0; i < iSize-1; i++) {
            //If ptxArray[i] is LARGER than ptxArray[i+1] -> swap them
            if ( compare(ptxArray[i], ptxArray[i+1]) == LARGER) {
                swap(ptxArray, i, i + 1);
                didASwap = 1;
            }
        }
        //If no swaps during this loop -> the array is sorted
        if (didASwap == 0) {
            isSorted = 1;
        }
    }
}
/* COMPARES TWO STRUCTS */
/* Returns if [txText0] is SMALLER, SIMILAR OR LARGER than [txText1] */
int compare(TEXT *txText0, TEXT *txText1) {
    int i;
    int comparison = SIMILAR;

    //Checking each char on the strings
    //Loop will end when determined one of them is larger
    // Or reaching the end of one of the two strings
    for(i = 0; i < txText0->iLength && i < txText1->iLength; i++) {

        //Parsing to int for readability
        if( (int)txText0->szText[i] < (int)txText1->szText[i] ) {
            comparison = SMALLER;
            break;
        } else if( (int)txText0->szText[i] > (int)txText1->szText[i] ) {
            comparison = LARGER;
            break;
        }
    }
    //If after the loop, the strings seem similar
    // -> Determine the longest of the strings: LARGER
    //If they are the same length -> nothing will be done; they are similar
    if(comparison == SIMILAR) {
        if(txText0->iLength < txText1->iLength) {
            comparison = SMALLER;
        } else if(txText0->iLength > txText1->iLength) {
            comparison = LARGER;
        }
    }

    return comparison;
}
/* SWAPPING TWO ELEMENTS */
void swap(TEXT **ptxArray, int i, int j) {
    TEXT *txTmp = ptxArray[i];
    ptxArray[i] = ptxArray[j];
    ptxArray[j] = txTmp;
}
/* PRINTING THE ARRAY */
void printArray(TEXT **ptxArray, int iSize) {
    int i;
    for(i = 0; i < iSize; i++) {
        printf("%i: %s\r\n", i, ptxArray[i]->szText);
    }
    printf("\r\n");
}
/* GETS THE INDEX OF AN ELEMENT */
int getIndex(TEXT *txText) {
    int i = 0;
    int iFound = 0;
    TEXT **ptxArray = txText->ptxArray;

    //Looping after the element similar
    while(ptxArray[i] != NULL) {
        if(ptxArray[i] == txText) {
            iFound = i;
            break;
        }
        i++;
    }
    return iFound;
}