#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#define MAX 100

int main (int argc[], char **argv) {

    FILE *filePointer;
    char string[MAX];

    if((filePointer = fopen("file-writen.txt", "r")) == NULL) {
        printf("Error opening the file.\n");
        exit(0);
    }

    while(strlen(fgets(string, MAX, stdin)) > 0) {
        fputs(string, filePointer);
        fputs("\n", filePointer);
    }

    fclose(filePointer);
    return 0;
}