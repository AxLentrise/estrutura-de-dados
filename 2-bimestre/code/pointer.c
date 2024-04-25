#include <stdio.h>

int main(int agrc, char **argv) {

    int *p;

    int value = 100;
    int sum;

    p = &value;
    sum = *p*2;

    printf_s("sum: %d", sum);

    getchar();

    return 0;
}