#include <stdio.h>
#include <stdlib.h>

/*
    argc = "arguments counter"
    argv = "arguments vector"

    argv[0] = program name
    every other argv can be attributed a call

*/

int main(int argc, char **argv) {

    FILE *fptr;
    char ch;
    int charCount;
    int vogalCount;

    if(argc != 2) {
        printf("Enter only one argument (file path).");
        exit(0);
    }

    if((fptr = fopen(argv[1], "r")) == NULL) {
        printf("Error opening file!");
        exit(0);
    }

    while((ch = getc(fptr)) != EOF) {
        printf("%c", ch);
        if((ch == 'a') || (ch == 'e') || (ch == 'i') || (ch == 'o') || (ch == 'u')) vogalCount++;
        if((ch == 'A') || (ch == 'E') || (ch == 'I') || (ch == 'O') || (ch == 'U')) vogalCount++;
        if(ch != '\n') charCount++;
    }

    double vogalPercent = vogalCount*100/charCount;

    printf("Number of characters: %d\n", charCount);
    printf("Number of vogals: %d\n", vogalCount);
    printf("Percentange of vogals: %.2f\%\n", vogalPercent);

    return 0;
}