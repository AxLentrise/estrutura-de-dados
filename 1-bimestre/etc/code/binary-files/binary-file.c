#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define BUFFER 255
#define PATH "book.dat"

#define RED "\033[31m"
#define RESET "\033[0m"

char buffered_str[BUFFER];

struct regBook {
    char name[BUFFER];
    int code;
    float price;
};

void addBook() {
    struct regBook book;
    char string[BUFFER];
    FILE *fptr;

    if((fptr = fopen(PATH, "ab")) == NULL) {
        printf("Error opening file.");
        return;
    }

    system("cls");
    printf("Enter book ID: ");
    getchar();
    fgets(buffered_str, BUFFER, stdin);
    // if(isdigit(buffered_str) == 0) 
    {
        sscanf(buffered_str, "%d", &book.code);
    }

    printf("Enter book name: ");
    // getchar();
    fgets(book.name, BUFFER, stdin);
    book.name[strlen(book.name)-1] = '\0';

    printf("Enter book price: ");
    // getchar();
    fgets(buffered_str, BUFFER, stdin);
    // if(isdigit(buffered_str) == 0) 
    {
        sscanf(buffered_str, "%f", &book.price);
    }

    fwrite(&book, sizeof(book), 1, fptr);
    fclose(fptr);
}

void listBooks() {
    struct regBook book;
    FILE *fptr;

    if((fptr = fopen(PATH, "rb")) == NULL) {
        printf("Error opening file.");
        return;
    }

    system("cls");
    printf("\n\033[31mID:\033[0m    \033[32mTitle:\033[0m               \033[33mPrice:\n\033[0m");
    while((fread(&book, sizeof(book), 1, fptr)) == 1) {
       printf("\033[31m%-6i\033[0m \033[32m%-20s\033[0m \033[33m%5.2f\n", book.code, book.name, book.price);
    }
    printf("\n");
    fclose(fptr);
}

void consultById() {
    struct regBook book;
    int id;
    int found = 0;
    FILE *fptr;

    system("cls");
    printf("Enter the book id to search: ");
    fflush(stdin);
    scanf("%d", &id);

    if((fptr = fopen(PATH, "rb")) == NULL) {
        printf("Error opening file.");
        return;
    }

    while((!found)&&((fread(&book, sizeof(book), 1, fptr)) == 1)) {
        if(book.code == id) {
            printf("Book found:\n");
            printf("\n\033[31mID:\033[0m    \033[32mTitle:\033[0m               \033[33mPrice:\n\033[0m");
            printf("\033[31m%-6i\033[0m \033[32m%-20s\033[0m \033[33m%5.2f\n\n033[0m", book.code, book.name, book.price);
            found++;
        }
    }

    if(!found) printf("Book not found.\n");
    fclose(fptr);
}

void consultByKeyword() {
    struct regBook book;
    char word[BUFFER];
    int found = 0;
    FILE *fptr;

    system("cls");
    printf("Enter the keyword to search: ");
    fflush(stdin);
    fgets(word, BUFFER, stdin);

    if((fptr = fopen(PATH, "rb")) == NULL) {
        printf("Error opening file.");
        return;
    }

    while((!found)&&((fread(&book, sizeof(book), 1, fptr)) == 1)) {
        if((strstr(book.name, word)) != NULL) {
            printf("Book found:\n");
            printf("\n\033[31mID:    \033[32mTitle:               \033[33mPrice:\n\033m[0m");
            printf("\033[31m%-6i \033[32m%-20s \033[33m%5.2f\n\n033[0m", book.code, book.name, book.price);
            found++;
        }
    }

    if(!found) printf("Book not found.\n");
    fclose(fptr);
}


void consultByName() {
    struct regBook book;
    char name[BUFFER];
    int found = 0;
    FILE *fptr;

    system("cls");
    printf("Enter the book name to search: ");
    fflush(stdin);
    fgets(name, BUFFER, stdin);

    if((fptr = fopen(PATH, "rb")) == NULL) {
        printf("Error opening file.");
        return;
    }

    while((!found)&&((fread(&book, sizeof(book), 1, fptr)) == 1)) {
        if(!strcmp(book.name, name)) {
            printf("Book found:\n");
            printf("\n\033[31mID:    \033[32mTitle:               \033[33mPrice:\n\033m[0m");
            printf("\033[31m%-6i \033[32m%-20s \033[33m%5.2f\n\n033[0m", book.code, book.name, book.price);
            found++;
        }
    }

    if(!found) printf("Book not found.\n");
    fclose(fptr);
}

int main(int argc, char **argv) {
    fflush(stdin);
    int code = -1;
    int short_buffer = 2;

    while(code != 0) {
        printf("\n\33[36m----- Library -----\33[0m\n\n");
        printf("\033[33m[1]\033[0m - Add book;\n");
        printf("\033[33m[2]\033[0m - List all books;\n");
        printf("\033[33m[3]\033[0m - Consult book by Id;\n");
        printf("\033[33m[4]\033[0m - Consult book by name;\n");
        printf("\033[33m[5]\033[0m - Consult book by keyword;\n");
        printf("\033[31m[0]\033[0m - To exit.\n\n");
        printf("Option: ");
        fgets(buffered_str, short_buffer, stdin);
        // if(isdigit(buffered_str) == 0) 
        {
            sscanf(buffered_str, "%d", &code);
        }

        system("cls");
        switch(code) {
            case 1:
                addBook(); break;
            case 2:
                listBooks(); break;
            case 3:
                consultById(); break;
            case 4:
                consultByName(); break;
            case 5:
                consultByKeyword(); break;
            case 0: break;
            default:
                printf("\n\n\033[31mEnter a valid code!\033[0m\n\n"); break;
        }
    }

    system("cls");
    printf("Application closed.");
    return 0;
}