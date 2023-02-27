#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node {
    char name[20];
    int size;
    int type; // 1 for directory; 0 otherwise
    int fileNum; // If it's a directory, this is how many files it contains
    struct Node** dirPtrs; // If it's a directory, this will contain pointers to all the structs it contains
} File;


int totalSize = 0;


void makeTree(FILE** inputs, File* parentNode) {
    char type[50], name[50];
    File* dirs[20];
    int dirSize = 0;
    int i = 0;
    int dirsIdx = 0;
    
    do { // Iterates over each member in directory
        if (fscanf(*inputs, "%s %s", type, name) == EOF)
            break;
        printf("Type, name = \"%s\", \"%s\"\n", type, name);

        parentNode->fileNum++;
        // makes space for one more file. I know this
        // causes a memory leak, but I only need to free
        // it at the end - but the program finishes there
        // anyway, so the operating system will free it for me.
        parentNode->dirPtrs = realloc(parentNode->dirPtrs, parentNode->fileNum*sizeof(File*)); 
        parentNode->dirPtrs[i] = malloc(sizeof(File)); // parentNode->dirPtrs[i] is now a pointer to the file with index i
        strcpy(parentNode->dirPtrs[i]->name, name);

        if  (!strcmp(type, "cd")) // reached the end of the files list (it's redundant, but I don't want to write an infinite loop)
            break;
        // depending on whether it's a directory or regular file, fill the struct appropriately
        if  (!strcmp(type, "dir")) {
            dirs[dirsIdx] = parentNode->dirPtrs[i];
            parentNode->dirPtrs[i]->type = 1;
            parentNode->dirPtrs[i]->fileNum = 0;
            parentNode->dirPtrs[i]->dirPtrs = malloc(0);
            dirsIdx++;
        } else {
            parentNode->dirPtrs[i]->type = 0;
            parentNode->dirPtrs[i]->size = atoi(type);
            dirSize += parentNode->dirPtrs[i]->size;
        }

        i++;
    } while (strcmp(type, "cd"));
    parentNode->fileNum = i;

    for (i = 0; i < dirsIdx; i++) {
        printf("Recursing into dir %s\n", dirs[i]->name);
        makeTree(inputs, dirs[i]);
        fscanf(*inputs, "%*s %*s"); // ignores the 'cd ..'
    }
}


int search(File* parentNode) {
    int dirSize = 0;
    for (int i = 0; i < parentNode->fileNum; i++) { // Iterates through each file
        if (parentNode->dirPtrs[i]->type == 1)
            // If it's a directory, get the size recursively
            dirSize += search(parentNode->dirPtrs[i]);
        else
            // Otherwise, get the size normally
            dirSize += parentNode->dirPtrs[i]->size;
    }
    if (dirSize <= 100000)
        totalSize += dirSize;

    return dirSize;
}


int main() {
    FILE* inputs = fopen("inputs.txt", "r");
    fscanf(inputs, "%*s %*s");

    File root;
    root.type = 1;
    root.fileNum = 0;
    root.dirPtrs = malloc(0);

    makeTree(&inputs, &root);
    fclose(inputs);

    search(&root);

    printf("total size = %d\n", totalSize);
    
    return 0;
}
