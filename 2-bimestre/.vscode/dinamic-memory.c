#include <stdio.h>
#include <stdlib.h>

typedef struct nodes {
    int value;
    struct nodes *next;
} node;

int main() {

    node *p1, *p2;

    if(!(p1 = (node*) malloc(sizeof(node))) | !(p2 = (node*) malloc(sizeof(node)))) {
        printf_s("Error allocation memory\n");
        exit(450);
    }

    p1->value = 69; p1->next = p2;
    p2->value = 20; p2->next = NULL;

    printf_s("P1[%p] = [%d] (%p)\n", p1, p1->value, p1->next);
    printf_s("P2[%p] = [%d] (%p)\n", p2, p2->value, p2->next);

    free(p1); free(p2);
    getchar();
    return -1;
}