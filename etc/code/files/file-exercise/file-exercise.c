#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main(int argc, char** argv) {

    FILE *fptr;
    char ch;
    char lastChar;
    int charCount = 0;
    int lineCount = 0;
    int wordCount = 0;
    
    if((fptr = fopen(argv[1], "r")) == NULL) {
        printf("Error opening file.");
        exit(0);
    }

    while((ch = getc(fptr)) != EOF) {
        printf("%c", ch);
        if(ch != '\n') charCount++;
        //  Se o char for igual a um espaço, mas o lastChar diferente de \n e outro espaço 
        if((ch == ' ') && !((lastChar == '\n') || (lastChar == ' ')) ||
        //  Ou o char for igual a \n, mas o lastChar diferente de outro \n e espaço
           (ch == '\n' && !((lastChar == '\n') || (lastChar == ' ')))
        ) wordCount++; // incrementa o wordCount
        if(ch == '\n') lineCount++;

        lastChar = ch;
    }

    if(lastChar != '\n') lineCount++;
    if(lastChar != EOF) wordCount++;

    printf("\n\nN of char: %d", charCount);
    printf("\nN of word: %d", wordCount);
    printf("\nN of line: %d", lineCount);

    fclose(fptr);
    return 0;
}