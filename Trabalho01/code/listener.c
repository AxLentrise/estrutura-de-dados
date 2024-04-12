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
    
    int num = 0;
    while(1) {
        Sleep(2);
        if(GetAsyncKeyState(37) == -32767) if(num > 1) num--;  // 0x26
        // if(GetAsyncKeyState(38) == -32767) if(num > 1) num--;  // 0x27
        // if(GetAsyncKeyState(39) == -32767) if(num > 1) num--;  
        if(GetAsyncKeyState(40) == -32767) if(num < 50) num++;

        printf_s("%d\n", num);
    }

    return 0;
}