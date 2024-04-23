#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#define MAX 256

int main(int argc[], char **argv) {

    FILE *filePointer;
    char line[MAX];

    if(filePointer = fopen("", "r") == NULL) {
        printf("Error opening file.");
        exit(0);
    }
    
    while(fgets(line, MAX, filePointer) != NULL) {
        printf("%s", line);
    }

    fclose(filePointer);
    return 0;
}