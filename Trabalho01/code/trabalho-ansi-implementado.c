/*
    @author:    Diogo Tiago Bertoldo
    @IDE:       VSC and Code::Blocks
    @compiler:  GCC 13.1.0
    @so:        Windows 11 (04/2024)
    @Version:   Visual Studio Code
    @Notes:     Essa versão tem suporte a ANSI Escape Codes
                Para executar em sua totalidade, é necessário
                Utilizar um terminal que de suporte a essas
                funções, a maioria dos terminais/shell modernos
                já aceitam, porém um terminal nativo de IDE
                como o Code::Blocks, não aceita.

    Trabalho de Estrutura de Dados, desenvolvido de forma independente
    com base na aplicaçao desenvolvida em sala de aula durante o bimestre

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define BUFFER 256              // Config
#define SHORT_BUFFER 8          // Config
#define BOOKS "books.dat"       // Config
#define CLIENTS "clients.dat"   // Config
#define SELLINGS "sellings.dat" // Config
#define READ "rb"               // Config
#define WRITE "ab"              // Config
#define ALL "rb+"               // Config

#define CLEAR  "\e[1;1H\e[2J"   // Padrões ANSI para manipular o terminal
#define CLINE  "\33[2K\r"       // Padrões ANSI para manipular o terminal
#define RESET  "\033[0m"        // Padrões ANSI para manipular o terminal
#define BOLD   "\033[1m"        // Padrões ANSI para manipular o terminal
#define FAINT  "\033[2m"        // Padrões ANSI para manipular o terminal
#define ITALIC  "\033[3m"       // Padrões ANSI para manipular o terminal

#define GRAY   "\033[38;5;255m" // Padrões ANSI para manipular o terminal
#define DGRAY  "\033[38;5;245m" // Padrões ANSI para manipular o terminal
#define RED    "\033[31m"       // Padrões ANSI para manipular o terminal
#define GREEN  "\033[32m"       // Padrões ANSI para manipular o terminal
#define YELLOW "\033[33m"       // Padrões ANSI para manipular o terminal
#define BLUE   "\033[34m"       // Padrões ANSI para manipular o terminal
#define PURPLE "\033[35m"       // Padrões ANSI para manipular o terminal
#define AQUA   "\033[36m"       // Padrões ANSI para manipular o terminal

typedef struct book {
    int code;
    char title[BUFFER];
    float price;
} book;

typedef struct client {
    int code;
    char name[BUFFER];
    char email[BUFFER];
    char fone[BUFFER];
} client;

typedef struct seeling {
    int book_code;
    int client_code;
    int sell_code;
    int quantity;
} selling;

// Limpa o buffer do terminal
void clearTerminal() {
    printf("%s%s", RESET, CLEAR);
}

// Verifica um char* buffer para determinar se pode ser passado para int
int checkIntNumbers(char* buffer) {
    for(int i = 0; i < strlen(buffer)-1; i++) {
        if(isdigit(buffer[i])) continue;

        // Se não cair no continue acima, é por que a verificação deu false
        // Logo o caractere não é um dígito válido
        printf_s("%s%sInput não pode ser convertido para int.%s\n", BOLD, RED, RESET);
        return 0;
    }
    return 1;
} // Fim checkIntNumbers

// Verifica um char* buffer para determinar se pode ser passado para float
int checkFloatNumbers(char* buffer) {
    int dot_iterator = 0;
    for(int i = 0; i < strlen(buffer)-1; i++) {
        if(isdigit(buffer[i])) continue;

        // Se não for um número, verifica se é um ponto para o número float
        // Se for um ponto, incrementa o iterador (que agora vai responder a false)
        // e continua a verificação, se outro ponto for detectado, é invalido 
        if((buffer[i] == '.') & (!dot_iterator)) {
            dot_iterator++;
            continue;
        }
        printf_s("%s%sInput não pode ser convertido para float.%s\n", BOLD, RED, RESET);
        return 0;
    }
    return 1;
} // Fim checkFloatNumbers

void clearBuffer(char* buffer) {
    if ((strchr(buffer, '\n') == NULL)) while (getchar() != '\n') continue;
} // Fim clearBuffer

void addBook() {
    clearTerminal();
    int running = 1;
    int change_code = 0;
    int read_code = 0;
    int read_name = 0;
    int read_price = 0;

    char short_buffer[SHORT_BUFFER] = {0};

    book sbook;
    FILE *fptr;

    if((fopen_s(&fptr, BOOKS, WRITE))) {
        printf_s("%s%sErro abrindo o arquivo.%s\n", BOLD, RED, RESET);
        printf_s("%s%sPressione qualquer tecla para continuar.%s", BOLD, YELLOW, RESET);
        getchar();
        fclose(fptr);
        return;
    }
    
    while(running) {
        if(!read_code) {
            printf_s("%sInsira o codigo do livro:%s ", BOLD, AQUA);
            if((fgets(short_buffer, sizeof(short_buffer), stdin)) != NULL) {
                clearBuffer(short_buffer);
                clearTerminal();
                if(checkIntNumbers(short_buffer)) {
                    sscanf_s(short_buffer, "%d", &sbook.code);
                    read_code++;
                    continue;
                } else {
                    continue;
                }
            } else {
                clearTerminal();
                printf_s("%s%sErro ao obter os dados.%s\n", BOLD, RED, RESET);
                continue;
            }
        } else {
            printf_s("%sCodigo:%s %d%s\n", BOLD, AQUA, sbook.code, RESET);
        }

        if(!read_name){
            printf_s("%s\nInsira o titulo do livro:%s ", BOLD, AQUA);
            fflush(stdin);
            if((fgets(sbook.title, sizeof(sbook.title), stdin)) != NULL) {
                clearBuffer(sbook.title);
                clearTerminal();
                sbook.title[strlen(sbook.title)-1] = '\0';
                read_name++;
                continue;
            } else {
                clearTerminal();
                printf_s("%s%sErro ao obter os dados.%s\n", BOLD, RED, RESET);
                continue;
            }
        } else {
            printf_s("%sTitulo:%s %.20s%s\n", BOLD, AQUA, sbook.title, RESET);
        }

        if(!read_price) {
            printf_s("%s\nInsira o preco do livro:%s ", BOLD, AQUA);
            if((fgets(short_buffer, sizeof(short_buffer), stdin)) != NULL) {
                clearBuffer(short_buffer);
                clearTerminal();
                if(checkFloatNumbers(short_buffer)) {
                    sscanf_s(short_buffer, "%f", &sbook.price);
                    read_price++;
                    continue;
                } else {
                    continue;
                }
            } else {
                clearTerminal();
                printf_s("%s%sErro ao obter os dados.%s\n", BOLD, RED, RESET);
                continue;
            }

        } else {
            printf_s("%sPreco:%s %.2f%s\n", BOLD, AQUA, sbook.price, RESET);
        }

        if((read_code) & (read_name) & (read_price)) {
            clearTerminal();
            printf_s("%s%sCodigo   Titulo               Preco  %s", BOLD, AQUA, RESET);
            printf_s("\n%s%-8d %-20.20s %.2f%s", BOLD, sbook.code, sbook.title, sbook.price, RESET);

            printf_s("%s%s\n\nDeseja alterar algum dado [S/N]: ", BOLD, YELLOW);
            if((fgets(short_buffer, sizeof(short_buffer), stdin)) != NULL) {
                clearBuffer(short_buffer);
                if(toupper(short_buffer[0]) == 'N') {
                    clearTerminal();
                    fwrite(&sbook, sizeof(sbook), 1, fptr);
                    running--;
                } else {
                    printf_s("%s%s---------- Escolha o dado a ser Alterado ----------%s\n\n", BOLD, YELLOW, RESET);
                    printf_s("%s%s[1]%s: Codigo;\n", BOLD, YELLOW, RESET);
                    printf_s("%s%s[2]%s: Titulo;\n", BOLD, YELLOW, RESET);
                    printf_s("%s%s[3]%s: Preco.\n\n", BOLD, YELLOW, RESET);
                    fgets(short_buffer, sizeof(short_buffer), stdin);
            
                    if(checkIntNumbers(short_buffer)) {
                        sscanf_s(short_buffer, "%d", &change_code);
                        switch(change_code) {
                            case 1: read_code--; break;
                            case 2: read_name--; break;
                            case 3: read_price--; break;
                            default:
                                clearTerminal();
                                printf_s("%s%sComando nao reconhecido, repita.%s\n", BOLD, YELLOW, RESET);
                                break;
                        }
                    }
                }
            }
        }
    }

    fclose(fptr);
} // End addBooks

void listBooks() {
    clearTerminal();
    int has_books = 0;

    FILE *fptr;
    book sbook;

    if((fopen_s(&fptr, BOOKS, READ))) {
        printf_s("%s%sErro abrindo o arquivo.%s\n", BOLD, RED, RESET);
        printf_s("%s%sPressione qualquer tecla para continuar.%s", BOLD, YELLOW, RESET);
        getchar();
        fclose(fptr);
        return;
    }

    printf_s("%s%sCodigo   Titulo               Preco  %s", BOLD, AQUA, RESET);
    while(fread_s(&sbook, sizeof(sbook), sizeof(sbook), 1, fptr)) {
        printf_s("\n%s%-8d %-20.20s %.2f%s", BOLD, sbook.code, sbook.title, sbook.price, RESET);
        has_books++;
    }

    if(!has_books) printf_s("%s%sNenhum livro encontrado.%s", BOLD, YELLOW, RESET);
    printf_s("%s%s\n\nPressione qualquer tecla para continuar.%s", BOLD, YELLOW, RESET);
    getchar();
    fclose(fptr);
} // Fim listBooks

void listHigherPriceBooks() {
    clearTerminal();
    int has_books = 0;
    double higher_price = 0;

    FILE *fptr;
    book sbook;

    if((fopen_s(&fptr, BOOKS, READ))) {
        printf_s("%s%sErro abrindo o arquivo.%s\n", BOLD, RED, RESET);
        printf_s("%s%sPressione qualquer tecla para continuar.%s", BOLD, YELLOW, RESET);
        getchar();
        fclose(fptr);
        return;
    }

    while(fread_s(&sbook, sizeof(sbook), sizeof(sbook), 1, fptr)) {
        if(sbook.price > higher_price) higher_price = sbook.price;
        has_books++;
    }

    if(higher_price != -1) {
        printf_s("%sLivro(s) mais caro(s):%s\n\n", BOLD, RESET);
        printf_s("%s%sCodigo   Titulo               Preco  %s", BOLD, AQUA, RESET);
        rewind(fptr);
        while(fread_s(&sbook, sizeof(sbook), sizeof(sbook), 1, fptr)) {
            if(sbook.price < higher_price) continue;
            printf_s("\n%s%-8d %-20.20s %.2f%s", BOLD, sbook.code, sbook.title, sbook.price, RESET);
        }
    } else {
        printf_s("%s%sNenhum livro encontrado.%s", BOLD, YELLOW, RESET);
    }

    printf_s("%s%s\n\nPressione qualquer tecla para continuar.%s", BOLD, YELLOW, RESET);
    getchar();
    fclose(fptr);
} // Fim listHigherPriceBooks

void increaseBooksPrice() {
    clearTerminal();
    float value = 0;
    int changes_iterator = 0;
    char short_buffer[SHORT_BUFFER] = {0};

    FILE *fptr;
    book sbook;

    if((fopen_s(&fptr, BOOKS, ALL))) {
        printf_s("%s%sErro abrindo o arquivo.%s\n", BOLD, RED, RESET);
        printf_s("%s%sPressione qualquer tecla para continuar.%s", BOLD, YELLOW, RESET);
        getchar();
        fclose(fptr);
        return;
    }

    while(!value) {
        clearTerminal();
        printf_s("%sDigite o quantos %% deseja aumentar o preco dos Livros:%s ", BOLD, AQUA);
        if((fgets(short_buffer, sizeof(short_buffer), stdin)) != NULL) {
            clearBuffer(short_buffer);
            if(checkFloatNumbers(short_buffer)) sscanf_s(short_buffer, "%f", &value);
        }
    }

    printf_s("%s%sStatus Codigo   Titulo               Preco  %s", BOLD, AQUA, RESET);
    while(fread_s(&sbook, sizeof(sbook), sizeof(sbook), 1, fptr)) {
        printf_s("\nANTIGO %s%-8d %-20.20s %s%.2f%s", BOLD, sbook.code, sbook.title, RED, sbook.price, RESET);
    }

    fseek(fptr, 0L, SEEK_SET);
    while(fread_s(&sbook, sizeof(sbook), sizeof(sbook), 1, fptr)) {
        sbook.price += value < 1 ? sbook.price*value : sbook.price*(value/100);

        if(!(fseek(fptr, -sizeof(book), SEEK_CUR))) fwrite(&sbook, sizeof(sbook), 1, fptr);
        changes_iterator++;
        fseek(fptr, changes_iterator*sizeof(book), SEEK_SET);
    }
    
    fseek(fptr, 0L, SEEK_SET);
    printf_s("%s%s\n\nStatus Codigo   Titulo               Preco  %s", BOLD, AQUA, RESET);
    while(fread_s(&sbook, sizeof(sbook), sizeof(sbook), 1, fptr)) {
        printf_s("\nNOVO   %s%-8d %-20.20s %s%.2f%s", BOLD, sbook.code, sbook.title, GREEN, sbook.price, RESET);
    }

    getchar();
    fclose(fptr);
} // Fim increaseBooksPrice

void searchBookByCode() {
    clearTerminal();
    int codigo = 0;
    int found = 0;
    char short_buffer[SHORT_BUFFER] = {0};

    FILE *fptr;
    book sbook;

    if((fopen_s(&fptr, BOOKS, READ))) {
        printf_s("%s%sErro abrindo o arquivo.%s\n", BOLD, RED, RESET);
        printf_s("%s%sPressione qualquer tecla para continuar.%s", BOLD, YELLOW, RESET);
        getchar();
        fclose(fptr);
        return;
    }

    while(!codigo) {
        clearTerminal();
        printf_s("%sDigite o codigo do livro que deseja procurar:%s ", BOLD, AQUA);
        if((fgets(short_buffer, sizeof(short_buffer), stdin)) != NULL) {
            clearBuffer(short_buffer);
            if(checkIntNumbers(short_buffer)) sscanf_s(short_buffer, "%d", &codigo);
        }
    }

    while((!found) & (fread_s(&sbook, sizeof(sbook), sizeof(sbook), 1, fptr))) {
        if(sbook.code == codigo) {
            clearTerminal();
            printf_s("%s%sCodigo   Titulo               Preco  %s", BOLD, AQUA, RESET);
            printf_s("\n%s%-8d %-20.20s %.2f%s", BOLD, sbook.code, sbook.title, sbook.price, RESET);
            printf_s("%s%s\n\nPressione qualquer tecla para continuar.%s", BOLD, YELLOW, RESET);
            found++;
        }
    }

    if(!found) printf_s("%s%sLivro com codigo [%s%d%s] nao encontrado.%s", BOLD, YELLOW, AQUA, codigo, YELLOW, RESET);
    getchar();
    fclose(fptr);
} // Fim searchBooksByCode

void searchBookByName() {
    clearTerminal();
    int found = 0;
    char buffer[BUFFER] = {0};

    FILE *fptr;
    book sbook;

    if((fopen_s(&fptr, BOOKS, READ))) {
        printf_s("%s%sErro abrindo o arquivo.%s\n", BOLD, RED, RESET);
        printf_s("%s%sPressione qualquer tecla para continuar.%s", BOLD, YELLOW, RESET);
        getchar();
        fclose(fptr);
        return;
    }

    printf_s("%sDigite o titulo do livro que deseja procurar:%s ", BOLD, AQUA);
    if((fgets(buffer, sizeof(buffer), stdin)) != NULL) {
        clearBuffer(buffer);
        buffer[strlen(buffer)-1] = '\0';
    }

    clearTerminal();
    while((!found) & (fread_s(&sbook, sizeof(sbook), sizeof(sbook), 1, fptr))) {
        if(!(strcmp(sbook.title, buffer))) {
            printf_s("%s%sCodigo   Titulo               Preco  %s", BOLD, AQUA, RESET);
            printf_s("\n%s%-8d %-20.20s %.2f%s", BOLD, sbook.code, sbook.title, sbook.price, RESET);
            printf_s("%s%s\n\nPressione qualquer tecla para continuar.%s", BOLD, YELLOW, RESET);
            found++;
        }
    }

    if(!found) printf_s("%s%sLivro com titulo [%s%s%s] nao encontrado.%s", BOLD, YELLOW, AQUA, buffer, YELLOW, RESET);
    getchar();
    fclose(fptr);
} // Fim searchBookByName

void searchBookByKeyword() {
    clearTerminal();
    int found = 0;
    char buffer[BUFFER] = {0};

    FILE *fptr;
    book sbook;

    if((fopen_s(&fptr, BOOKS, READ))) {
        printf_s("%s%sErro abrindo o arquivo.%s\n", BOLD, RED, RESET);
        printf_s("%s%sPressione qualquer tecla para continuar.%s", BOLD, YELLOW, RESET);
        getchar();
        fclose(fptr);
        return;
    }

    printf_s("%sDigite a palavra no titulo do livro que deseja procurar:%s ", BOLD, AQUA);
    if((fgets(buffer, sizeof(buffer), stdin)) != NULL) {
        clearBuffer(buffer);
        buffer[strlen(buffer)-1] = '\0';
    }

    clearTerminal();
    while(fread_s(&sbook, sizeof(sbook), sizeof(sbook), 1, fptr)) {
        if((strstr(sbook.title, buffer)) != NULL) {
            if(!found) printf_s("%s%sCodigo   Titulo               Preco  %s", BOLD, AQUA, RESET);
            printf_s("\n%s%-8d %-20.20s %.2f%s", BOLD, sbook.code, sbook.title, sbook.price, RESET);
            found++;
        }
    }

    if(!found) printf_s("%s%sLivro com palavra [%s%s%s] no titulo nao encontrado.%s", BOLD, YELLOW, AQUA, buffer, YELLOW, RESET);
    printf_s("%s%s\n\nPressione qualquer tecla para continuar.%s", BOLD, YELLOW, RESET);
    getchar();
    fclose(fptr);
} // Fim searchBookByName

void changeBookData() {
    clearTerminal();
    int codigo = 0;
    int changes_iterator = 0;
    int found = 0;
    int file_index = 0;
    int changes_made = 0;
    int running = 1;
    char short_buffer[SHORT_BUFFER] = {0};

    FILE *fptr;
    book sbook;

    if((fopen_s(&fptr, BOOKS, ALL))) {
        printf_s("%s%sErro abrindo o arquivo.%s\n", BOLD, RED, RESET);
        printf_s("%s%sPressione qualquer tecla para continuar.%s", BOLD, YELLOW, RESET);
        getchar();
        fclose(fptr);
        return;
    }

    while(!codigo) {
        clearTerminal();
        printf_s("%sDigite o codigo do livro que deseja procurar:%s ", BOLD, AQUA);
        if((fgets(short_buffer, sizeof(short_buffer), stdin)) != NULL) {
            clearBuffer(short_buffer);
            if(checkIntNumbers(short_buffer)) sscanf_s(short_buffer, "%d", &codigo);
        }
    }

    while((!found) & (fread_s(&sbook, sizeof(book), sizeof(book), 1, fptr))) {
        if(sbook.code == codigo) {
            found++;
            fseek(fptr, -sizeof(book), SEEK_CUR);
        } else file_index++;
    }

    if(found) do {
        clearTerminal();
        printf_s("%s%sCodigo   Titulo               Preco  %s", BOLD, AQUA, RESET);
        printf_s("\n%s%-8d %-20.20s %.2f%s\n\n", BOLD, sbook.code, sbook.title, sbook.price, RESET);

        printf_s("%s%s---------- Escolha qual dado alterar ----------%s\n\n", BOLD, AQUA, RESET);
        printf_s("%s%s[1]%s:  Alterar Titulo;\n", BOLD, AQUA, RESET);
        printf_s("%s%s[2]%s:  Alterar Preco;\n", BOLD, AQUA, RESET);
        printf_s("%s%s[0]%s:  Parar de Alterar\n", BOLD, RED, RESET);

        fgets(short_buffer, sizeof(short_buffer), stdin);
        clearBuffer(short_buffer);
        if(checkIntNumbers(short_buffer)) {
            sscanf_s(short_buffer, "%d", &changes_iterator);
            switch(changes_iterator) {
                case 1:
                    changes_made++;
                    printf_s("%sDigite o novo Titulo:%s ", BOLD, AQUA);
                    fgets(sbook.title, sizeof(sbook.title), stdin);
                    sbook.title[strlen(sbook.title)-1] = '\0';
                    break;
                case 2:
                    changes_made++;
                    printf_s("%sDigite o novo Preco:%s ", BOLD, AQUA);
                    if((fgets(short_buffer, sizeof(short_buffer), stdin)) != NULL) {
                        if(checkFloatNumbers(short_buffer)) sscanf_s(short_buffer, "%f", &sbook.price);
                    }
                    break;
                case 0:
                    running--;
                    break;
                default:
                    printf_s("%s%sComando nao reconhecido.\n%s", BOLD, YELLOW, RESET);
                    break;
            }
        }
    } while(running);

    if(found) {
        if(changes_made) {
            printf_s("%s%sDeseja aplicar as alteracoes [S/N]: ", BOLD, YELLOW);
            if((fgets(short_buffer, sizeof(short_buffer), stdin)) != NULL) {
                clearBuffer(short_buffer);
                if(toupper(short_buffer[0]) == 'S') {
                    if(!(fseek(fptr, file_index*sizeof(book), SEEK_SET)))
                    fwrite(&sbook, sizeof(book), 1, fptr);
                    printf_s("%s%s\nLivro com codigo [%s%d%s] modificado com sucesso.%s", BOLD, YELLOW, AQUA, codigo, YELLOW, RESET);
                } else printf_s("%s%s\nLivro com codigo [%s%d%s] nao modificado.%s", BOLD, YELLOW, AQUA, codigo, YELLOW, RESET);
            }
        }else printf_s("%s%s\nLivro com codigo [%s%d%s] nao modificado.%s", BOLD, YELLOW, AQUA, codigo, YELLOW, RESET);
    }

    if(!found) printf_s("%s%sLivro com codigo [%s%d%s] nao encontrado.%s", BOLD, YELLOW, AQUA, codigo, YELLOW, RESET);
    getchar();
    fclose(fptr);
} // Fim changeBookData

void removeBook() {
    clearTerminal();
    int codigo = 0;
    int found = 0;
    int file_index = 0;
    int removed = 0;
    int running = 1;
    char short_buffer[SHORT_BUFFER] = {0};

    char DESTINY[] = "books-new.dat";

    FILE *source;
    FILE *destiny;
    book sbook;

    if((fopen_s(&source, BOOKS, READ))) {
        printf_s("%s%sErro abrindo o arquivo fonte.%s\n", BOLD, RED, RESET);
        printf_s("%s%sPressione qualquer tecla para continuar.%s", BOLD, YELLOW, RESET);
        getchar();
        fclose(source);
        return;
    }

    if((fopen_s(&destiny, DESTINY, WRITE))) {
        printf_s("%s%sErro abrindo o arquivo destino.%s\n", BOLD, RED, RESET);
        printf_s("%s%sPressione qualquer tecla para continuar.%s", BOLD, YELLOW, RESET);
        getchar();
        fclose(destiny);
        return;
    }

    while(!codigo) {
        clearTerminal();
        printf_s("%sDigite o codigo do livro que deseja procurar:%s ", BOLD, AQUA);
        if((fgets(short_buffer, sizeof(short_buffer), stdin)) != NULL) {
            clearBuffer(short_buffer);
            if(checkIntNumbers(short_buffer)) sscanf_s(short_buffer, "%d", &codigo);
        }
    }

    while((!found) & (fread_s(&sbook, sizeof(book), sizeof(book), 1, source))) {
        if(sbook.code == codigo) {
            found++;
            fseek(source, -sizeof(book), SEEK_CUR);
        } else file_index++;
    }

    if(found) do {
        clearTerminal();
        printf_s("%s%sCodigo   Titulo               Preco  %s", BOLD, AQUA, RESET);
        printf_s("\n%s%-8d %-20.20s %.2f%s\n\n", BOLD, sbook.code, sbook.title, sbook.price, RESET);

        printf_s("%s%s---------- Deseja remover o Livro ----------%s\n\n", BOLD, AQUA, RESET);
        printf_s("%s%s[0]%s:  Nao;\n", BOLD, YELLOW, RESET);
        printf_s("%s%s[1]%s:  Sim;\n", BOLD, RED, RESET);

        fgets(short_buffer, sizeof(short_buffer), stdin);
        clearBuffer(short_buffer);
        if(checkIntNumbers(short_buffer)) {
            sscanf_s(short_buffer, "%d", &removed);
            if(removed) {
                if(!(fseek(source, 0L, SEEK_SET))) while(fread_s(&sbook, sizeof(book), sizeof(book), 1, source)) {
                    if(sbook.code != codigo) fwrite(&sbook, sizeof(book), 1, destiny);
                }

                if((fclose(source)) | (fclose(destiny))) {
                    printf_s("%s%sArquivos nao foram fechados corretamente.%s", BOLD, RED, RESET);
                    printf_s("%s%s\nLivro com codigo [%s%d%s] nao removido.%s", BOLD, YELLOW, AQUA, codigo, YELLOW, RESET);
                    getchar();
                    return;
                }
                
                system("Del books.dat");
                system("ren books-new.dat books.dat");
            
                printf_s("%s%s\nLivro com codigo [%s%d%s] removido com sucesso.%s", BOLD, RED, YELLOW, codigo, RED, RESET);
                getchar();
                return;
            } else {
                running--;
                printf_s("%s%s\nLivro com codigo [%s%d%s] nao removido.%s", BOLD, YELLOW, AQUA, codigo, YELLOW, RESET);
            }
        }
    } while(running);

    if(!found) printf_s("%s%sLivro com codigo [%s%d%s] nao encontrado.%s", BOLD, YELLOW, AQUA, codigo, YELLOW, RESET);
    if((fclose(source)) | (fclose(destiny))) {
        printf_s("%s%sArquivos nao foram fechados corretamente.%s", BOLD, RED, RESET);
        getchar();
    }
} // Fim removeBook

void addClient() {
    clearTerminal();
    int running = 1;
    int change_code = 0;
    int read_code = 0;
    int read_name = 0;
    int read_email = 0;
    int read_fone = 0;

    char short_buffer[SHORT_BUFFER] = {0};

    client sclient;
    FILE *fptr;

    if((fopen_s(&fptr, CLIENTS, WRITE))) {
        printf_s("%s%sErro abrindo o arquivo.%s\n", BOLD, RED, RESET);
        printf_s("%s%sPressione qualquer tecla para continuar.%s", BOLD, YELLOW, RESET);
        getchar();
        fclose(fptr);
        return;
    }
    
    while(running) {
        if(!read_code) {
            printf_s("%sInsira o codigo do Cliente:%s ", BOLD, AQUA);
            if((fgets(short_buffer, sizeof(short_buffer), stdin)) != NULL) {
                clearBuffer(short_buffer);
                clearTerminal();
                if(checkIntNumbers(short_buffer)) {
                    sscanf_s(short_buffer, "%d", &sclient.code);
                    read_code++;
                    continue;
                } else {
                    continue;
                }
            } else {
                clearTerminal();
                printf_s("%s%sErro ao obter os dados.%s\n", BOLD, RED, RESET);
                continue;
            }
        } else {
            printf_s("%sCodigo:%s %d%s\n", BOLD, AQUA, sclient.code, RESET);
        }

        if(!read_name){
            printf_s("%s\nInsira o nome do Cliente:%s ", BOLD, AQUA);
            fflush(stdin);
            if((fgets(sclient.name, sizeof(sclient.name), stdin)) != NULL) {
                clearBuffer(sclient.name);
                clearTerminal();
                sclient.name[strlen(sclient.name)-1] = '\0';
                read_name++;
                continue;
            } else {
                clearTerminal();
                printf_s("%s%sErro ao obter os dados.%s\n", BOLD, RED, RESET);
                continue;
            }
        } else {
            printf_s("%sNome:%s %.20s%s\n", BOLD, AQUA, sclient.name, RESET);
        }

        if(!read_email){
            printf_s("%s\nInsira o email do Cliente:%s ", BOLD, AQUA);
            fflush(stdin);
            if((fgets(sclient.email, sizeof(sclient.email), stdin)) != NULL) {
                clearBuffer(sclient.email);
                clearTerminal();
                sclient.email[strlen(sclient.email)-1] = '\0';
                read_email++;
                continue;
            } else {
                clearTerminal();
                printf_s("%s%sErro ao obter os dados.%s\n", BOLD, RED, RESET);
                continue;
            }
        } else {
            printf_s("%sEmail:%s %.20s%s\n", BOLD, AQUA, sclient.email, RESET);
        }

        if(!read_fone){
            printf_s("%s\nInsira o telefone do Cliente:%s ", BOLD, AQUA);
            fflush(stdin);
            if((fgets(sclient.fone, sizeof(sclient.fone), stdin)) != NULL) {
                clearBuffer(sclient.fone);
                clearTerminal();
                sclient.fone[strlen(sclient.fone)-1] = '\0';
                read_fone++;
                continue;
            } else {
                clearTerminal();
                printf_s("%s%sErro ao obter os dados.%s\n", BOLD, RED, RESET);
                continue;
            }
        } else {
            printf_s("%sTelefone:%s %.20s%s\n", BOLD, AQUA, sclient.fone, RESET);
        }

        if((read_code) & (read_name) & (read_email) & (read_fone)) {
            clearTerminal();
            printf_s("%s%sCodigo   Nome                 Email           Fone        %s", BOLD, AQUA, RESET);
            printf_s("\n%s%-8d %-20.20s %-15.15s %-12.12s%s", BOLD, sclient.code, sclient.name, sclient.email, sclient.fone, RESET);

            printf_s("%s%s\n\nDeseja alterar algum dado [S/N]: ", BOLD, YELLOW);
            if((fgets(short_buffer, sizeof(short_buffer), stdin)) != NULL) {
                clearBuffer(short_buffer);
                if(toupper(short_buffer[0]) == 'N') {
                    clearTerminal();
                    fwrite(&sclient, sizeof(client), 1, fptr);
                    running--;
                } else {
                    printf_s("%s%s---------- Escolha o dado a ser Alterado ----------%s\n\n", BOLD, YELLOW, RESET);
                    printf_s("%s%s[1]%s: Codigo;\n", BOLD, YELLOW, RESET);
                    printf_s("%s%s[2]%s: Nome;\n", BOLD, YELLOW, RESET);
                    printf_s("%s%s[3]%s: Email.\n\n", BOLD, YELLOW, RESET);
                    printf_s("%s%s[4]%s: Telefone.\n\n", BOLD, YELLOW, RESET);
                    fgets(short_buffer, sizeof(short_buffer), stdin);
            
                    if(checkIntNumbers(short_buffer)) {
                        sscanf_s(short_buffer, "%d", &change_code);
                        switch(change_code) {
                            case 1: read_code--; break;
                            case 2: read_name--; break;
                            case 3: read_email--; break;
                            case 4: read_fone--; break;
                            default:
                                clearTerminal();
                                printf_s("%s%sComando nao reconhecido, repita.%s\n", BOLD, YELLOW, RESET);
                                break;
                        }
                    }
                }
            }
        }
    }

    fclose(fptr);
} // End addClient

void listClients() {
    clearTerminal();
    int has_clients = 0;

    FILE *fptr;
    client sclient;

    if((fopen_s(&fptr, CLIENTS, READ))) {
        printf_s("%s%sErro abrindo o arquivo.%s\n", BOLD, RED, RESET);
        printf_s("%s%sPressione qualquer tecla para continuar.%s", BOLD, YELLOW, RESET);
        getchar();
        fclose(fptr);
        return;
    }

    printf_s("%s%sCodigo   Nome                 Email           Fone        %s", BOLD, AQUA, RESET);
    while(fread_s(&sclient, sizeof(client), sizeof(client), 1, fptr)) {
        printf_s("\n%s%-8d %-20.20s %-15.15s %-12.12s%s", BOLD, sclient.code, sclient.name, sclient.email, sclient.fone, RESET);
        has_clients++;
    }

    if(!has_clients) printf_s("%s%sNenhum cliente encontrado.%s", BOLD, YELLOW, RESET);
    printf_s("%s%s\n\nPressione qualquer tecla para continuar.%s", BOLD, YELLOW, RESET);
    getchar();
    fclose(fptr);
} // Fim listClients

client searchClient(int code) {

    FILE *fptr;
    client sclient;
    int found = 0;
    if((fopen_s(&fptr, CLIENTS, READ))) {
        printf_s("%s%sErro abrindo o arquivo.%s\n", BOLD, RED, RESET);
        printf_s("%s%sPressione qualquer tecla para continuar.%s", BOLD, YELLOW, RESET);
        getchar();
        fclose(fptr);
        return;
    }

    while((!found) & (fread_s(&sclient, sizeof(client), sizeof(client), 1, fptr))) {
        if(sclient.code == code) found++;
    }

    fclose(fptr);
    if(!found) {
        sclient.code = 0;
        return sclient;
    } else return sclient;
} // Fim searchClient

book searchBook(int code) {

    FILE *fptr;
    book sbook;
    int found = 0;
    if((fopen_s(&fptr, BOOKS, READ))) {
        printf_s("%s%sErro abrindo o arquivo.%s\n", BOLD, RED, RESET);
        printf_s("%s%sPressione qualquer tecla para continuar.%s", BOLD, YELLOW, RESET);
        getchar();
        fclose(fptr);
        return;
    }

    while((!found) & (fread_s(&sbook, sizeof(book), sizeof(book), 1, fptr))) {
        if(sbook.code == code) found++;
    }

    fclose(fptr);
    if(!found) {
        sbook.code = 0;
        return sbook;
    } else return sbook;
} // Fim searchBook

void addSelling() {
    clearTerminal();
    int running = 1;
    int change_code = 0;
    int read_bcode = 0;
    int read_ccode = 0;
    int read_scode = 0;
    int read_quantity = 0;

    char short_buffer[SHORT_BUFFER] = {0};

    selling ssellings;
    client sclient;
    book sbook;

    FILE *fptr;

    if((fopen_s(&fptr, SELLINGS, WRITE))) {
        printf_s("%s%sErro abrindo o arquivo.%s\n", BOLD, RED, RESET);
        printf_s("%s%sPressione qualquer tecla para continuar.%s", BOLD, YELLOW, RESET);
        getchar();
        fclose(fptr);
        return;
    }
    
    while(running) {
        if(!read_bcode) {
            printf_s("%sInsira o codigo do Livro:%s ", BOLD, AQUA);
            if((fgets(short_buffer, sizeof(selling), stdin)) != NULL) {
                clearBuffer(short_buffer);
                clearTerminal();
                if(checkIntNumbers(short_buffer)) {
                    sscanf_s(short_buffer, "%d", &ssellings.book_code);
                    
                    sbook = searchBook(ssellings.book_code);
                    if(!sbook.code) {
                        printf_s("\n%s%sLivro nao cadastrado.%s", BOLD, RED, RESET);
                    } else read_bcode++;

                    continue;
                } else {
                    continue;
                }
            } else {
                clearTerminal();
                printf_s("%s%sErro ao obter os dados.%s\n", BOLD, RED, RESET);
                continue;
            }
        } else {
            printf_s("%sCodigo do Livro:%s %d%s\n", BOLD, AQUA, ssellings.book_code, RESET);
        }

        if(!read_ccode) {
            printf_s("%sInsira o codigo do Cliente:%s ", BOLD, AQUA);
            if((fgets(short_buffer, sizeof(selling), stdin)) != NULL) {
                clearBuffer(short_buffer);
                clearTerminal();
                if(checkIntNumbers(short_buffer)) {
                    sscanf_s(short_buffer, "%d", &ssellings.client_code);
                
                    sclient = searchClient(ssellings.client_code);
                    if(!sclient.code) {
                        printf_s("\n%s%sCliente nao cadastrado.%s", BOLD, RED, RESET);
                    } else read_ccode++;

                    continue;
                } else {
                    continue;
                }
            } else {
                clearTerminal();
                printf_s("%s%sErro ao obter os dados.%s\n", BOLD, RED, RESET);
                continue;
            }
        } else {
            printf_s("%sCodigo do Cliente:%s %d%s\n", BOLD, AQUA, ssellings.client_code, RESET);
        }

        if(!read_scode) {
            printf_s("%sInsira o codigo da Venda:%s ", BOLD, AQUA);
            if((fgets(short_buffer, sizeof(selling), stdin)) != NULL) {
                clearBuffer(short_buffer);
                clearTerminal();
                if(checkIntNumbers(short_buffer)) {
                    sscanf_s(short_buffer, "%d", &ssellings.sell_code);
                    read_scode++;
                    continue;
                } else {
                    continue;
                }
            } else {
                clearTerminal();
                printf_s("%s%sErro ao obter os dados.%s\n", BOLD, RED, RESET);
                continue;
            }
        } else {
            printf_s("%sCodigo da Venda:%s %d%s\n", BOLD, AQUA, ssellings.sell_code, RESET);
        }

        if(!read_quantity) {
            printf_s("%sInsira a quantidade de Livros comprados:%s ", BOLD, AQUA);
            if((fgets(short_buffer, sizeof(selling), stdin)) != NULL) {
                clearBuffer(short_buffer);
                clearTerminal();
                if(checkIntNumbers(short_buffer)) {
                    sscanf_s(short_buffer, "%d", &ssellings.quantity);
                    read_quantity++;
                    continue;
                } else {
                    continue;
                }
            } else {
                clearTerminal();
                printf_s("%s%sErro ao obter os dados.%s\n", BOLD, RED, RESET);
                continue;
            }
        } else {
            printf_s("%sCodigo do Livro:%s %d%s\n", BOLD, AQUA, ssellings.quantity, RESET);
        }

        if((read_scode) & (read_bcode) & (read_ccode) & (read_quantity)) {
            clearTerminal();
            printf_s("%s%sVenda    Livro    Cliente  Quantidade%s", BOLD, AQUA, RESET);
            printf_s("\n%s%-8d %-8d %-8d %-8d%s", BOLD, ssellings.sell_code, ssellings.book_code, ssellings.client_code, ssellings.quantity, RESET);

            printf_s("%s%s\n\nDeseja alterar algum dado [S/N]: ", BOLD, YELLOW);
            if((fgets(short_buffer, sizeof(short_buffer), stdin)) != NULL) {
                clearBuffer(short_buffer);
                if(toupper(short_buffer[0]) == 'N') {
                    clearTerminal();
                    fwrite(&ssellings, sizeof(selling), 1, fptr);
                    printf_s("%s%sVenda efetuada com sucesso.\n%s", BOLD, YELLOW, RESET);
                    printf_s("%s%sPressione qualquer tecla para continuar.%s", BOLD, YELLOW, RESET);
                    getchar();
                    running--;
                } else {
                    printf_s("%s%s---------- Escolha o dado a ser Alterado ----------%s\n\n", BOLD, YELLOW, RESET);
                    printf_s("%s%s[1]%s: Codigo Venda;\n", BOLD, YELLOW, RESET);
                    printf_s("%s%s[2]%s: Codigo Livro;\n", BOLD, YELLOW, RESET);
                    printf_s("%s%s[3]%s: Codigo Cliente.\n\n", BOLD, YELLOW, RESET);
                    printf_s("%s%s[4]%s: Quantidade.\n\n", BOLD, YELLOW, RESET);
                    fgets(short_buffer, sizeof(short_buffer), stdin);
            
                    if(checkIntNumbers(short_buffer)) {
                        sscanf_s(short_buffer, "%d", &change_code);
                        switch(change_code) {
                            case 1: read_scode--; break;
                            case 2: read_bcode--; break;
                            case 3: read_ccode--; break;
                            case 4: read_quantity--; break;
                            default:
                                clearTerminal();
                                printf_s("%s%sComando nao reconhecido, repita.%s\n", BOLD, YELLOW, RESET);
                                break;
                        }
                    }
                }
            }
        }
    }

    fclose(fptr);
} // End addSelling

void listSellings() {
    clearTerminal();
    int has_selling = 0;

    FILE *fptr;
    selling ssellings;

    if((fopen_s(&fptr, SELLINGS, READ))) {
        printf_s("%s%sErro abrindo o arquivo.%s\n", BOLD, RED, RESET);
        printf_s("%s%sPressione qualquer tecla para continuar.%s", BOLD, YELLOW, RESET);
        getchar();
        fclose(fptr);
        return;
    }

    printf_s("%s%sVenda    Livro    Cliente  Quantidade%s", BOLD, AQUA, RESET);
    while(fread_s(&ssellings, sizeof(selling), sizeof(selling), 1, fptr)) {
        printf_s("\n%s%-8d %-8d %-8d %-8d%s", BOLD, ssellings.sell_code, ssellings.book_code, ssellings.client_code, ssellings.quantity, RESET);
        has_selling++;
    }

    if(!has_selling) printf_s("%s%sNenhuma venda encontrada.%s", BOLD, YELLOW, RESET);
    printf_s("%s%s\n\nPressione qualquer tecla para continuar.%s", BOLD, YELLOW, RESET);
    getchar();
    fclose(fptr);
} // Fim listSellings

void listAllClientSellings() {
    clearTerminal();
    int codigo = 0;
    int found = 0;
    int running = 1;
    char short_buffer[SHORT_BUFFER] = {0};

    FILE *fclient;
    client sclient;
    selling sellings;

    if((fopen_s(&fclient, CLIENTS, READ))) {
        printf_s("%s%sErro abrindo o arquivo.%s\n", BOLD, RED, RESET);
        printf_s("%s%sPressione qualquer tecla para continuar.%s", BOLD, YELLOW, RESET);
        getchar();
        fclose(fclient);
        return;
    }

    while(!codigo) {
        clearTerminal();
        printf_s("%sDigite o codigo do cliente que deseja procurar:%s ", BOLD, AQUA);
        if((fgets(short_buffer, sizeof(short_buffer), stdin)) != NULL) {
            clearBuffer(short_buffer);
            if(checkIntNumbers(short_buffer)) sscanf_s(short_buffer, "%d", &codigo);
        }
    }

    while((!found) & (fread_s(&sclient, sizeof(client), sizeof(client), 1, fclient))) {
        if(sclient.code == codigo) {
            printf_s("%s%sCodigo   Nome                 Email           Fone        %s", BOLD, AQUA, RESET);
            printf_s("\n%s%-8d %-20.20s %-15.15s %-12.12s%s", BOLD, sclient.code, sclient.name, sclient.email, sclient.fone, RESET);
            found++;
        }
    }

    if(found) {
        
        int has_selling = 0;

        FILE *fsellings;
        selling ssellings;

        if((fopen_s(&fsellings, SELLINGS, READ))) {
            printf_s("%s%sErro abrindo o arquivo.%s\n", BOLD, RED, RESET);
            printf_s("%s%sPressione qualquer tecla para continuar.%s", BOLD, YELLOW, RESET);
            getchar();
            fclose(fsellings);
            return;
        }

        while(fread_s(&ssellings, sizeof(selling), sizeof(selling), 1, fsellings)) {
            if(!has_selling) {
                printf_s("%s%s\n\nTodas as compras do cliente\n%s", BOLD, YELLOW, RESET);
                printf_s("%s%sVenda    Livro    Quantidade%s", BOLD, AQUA, RESET);
            }
            printf_s("\n%s%-8d %-8d %-8d%s", BOLD, ssellings.sell_code, ssellings.book_code, ssellings.quantity, RESET);
            has_selling++;
        }

        if(!has_selling) printf_s("%s%s\nNenhuma venda encontrada.%s", BOLD, YELLOW, RESET);
        fclose(fsellings);
    } else printf_s("%s%sCliente com codigo [%s%d%s] nao encontrado.%s", BOLD, YELLOW, AQUA, codigo, YELLOW, RESET);

    printf_s("%s%s\n\nPressione qualquer tecla para continuar.%s", BOLD, YELLOW, RESET);
    getchar();
    fclose(fclient);
} // Fim listAllClientSellings

int *searchEachIndividualClientSellings(int size) {

    int *client_codes = malloc(size);
    int has_selling = 0;

    int array_iterator = 0;
    int already_added = 0;

    FILE *fptr;
    selling ssellings;

    if((fopen_s(&fptr, SELLINGS, READ))) {
        printf_s("%s%sErro abrindo o arquivo.%s\n", BOLD, RED, RESET);
        printf_s("%s%sPressione qualquer tecla para continuar.%s", BOLD, YELLOW, RESET);
        getchar();
        fclose(fptr);
        return;
    }

    while(fread_s(&ssellings, sizeof(selling), sizeof(selling), 1, fptr)) {
        already_added = 0;
        for(int i = 0; i <= size; i++) {
            if(client_codes[i] == ssellings.client_code) already_added++;
        }

        if(!already_added) {
            client_codes[array_iterator] = ssellings.client_code;
            array_iterator++;
        }
        has_selling++;
    }

    fclose(fptr);

    if(has_selling) {
        return client_codes;
    } else {
        printf_s("%s%sNenhuma venda encontrada.%s", BOLD, YELLOW, RESET);
        printf_s("%s%s\n\nPressione qualquer tecla para continuar.%s", BOLD, YELLOW, RESET);
        getchar();

        return NULL;
    }
}

void listClientsWithSellings() {
    clearTerminal();
    int count_clients = 0;

    FILE *fptr;
    client sclient;

    if((fopen_s(&fptr, CLIENTS, READ))) {
        printf_s("%s%sErro abrindo o arquivo.%s\n", BOLD, RED, RESET);
        printf_s("%s%sPressione qualquer tecla para continuar.%s", BOLD, YELLOW, RESET);
        getchar();
        fclose(fptr);
        return;
    }

    while(fread_s(&sclient, sizeof(client), sizeof(client), 1, fptr)) {
        count_clients++;
    }

    if(count_clients) {
        int *client_codes = searchEachIndividualClientSellings(count_clients);

        if(client_codes != NULL) {
            fseek(fptr, 0L, SEEK_SET);
            printf_s("%s%sCodigo   Nome                 Email           Fone        %s", BOLD, AQUA, RESET);
            while(fread_s(&sclient, sizeof(client), sizeof(client), 1, fptr)) {
                for(int i = 0; i <= count_clients; i++) if(client_codes[i] == sclient.code) {
                    printf_s("\n%s%-8d %-20.20s %-15.15s %-12.12s%s", BOLD, sclient.code, sclient.name, sclient.email, sclient.fone, RESET);
                }
                
            }

            free(client_codes);
        }
    } else printf_s("%s%sNenhum cliente encontrado.%s", BOLD, YELLOW, RESET);
    
    printf_s("%s%s\n\nPressione qualquer tecla para continuar.%s", BOLD, YELLOW, RESET);
    getchar();
    fclose(fptr);
} // Fim listClientsWithSellings

// printf_s("%s%sCodigo   Nome                 Email           Fone        %s", BOLD, AQUA, RESET);
// printf_s("\n%s%-8d %-20.20s %-15.15s %-12.12s%s", BOLD, sclient.code, sclient.name, sclient.email, sclient.fone, RESET);

int main() {
    int running = 1;
    int input_error_iterator = 0;
    int show_message = 0;
    int command_unknow = 0;

    char short_buffer[SHORT_BUFFER] = {0};
    int safe_code = 0;

    while(running) {
        if(!show_message) {
            clearTerminal();
            if(input_error_iterator) {
                printf_s("%s%sEncontrado erro na entrada, digite novamente. (erros para finalizar aplicacao: %d)%s\n",
                BOLD,
                input_error_iterator == 4 ? RED : YELLOW,
                5-input_error_iterator,
                RESET);

                if(input_error_iterator > 3) running--;
            }

            if(command_unknow) {
                printf_s("%s%sComando nao reconhecido.\n%s", BOLD, YELLOW, RESET);
                command_unknow--;
            }
            
            printf_s("%s%s---------- Livraria ----------%s\n\n", BOLD, AQUA, RESET);
            printf_s("            .--.                      .---.");
            printf_s("        .---|__|              .-.     |~~~|");
            printf_s("        .--|===|--|_          |_|     |~~~|--.");
            printf_s("        |  |===|  |'\\     .---!~|  .--|   |--|");
            printf_s("        |%%|   |  |.'\\    |===| |--|%%|   |  |");
            printf_s("        |%%|   |  |\\.'\\   |   | |__|  |   |  |");
            printf_s("        |  |   |  | \\  \\  |===| |==|  |   |  |");
            printf_s("        |  |   |__|  \\.'\\ |   |_|__|  |~~~|__|");
            printf_s("        |  |===|--|   \\.'\\|===|~|--|%%|~~~|--|");
            printf_s("        ^--^---'--^    `-'`---^-^--^--^---'--' ");

            // Livros
            printf_s("%s%s[1]%s:  Adicionar Livro;\n", BOLD, AQUA, RESET);
            printf_s("%s%s[2]%s:  Exibir Livros;\n", BOLD, AQUA, RESET);
            printf_s("%s%s[3]%s:  Exibir Livro(s) mais %sCaro(s)%s;\n", BOLD, RED, RESET, GREEN, RESET);
            printf_s("%s%s[4]%s:  Aumentar %sPreco%s dos %sLivros%s;\n", BOLD, RED, RESET, GREEN, RESET, GREEN, RESET);
            printf_s("%s%s[5]%s:  Consultar Livro pelo %sCodigo%s;\n", BOLD, AQUA, RESET, GREEN, RESET);
            printf_s("%s%s[6]%s:  Consultar Livro pelo %sTitulo%s;\n", BOLD, AQUA, RESET, GREEN, RESET);
            printf_s("%s%s[7]%s:  Consultar Livro por %spalavra-chave%s no %sTitulo%s;\n", BOLD, AQUA, RESET, GREEN, RESET, GREEN, RESET);
            printf_s("%s%s[8]%s:  Alterar dados de um Livro;\n", BOLD, AQUA, RESET);
            printf_s("%s%s[9]%s:  Excluir um Livro;\n", BOLD, AQUA, RESET);

            // Clientes
            printf_s("%s%s[10]%s: Cadastrar Cliente;\n", BOLD, AQUA, RESET);
            printf_s("%s%s[11]%s: Exibir Clientes;\n", BOLD, AQUA, RESET);
            printf_s("%s%s[12]%s: Exibir todas as %sCompras%s de um Cliente;\n", BOLD, RED, RESET, GREEN, RESET); // TODO
            printf_s("%s%s[13]%s: Exibir todos os Clientes que %scompraram%s um Livro;\n", BOLD, RED, RESET, GREEN, RESET); // TODO

            // Vendas
            printf_s("%s%s[14]%s: Efetuar Venda;\n", BOLD, AQUA, RESET);
            printf_s("%s%s[15]%s: Listar Vendas;\n", BOLD, AQUA, RESET);

            printf_s("%s%s[99]%s: Finalizar aplicacao.\n\n", BOLD, PURPLE, RESET);
            show_message++;
        }

        fflush(stdin);
        fgets(short_buffer, sizeof(short_buffer), stdin);
        clearBuffer(short_buffer);
        if(checkIntNumbers(short_buffer)) {
            sscanf_s(short_buffer, "%d", &safe_code);
            show_message--;
            switch(safe_code) {
                case 1: addBook(); break;
                case 2: listBooks(); break;
                case 3: listHigherPriceBooks(); break;
                case 4: increaseBooksPrice(); break;
                case 5: searchBookByCode(); break;
                case 6: searchBookByName(); break;
                case 7: searchBookByKeyword(); break;
                case 8: changeBookData(); break;
                case 9: removeBook(); break;
                case 10: addClient(); break;
                case 11: listClients(); break;
                case 12: listAllClientSellings(); break;
                case 13: listClientsWithSellings(); break;
                case 14: addSelling(); break;
                case 15: listSellings(); break;
                case 99: running--; break;
                default: command_unknow++; break;
            }
        } else {
            show_message--;
            input_error_iterator++;
        }

    }

    return 0;
}
