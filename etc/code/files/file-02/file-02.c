#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

int main(int argc[], char **argv) {

    FILE *filePointer;
    char ch;
        // fopen return NULL if the file cant be opened
    if ((filePointer = fopen("file.txt", "r")) == NULL){
        printf("Error opening file.");
        exit(0);
    }

        // EOF = End Of Files
    while((ch = getc(filePointer)) != EOF) {
        printf("%c", ch);
    }

        // Even if the file is not opened, close it
    fclose(filePointer);
    return 0;
}