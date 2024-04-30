#include <stdio.h>

int main() {

    int vect[] = {1, 2, 3, 4, 5}; 
    int *ptr = vect;

    for(int i = 0; i < 5; i++) {
        printf_s("%d [%p]\n", *(ptr+i), ptr+i);
    }

    getchar();

    return -1;
}