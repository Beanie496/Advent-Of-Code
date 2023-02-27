#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MIN(a,b) (a < b ? a : b)
#define MAX(a,b) (a > b ? a : b)


int main() {
    char** inputString;
    int sideLength = 99;
    char visibleTreesHorizontal[sideLength][sideLength];
    char visibleTreesVertical[sideLength][sideLength];
    FILE* inputs = fopen("inputs.txt", "r");
    int visibleTotal = 0;

    inputString = malloc(sideLength*sizeof(char*)); // 99 lines

    for (int i = 0; i < sideLength; i++) { // square, 99 in side length
        inputString[i] = malloc(sideLength*sizeof(char));
        fscanf(inputs, "%s", inputString[i]);
    }

    for (int row = 0; row < sideLength; row++) { // sets a grid of being viewed from the side
        for (int column = 0; column < sideLength; column++) {
            if (column == 0)
                visibleTreesHorizontal[row][column] = inputString[row][column];
            else
                visibleTreesHorizontal[row][column] = MAX(visibleTreesHorizontal[row][column - 1],inputString[row][column]);
        }
    }

    for (int row = 0; row < sideLength; row++) { // from other side
        for (int column = sideLength - 1; column >= 0; column--) {
            if (column == sideLength - 1)
                visibleTreesHorizontal[row][column] = inputString[row][column];
            else 
                visibleTreesHorizontal[row][column] = MIN(visibleTreesHorizontal[row][column],MAX(inputString[row][column],visibleTreesHorizontal[row][column + 1]));
        }
    }

    for (int column = 0; column < sideLength; column++) { // sets a grid of being viewed from the top
        for (int row = 0; row < sideLength; row++) {
            if (row == 0)
                visibleTreesVertical[row][column] = inputString[row][column];
            else
                visibleTreesVertical[row][column] = MAX(visibleTreesVertical[row - 1][column],inputString[row][column]);
        }
    }

    for (int column = 0; column < sideLength; column++) { // from bottom
        for (int row = sideLength - 1; row >= 0; row--) {
            if (row == sideLength - 1)
                visibleTreesVertical[row][column] = inputString[row][column];
            else 
                visibleTreesVertical[row][column] = MIN(visibleTreesVertical[row][column],MAX(inputString[row][column],visibleTreesVertical[row + 1][column]));
        }
    }
    
    for (int i = 0; i < sideLength; i++)
        printf("%.*s\n", sideLength, visibleTreesHorizontal[i]);

    for (int i = 0; i < sideLength; i++)
        printf("%.*s\n", sideLength, visibleTreesVertical[i]);

    for (int row = 0; row < sideLength; row++) {
        for (int column = 0; column < sideLength; column++) {
            if (row % (sideLength - 1) == 0 || column % (sideLength - 1) == 0)
                visibleTotal++;
            else if (inputString[row][column] > visibleTreesHorizontal[row][column - 1] ||
                     inputString[row][column] > visibleTreesHorizontal[row][column + 1] ||
                     inputString[row][column] > visibleTreesVertical[row + 1][column] ||
                     inputString[row][column] > visibleTreesVertical[row - 1][column])
                visibleTotal++;
        }
    }

    printf("Total = %d\n", visibleTotal);
    
    return 0;
}
