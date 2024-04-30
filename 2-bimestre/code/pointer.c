/*
    int *p, v;
    
    Pointers can receive NULL to indicate they dont point to anything:
        RIGHT    p = NULL;

    Pointers cant attribute NULL to some variable location:
        WRONG   *p = NULL;

    Pointers can receive memory adress of a variable of the same type:
        RIGHT    p = &v;

    The memory adress a memory points to cannot receive another memory adress:
        WRONG    *p = &v;

    A pointer pointing to a memory adress can attribute another value of the same type:
        RIGHT    *p = v;
*/

#include <stdio.h>

int main() {

    int *p, v;

    // p = NULL;

    // *p = NULL;

    // p = &v;

    // *p = &v;

    // *p = v;

    return 0;
}