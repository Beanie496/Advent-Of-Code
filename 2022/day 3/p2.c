#include <stdio.h>


int main() {
    FILE* inputs = fopen("inputs.txt", "r");
    char inputString[200];
    int sum = 0;
    int size;
    int buckets[128] = { 0 }; // This is inefficient. I don't care.
    int j;

    for (int i = 0; i < 100; i++) {
        for (j = 0; j < 3; j++) {
            fscanf(inputs, "%s", inputString);

            for (size = 0; inputString[size] != '\0'; size++)
                if (buckets[inputString[size]] == j)
                    buckets[inputString[size]]++;
        }
            
        for (j = 0; j < 128; j++) {
            if (buckets[j] == 3) {
                if (j <= 'Z')
                    sum += j - 'A' + 1 + 26;
                else
                    sum += j - 'a' + 1;
            }
            buckets[j] = 0;
        }
    }
    fclose(inputs);
    printf("Sum = %d\n", sum);

    return 0;
}
