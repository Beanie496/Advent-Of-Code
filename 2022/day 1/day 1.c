#include <stdio.h>
#include <unistd.h>


int main()
{
    int maxes[3] = { 0 };
    int runningTotal = 0;
    int currentNum;

    FILE* caloriesFile = fopen("calories.txt", "r");

    do {
        fscanf(caloriesFile, "%d", &currentNum);
        runningTotal += currentNum;
        printf("Current num = %d; running total = %d\n", currentNum, runningTotal);
        fgetc(caloriesFile);

        if (fgetc(caloriesFile)  == '\n') {
            if (runningTotal > maxes[0]) {
                maxes[2] = maxes[1];
                maxes[1] = maxes[0];
                maxes[0] = runningTotal;
                printf("NEW MAXES = %d, %d, %d\n", maxes[0], maxes[1], maxes[2]);
            } else if (runningTotal > maxes[1]) {
                maxes[2] = maxes[1];
                maxes[1] = runningTotal;
                printf("NEW MAXES = %d, %d, %d\n", maxes[0], maxes[1], maxes[2]);
            } else if (runningTotal > maxes[2]) {
                maxes[2] = runningTotal;
                printf("NEW MAXES = %d, %d, %d\n", maxes[0], maxes[1], maxes[2]);
            }
            runningTotal = 0;
        }

        if (fgetc(caloriesFile) == EOF)
            break;

        fseek(caloriesFile, -2, SEEK_CUR);
    } while (1);
    fclose(caloriesFile);
    
    printf("MAXES = %d, %d, %d\n", maxes[0], maxes[1], maxes[2]);
    printf("Total = %d\n", maxes[0] + maxes[1] + maxes[2]);

    return 0;
}
