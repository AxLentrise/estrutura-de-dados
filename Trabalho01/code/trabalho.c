/*
    @author:     Diogo Tiago Bertoldo
    @compiler:   GCC 13.1.0
    @so:         Windows 11 (04/2024)

    Trabalho de Estrutura de Dados, desenvolvido de forma independente
    com base n aplicaçao desenvolvida em sala de aula, aqui elevada um
    pouco a complexidade para fazer algo melhor de se utilizar

*/

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#define MAX 256                 // Config
#define BOOKS "books.dat"       // Config
#define CLIENTS "clients.dat"   // Config
#define SELLINGS "sellings.dat" // Config
#define READ "rb"               // Config
#define WRITE "ab"              // Config

#define BACKSPACE 8    // Códigos ASCII para o keyListener
#define ESC       27   // Códigos ASCII para o keyListener
#define ENTER     13   // Códigos ASCII para o keyListener
#define SPACE     32   // Códigos ASCII para o keyListener
#define ZERO      48   // Códigos ASCII para o keyListener
#define ONE       49   // Códigos ASCII para o keyListener
#define TWO       50   // Códigos ASCII para o keyListener
#define THREE     51   // Códigos ASCII para o keyListener
#define FOUR      52   // Códigos ASCII para o keyListener
#define FIVE      53   // Códigos ASCII para o keyListener
#define SIX       54   // Códigos ASCII para o keyListener
#define SEVEN     55   // Códigos ASCII para o keyListener
#define EIGHT     56   // Códigos ASCII para o keyListener
#define NINE      57   // Códigos ASCII para o keyListener
#define PRESSED -32767 // RETURN da API do Windows

#define CLEAR  "\e[1;1H\e[2J" // Padrões ANSI para manipular o terminal
#define CLINE  "\33[2K\r"     // Padrões ANSI para manipular o terminal
#define RESET  "\033[0m"      // Padrões ANSI para manipular o terminal
#define BOLD   "\033[1m"      // Padrões ANSI para manipular o terminal
#define RED    "\033[31m"     // Padrões ANSI para manipular o terminal
#define GREEN  "\033[32m"     // Padrões ANSI para manipular o terminal
#define YELLOW "\033[33m"     // Padrões ANSI para manipular o terminal
#define BLUE   "\033[34m"     // Padrões ANSI para manipular o terminal
#define PURPLE "\033[35m"     // Padrões ANSI para manipular o terminal
#define AQUA   "\033[36m"     // Padrões ANSI para manipular o terminal

typedef struct {
    int code;
    char name[MAX];
    float price;
} book;

typedef struct {
    int code;
    char name[MAX];
    char email[MAX];
    int fone_number[MAX];
} client;

typedef struct {
    int book_code;
    int client_code;
    int sell_code;
    int quantity;
} selling;

// Limpa o buffer do terminal
void clearTerminal() {
    printf("%s", CLEAR);
}

// Check a char* buffer to determine if its parsable
int checkNumbers(char* buffer) {
    int dot_iterator = 0;
    for(int i = 0; i < strlen(buffer)-1; i++) {
        if(isdigit(buffer[i])) continue;
        if((buffer[i] == '.') & (dot_iterator < 1)) {
            dot_iterator++;
            continue;
        }
        printf_s("%s%sInput not parsable.%s\n", BOLD, RED, RESET);
        return 0;
    }
    return 1;
} // End checkNumbers

void addBook() {
    clearTerminal();
    int input_error_iterator = 0;
    int read_code = 0;
    int read_name = 0;
    int read_price = 0;

    book sbook;
    FILE *fptr;

    if((fptr = fopen(BOOKS, WRITE)) == NULL) {
        printf_s("%s%sError opening file, check path.%s\n", BOLD, RED, RESET);
        return;
    }

    while(1) {
        char buffer[8] = {0};
        buffer[MAX-1] = '\0';

        if(input_error_iterator) {
            printf_s("%s%sFound input mismatch, retype. (errors to finish application: %d)%s\n",
            BOLD,
            input_error_iterator == 4 ? RED : YELLOW,
            5-input_error_iterator,
            RESET);
        }

        printf_s("Enter the book code: %s%s\n", YELLOW, RESET);
        
        if((fgets(buffer, sizeof(buffer), stdin)) == NULL) {
            printf_s("%s%sError getting user input.%s\n", BOLD, RED, RESET);
        }

        if(checkNumbers(buffer)) {
            input_error_iterator = 0;
            sscanf_s(buffer, "%d", &sbook.code);
            break;
        } else {
            input_error_iterator++;
            if(input_error_iterator > 4) fclose(fptr); return;
        }
    }


} // End addBooks

int main() {
    Sleep(1);
    int input_error_iterator = 0;
    int index_iterator = 0;
    int show_message = 0;
    char short_buffer[3] = {0};
    char number_pressed = '\0';
    short_buffer[2] = '\0';


    while(1) {
        int safe_code = 0;
        fflush(stdin);

        if(!show_message) {
            clearTerminal();
            printf_s("%d\n\n", input_error_iterator);
            if(input_error_iterator) {
                printf_s("%s%sFound input mismatch, retype. (errors to finish application: %d)%s\n",
                BOLD,
                input_error_iterator == 4 ? RED : YELLOW,
                5-input_error_iterator,
                RESET);
            }

            if(index_iterator == 2) {
                printf_s("%s%sMax input size reached.%s\n", BOLD, YELLOW, RESET);
            }
            
            printf_s("%s%s---------- Library ----------%s\n\n", BOLD, AQUA, RESET);
            printf_s("%s%s[1]%s: Add new book;\n", BOLD, AQUA, RESET);
            printf_s("%s%s[ESC]%s: Finish application.\n\n", BOLD, PURPLE, RESET);
            show_message++;
        }
        printf_s("%s%s%s>%s%s", CLINE, BOLD, AQUA, short_buffer, RESET);
        Sleep(1);

        if(GetAsyncKeyState(ESC) == PRESSED) break;

        // iterates throught the number keys to check if one is pressed
        for(int key = ZERO; key <= NINE; key++) {
            if(GetAsyncKeyState(key) == PRESSED) {
                if(index_iterator == 2) {
                    show_message--;
                    continue;
                }

                number_pressed = (char)key;
                short_buffer[index_iterator] = number_pressed;
                index_iterator++;
            }
        }

        if(GetAsyncKeyState(BACKSPACE) == PRESSED) {
            short_buffer[index_iterator] = '\0';
            index_iterator--;
            continue;
        }

        if(GetAsyncKeyState(ENTER) == PRESSED) {
            if(checkNumbers(short_buffer)) {
                input_error_iterator = 0;
                sscanf_s(short_buffer, "%d", &safe_code);
                show_message--;
            } else {
                input_error_iterator++;
                if(input_error_iterator > 4) break;
                show_message--;
            }

            if(!input_error_iterator) switch(safe_code) {
                case 1: addBook(); break;
                
                case 99: return 420;
                default: printf_s("%s%sCommand not recognized.\n%s", BOLD, YELLOW, RESET); break;
            }
        }
    }

    return 0;
}
