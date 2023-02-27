#include <stdio.h>

#define MOVESCORE(move) move - 'A' + 1


int main() {
    FILE* moves = fopen("inputs.txt", "r");

    char opponentMove;
    char yourMove;
    int result;
    int totalScore = 0;

    while (1) {
        opponentMove = fgetc(moves);
        if (opponentMove == '\n') // There's an empty line at the bottom of the file
            break;
        printf("opponent's move = %c, ", opponentMove);
        
        fgetc(moves); // skips over the space;

        result = fgetc(moves) - 'Y'; // -1, 0 or 1 for LDW
        printf("needed result = %d; ", result);

        yourMove = opponentMove + result;
        if (yourMove == 'C' + 1)
            yourMove = 'A';
        if (yourMove == 'A' - 1)
            yourMove = 'C';

        result = (result + 1)*3 + MOVESCORE(yourMove); // 0 for loss, 3 for draw, 6 for win
        totalScore += result;
        printf("Score added = %d; total score is now %d.\n", result, totalScore);

        fgetc(moves); // newline at the end
    }
    fclose(moves);

    printf("TOTAL SCORE: %d.\n", totalScore);

    return 0;
}
