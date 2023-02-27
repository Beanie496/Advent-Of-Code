#include <stdio.h>


int main() {
    int visited = 1; // starting square is 1
    char direction;
    int repeat;
    int offset[2] = { 0 };
    int grid[1000][1000] = { 0 }; // is this inefficient? yes. would i use an array of chars and malloc() if i needed efficiency? also yes.
    int x = 499, y = 499;
    grid[x][y] = 1;
    
    FILE* inputs = fopen("inputs.txt", "r");

    for (int line = 0; line < 2000; line++) {
        fscanf(inputs, " %c %d", &direction, &repeat);
        printf("%c, %d; line = %d\n", direction, repeat, line);

        for (int i = 0; i < repeat; i++) {
            switch (direction) { // inefficient. It makes it easier though.
                case 'R':
                    offset[0]++;
                    break;
                case 'D':
                    offset[1]--;
                    break;
                case 'L':
                    offset[0]--;
                    break;
                case 'U':
                    offset[1]++;
                    break;
                default:
                    break;
            }

            if (offset[0] < -1 || offset[0] > 1) {
                offset[0] >>= 1; // since it's either -2 or 2, this brings it back to -1 or 1
                x += offset[0];
                y += offset[1];
                offset[1] = 0; // it moves diagonally, making this 0
            } else if (offset[1] < -1 || offset[1] > 1) {
                offset[1] >>= 1;
                y += offset[1];
                x += offset[0];
                offset[0] = 0;
            }
            if (grid[x][y] == 0) {
                visited++;
                grid[x][y] = 1;
            }
        }
    }

    printf("visited = %d\n", visited);

    return 0;
}
