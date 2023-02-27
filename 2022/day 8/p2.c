#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MIN(a,b) (a < b ? a : b)
#define MAX(a,b) (a > b ? a : b)


int main() {
    char** inputString;
    int sideLength = 99;
    FILE* inputs = fopen("inputs.txt", "r");
    int highestScore = 0;

    inputString = malloc(sideLength*sizeof(char*)); // 99 lines

    for (int i = 0; i < sideLength; i++) { // square, 99 in side length
        inputString[i] = malloc(sideLength*sizeof(char));
        fscanf(inputs, "%s", inputString[i]);
    }

    for (int row = 1; row < sideLength - 1; row++) {
        for (int column = 1; column < sideLength - 1; column++) { // it's obviously not a border tree
            int currentScore = 1;
            int x, y;
            x = column;
            y = row;
            do { y--; } while (y > 0 && inputString[y][x] < inputString[row][column]);
            currentScore *= row - y;
            printf("%c, score up = %d\n", inputString[row][column], row - y);
            y = row;
            do { y++; } while (y < sideLength - 1 && inputString[y][x] < inputString[row][column]);
            currentScore *= y - row;
            printf("score down = %d\n", y - row);
            y = row;
            x = column;
            do { x--; } while (x > 0 && inputString[y][x] < inputString[row][column]);
            currentScore *= column - x;
            printf("score left = %d\n", column - x);
            x = column;
            do { x++; } while (x < sideLength - 1 && inputString[y][x] < inputString[row][column]);
            printf("score right = %d\n", x - column);
            currentScore *= x - column;
            printf("\n");

            if (currentScore > highestScore)
                highestScore = currentScore;
        }
    }

    printf("Highest score = %d\n", highestScore);

    return 0;
}
