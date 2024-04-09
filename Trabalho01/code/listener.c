#include <windows.h>
#include <stdio.h>

int main()
{
    int result,teclas;

    // while(1) {
    //     for(teclas = 0; teclas <= 255; teclas++) {
    //         Sleep(300);

    //         result = GetAsyncKeyState(teclas);

    //         if(result == -32767) {
    //             printf_s("true  = 0x%X\n", teclas);
    //         } else {
    //             printf_s("false = 0x%X\n", teclas);
    //         }

    //         // 0x26 = UP
    //         // 0x28 = DOWN
           
    //     }
    // }

    while(1) {
        Sleep(2);
        if(GetAsyncKeyState(38) == -32767) printf_s("UP   PRESSED\n");
        if(GetAsyncKeyState(40) == -32767) printf_s("DOWN PRESSED\n");
    }

    return 0;
}