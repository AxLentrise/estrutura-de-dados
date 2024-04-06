#include <stdio.h>
#include <conio.h>

int main(int argc[], char **argv){

    FILE *filePointer;
    char ch;
                //     path  w = write
                //     path  r = read
                //     path  a = append
                //     path  b = binary
    filePointer = fopen("out-file.txt", "w");
                     //     27 = ESC
    while ((ch=getche()) != 27) {
        if(ch == 13){//     13 = Enter
            putc('\n', filePointer);
        } else {
            putc(ch, filePointer);
        }
    }
    
    fclose(filePointer);
    return 0;
}