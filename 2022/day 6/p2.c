#include <stdio.h>


int main() {
    FILE* inputs = fopen("inputs.txt", "r");
    char currentChar;
    int buckets[128] = { 0 };
    char l4Chars[14];
    int i = 14;
    int isUnique = 0;

    for (int j = 0; j < 13; j++) {
        l4Chars[j] = fgetc(inputs);
        buckets[l4Chars[j]]++;
    }
    while ((currentChar = fgetc(inputs)) != EOF) {
        l4Chars[13] = currentChar;
        buckets[l4Chars[13]]++;
        isUnique = 1;
        for (int j = 1; j < 128; j++)
            if(buckets[j] > 1)
                isUnique = 0;
        if (isUnique == 1) {
            printf("%d\n", i);
            return 0;
        }
        i++;
        buckets[l4Chars[0]]--;
        for (int j = 0; j < 13; j++)
            l4Chars[j] = l4Chars[j + 1];
    }
}
