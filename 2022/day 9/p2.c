#include <stdio.h>
#include <stdlib.h>


#define TOTAL_NODES 10


typedef struct knot {
    int x, y;
    int offset[2];
} Node;


int main() {
    int visited = 1; // starting square is 1
    char direction;
    int vector[2];
    int repeat;
    int** grid = malloc(1000*sizeof(int*));
    for (int i = 0; i < 1000; i++)
        grid[i] = malloc(1000*sizeof(int*));

    Node nodes[TOTAL_NODES]; // TOTAL_NODES nodes, from head to tail
    for (int i = 0; i < TOTAL_NODES; i++) {
        nodes[i].x = 499;
        nodes[i].y = 499;
        nodes[i].offset[0] = 0;
        nodes[i].offset[1] = 0;
    }
    grid[nodes[0].x][nodes[0].y] = 1;
    
    FILE* inputs = fopen("inputs.txt", "r");

    for (int line = 0; line < 2000; line++) {
        fscanf(inputs, " %c %d", &direction, &repeat);

        printf("LINE %d: direction = %c, repeat = %d\n", line, direction, repeat);

        switch (direction) { // inefficient. It makes it easier though.
            case 'U':
                vector[0] = 0;
                vector[1] = 1;
                break;
            case 'D':
                vector[0] = 0;
                vector[1] = -1;
                break;
            case 'R':
                vector[0] = 1;
                vector[1] = 0;
                break;
            case 'L':
                vector[0] = -1;
                vector[1] = 0;
                break;
            default:
                break;
        }
        
        for (int iteration = 0; iteration < repeat; iteration++) {

            nodes[0].x += vector[0];
            nodes[0].y += vector[1];
            nodes[0].offset[0] += vector[0];
            nodes[0].offset[1] += vector[1];

            for (int node = 1; node < TOTAL_NODES; node++) {

                if (nodes[node - 1].offset[0] < -1 || nodes[node - 1].offset[0] > 1) {

                    nodes[node - 1].offset[0] >>= 1; // since it's either -2 or 2, this brings it back to -1 or 1
                    nodes[node].x += nodes[node - 1].offset[0];
                    nodes[node].offset[0] += nodes[node - 1].offset[0];

                    int bitShift = nodes[node - 1].offset[1] - nodes[node - 1].offset[1]/2; // -2, -1, 0, 1, 2 will map to -1, -1, 0, 1, 1
                    nodes[node].y += bitShift;
                    nodes[node].offset[1] += bitShift;
                    nodes[node - 1].offset[1] -= bitShift;

                } else if (nodes[node - 1].offset[1] < -1 || nodes[node - 1].offset[1] > 1) {

                    nodes[node - 1].offset[1] >>= 1; // since it's either -2 or 2, this brings it back to -1 or 1
                    nodes[node].y += nodes[node - 1].offset[1];
                    nodes[node].offset[1] += nodes[node - 1].offset[1];

                    int bitShift = nodes[node - 1].offset[0] - nodes[node - 1].offset[0]/2;
                    nodes[node].x += bitShift;
                    nodes[node].offset[0] += bitShift;
                    nodes[node - 1].offset[0] -= bitShift;

                }
            }

            if (grid[nodes[TOTAL_NODES - 1].x][nodes[TOTAL_NODES - 1].y] == 0) {
                visited++;
                grid[nodes[TOTAL_NODES - 1].x][nodes[TOTAL_NODES - 1].y] = 1;
            }
        }
    }

    printf("visited = %d\n", visited);

    return 0;
}
