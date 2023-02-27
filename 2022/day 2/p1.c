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

        yourMove = fgetc(moves) - 23; // X -> A; Y-> B; Z-> C
        printf("your move = %c; ", yourMove);

        result = yourMove - opponentMove;
        if (result == -2) // rock (1) beats paper (3)
            result = 1;
        if (result == 2) // paper gets beaten by rock
            result = -1;
        printf("result = %d. ", result);

        result = (result + 1)*3 + MOVESCORE(yourMove); // 0 for loss, 3 for draw, 6 for win
        totalScore += result;
        printf("Score added = %d; total score is now %d.\n", result, totalScore);

        fgetc(moves); // newline at the end
    }
    fclose(moves);

    printf("TOTAL SCORE: %d.\n", totalScore);

    return 0;
}
