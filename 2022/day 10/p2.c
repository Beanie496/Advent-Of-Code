#include <stdio.h>
#include <string.h>


int main() {
    FILE* inputs = fopen("inputs.txt", "r");
    char instruction[5];
    int value;
    char pixels[240];
    int cycle = 0;
    int X = 1;

    for (int line = 0; line < 144; line++) {
        fscanf(inputs, "%s", instruction);

        if (!strcmp(instruction, "noop")) {

            if (cycle % 40 >= X - 1 && cycle % 40 <= X + 1)
                pixels[cycle] = '#';
            else
                pixels[cycle] = '.';

            cycle++;

        } else {
            fscanf(inputs, "%d", &value);

            if (cycle % 40 >= X - 1 && cycle % 40 <= X + 1)
                pixels[cycle] = '#';
            else
                pixels[cycle] = '.';
            cycle++;

            if (cycle % 40 >= X - 1 && cycle % 40 <= X + 1)
                pixels[cycle] = '#';
            else
                pixels[cycle] = '.';
            cycle++;

            X += value;
        }
    }
    
    for (int i = 0; i < 6; i++)
        printf("%.40s\n", pixels + i*40);
    
    return 0;

}
