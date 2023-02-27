#include <stdio.h>


int main() {
    FILE* fptr = fopen("inputs.txt", "r");
    int encPairs = 0;
    int n1range[2];
    int n2range[2];

    for (int i = 0; i < 1000; i++) {
        fscanf(fptr, "%d %d %d %d", &n1range[0], &n1range[1], &n2range[0], &n2range[1]);
        if (n1range[0] <= n2range[0] && n1range[1] >= n2range[1])
            encPairs++;
        else if (n1range[0] >= n2range[0] && n1range[1] <= n2range[1])
            encPairs++;
    }

    printf("pairs = %d\n", encPairs);

    return 0;
}
