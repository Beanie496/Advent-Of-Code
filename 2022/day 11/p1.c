#include <stdio.h>


#define MONKS 8
#define ROUNDS 20


typedef struct monkeyTemplate {
    long long items[100];
    int itemsNum;
    int itemsInspected;
    char op;
    int opBy;
    int divBy;
    int ifTrue;
    int ifFalse;
} Monkey;


int main() {
    FILE* inputs = fopen("inputs.txt", "r");
    int i;
    Monkey monks[MONKS]; 

    // This stores in the relevant values to each of the monkeys
    for (int monk = 0; monk < MONKS; monk++) {
        fscanf(inputs, "%*s %*s %*s %*s %lld", &monks[monk].items[0]);

        i = 0;
        // stores in all the worry levels
        do {
            i++;
            fscanf(inputs, "%*c %lld", &monks[monk].items[i]);
        } while (monks[monk].items[i] < 100 && monks[monk].items[i] > 10);
        monks[monk].itemsNum = i;

        fscanf(inputs, "%*s %*s %*s %*s %c %d", &monks[monk].op, &monks[monk].opBy);
        fscanf(inputs, "%*s %*s %*s %d", &monks[monk].divBy);
        fscanf(inputs, "%*s %*s %*s %*s %*s %d", &monks[monk].ifTrue);
        fscanf(inputs, "%*s %*s %*s %*s %*s %d", &monks[monk].ifFalse);
        monks[monk].itemsInspected = 0;
    }

    for (int round = 0; round < ROUNDS; round++) {
        printf("ROUND %d:\n\n", round);

        for (int monk = 0; monk < MONKS; monk++) {
            printf("Monkey %d\n", monk);

            for (int item = 0; item < monks[monk].itemsNum; item++) {

                printf("Starting item: %lld\n", monks[monk].items[item]);

                switch (monks[monk].op) {
                    case '*':
                        printf("%lld * %d = ", monks[monk].items[item], monks[monk].opBy);
                        monks[monk].items[item] *= monks[monk].opBy;
                        printf("%lld\n", monks[monk].items[item]);
                        break;
                    case '+':
                        printf("%lld + %d = ", monks[monk].items[item], monks[monk].opBy);
                        monks[monk].items[item] += monks[monk].opBy;
                        printf("%lld\n", monks[monk].items[item]);
                        break;
                    case '^':
                        printf("%lld^2 = ", monks[monk].items[item]);
                        monks[monk].items[item] *= monks[monk].items[item];
                        printf("%lld\n", monks[monk].items[item]);
                        break;
                    default:
                        break;
                }

                printf("%lld/3 = ", monks[monk].items[item]);
                monks[monk].items[item] /= 3;
                printf("%lld\n", monks[monk].items[item]);

                if (monks[monk].items[item] % monks[monk].divBy == 0) {

                    printf("%lld is divisible by %d. ", monks[monk].items[item], monks[monk].divBy);

                    int ifTrueMonk = monks[monk].ifTrue;
                    printf("Thrown to monkey %d\n", ifTrueMonk);
                    monks[ifTrueMonk].items[monks[ifTrueMonk].itemsNum] = monks[monk].items[item];
                    monks[ifTrueMonk].itemsNum++;

                } else {

                    printf("%lld is not divisible by %d. ", monks[monk].items[item], monks[monk].divBy);

                    int ifFalseMonk = monks[monk].ifFalse;

                    printf("Thrown to monkey %d\n", ifFalseMonk);
                    monks[ifFalseMonk].items[monks[ifFalseMonk].itemsNum] = monks[monk].items[item];
                    monks[ifFalseMonk].itemsNum++;
                }

                monks[monk].itemsInspected++;
            }

            monks[monk].itemsNum = 0; // it's gone through each of the items so this must be 0.
            printf("Items inspected = %d\n", monks[monk].itemsInspected);
        }

        // prints out all the worry levels for each monkey
        for (int monk = 0; monk < MONKS; monk++) {
            printf("monkey %d ", monk);
            for (int item = 0; item < monks[monk].itemsNum; item++)
                printf("%lld ", monks[monk].items[item]);
            printf("\n");
        }
    }

    // prints the final number of items inspected for each monkey (i multiply the two highest ones by hand)
    for (int monk = 0; monk < MONKS; monk++)
        printf("\"%d\"\n", monks[monk].itemsInspected);

    return 0;
}
