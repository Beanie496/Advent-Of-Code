#include <stdio.h>
#include <string.h>


int main() {
    FILE* inputs = fopen("inputs.txt", "r");
    char instruction[5];
    int value;
    int totalSigStrength = 0;
    int cycle = 0;
    int X = 1;

    for (int line = 0; line < 144; line++) {
        fscanf(inputs, "%s", instruction);
        printf("%s ", instruction);

        if (!strcmp(instruction, "noop")) {
            printf("\n");
            cycle++;
            if ((cycle + 20) % 40 == 0) {
                totalSigStrength += X*cycle;
                printf("20th cycle. %d\n", totalSigStrength);
            }
        } else {
            fscanf(inputs, "%d", &value);
            printf("Value = %d\n", value);
            if ((cycle + 20) % 40 == 38 || (cycle + 20) % 40 == 39) {
                totalSigStrength += X*(cycle + 40 - ((cycle + 20) % 40));
                printf("20th cycle. %d\n", totalSigStrength);
            }
            X += value;
            cycle += 2;
        }
    }

    printf("%d\n", totalSigStrength);
    
    return 0;

}
