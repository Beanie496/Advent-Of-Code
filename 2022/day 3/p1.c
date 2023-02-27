#include <stdio.h>


int main() {
    FILE* inputs = fopen("inputs.txt", "r");
    char inputString[200];
    int sum = 0;
    int size;
    int buckets[128]; // This is inefficient. I don't care.
    int j;

    for (int i = 0; i < 300; i++) {
        fscanf(inputs, "%s", inputString);
        printf("%s\n", inputString);

        for (size = 0; inputString[size] != '\0'; size++);
        printf("size = %d\n", size);

        for (j = 0; j < size/2; j++)
            buckets[inputString[j]] = 1;
        printf("j = %d\n", j);
        
        for (; inputString[j] != '\0'; j++) {
            if (buckets[inputString[j]] == 1) {
                buckets[inputString[j]] = 0;
                printf("Found a match (line %d); %c\n", i, inputString[j]);
                if (inputString[j] <= 'Z')
                    sum += inputString[j] - 'A' + 1 + 26;
                else
                    sum += inputString[j] - 'a' + 1;
            }
        }

        for (j = 0; j < 128; j++)
            buckets[j] = 0;
    }
    fclose(inputs);
    printf("Sum = %d\n", sum);

    return 0;
}
