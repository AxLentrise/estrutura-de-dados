#include <stdio.h>
#include <stdlib.h>

typedef struct person {
    char name[25];
    int age;
} person;

int main() {

    char buffer = malloc(sizeof(person));
    char stdin_buffer[4] = {0};

    printf_s("Enter the person name: ");
    // fgets(p1.name, sizeof(p1.name), stdin);
    // p1.name[strlen(p1.name)-1] = '\0';

    printf_s("Enter the person age: ");
    // fgets(buffer, sizeof(buffer), stdin);
    // sscanf_s(buffer, "%d", &p1.age);

    // printf_s("[NORMAL]  = %s is %d years old\n", p1.name, p1.age);
    // printf_s("[POINTER] = %s is %d years old\n", ptr->name, ptr->age);



    getchar();
    free(buffer);
    return -1;
}