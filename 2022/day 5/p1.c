#include <stdio.h>


int main()
{
    char stacks[9][100] = { '\0' }; // We're writing code that takes less time to write, not good code.
    char* stackPtrs[9];
    char finalWord[9];
    char currentChar;

    int moves;
    int src;
    int dest;
    int k;

    FILE* inputs = fopen("inputs.txt", "r");
    
    for (int i = 8; i >= 0; i--) {
        for (int j = 0; j < 9; j++) {
            stacks[j][i] = fgetc(inputs);
            printf("stacks[%d][%d] = \"%c\"\n", j, i, stacks[j][i]);
            if (stacks[j][i] == ' ') {
                stacks[j][i] = '\0';
                stackPtrs[j] = &stacks[j][i - 1];
            }
            fgetc(inputs);
        }
    }

    for (int i = 0; i < 502; i++) {
        fscanf(inputs, "%d %d %d", &moves, &src, &dest);
        printf("moves = %d, src = %d, dest = %d\n", moves, src, dest);
        for (int j = 0; j < moves; j++) {
            printf("src = %c, dest = %c\n", *stackPtrs[src - 1], *stackPtrs[dest - 1]);
            stackPtrs[dest - 1]++;
            *stackPtrs[dest - 1] = *stackPtrs[src - 1];
            *stackPtrs[src - 1] = '\0';
            stackPtrs[src - 1]--;
        }
    }

    for (int i = 0; i < 9; i++)
        printf("%c", *stackPtrs[i]);
    printf("\n");

    return 0;
}
