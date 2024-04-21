/*
    @author:    Diogo Tiago Bertoldo
    @IDE:       VSC and Code::Blocks
    @compiler:  GCC 13.1.0
    @so:        Windows 11 (04/2024)
    @Version:   Code::Blocks
    @Notes:     Essa versão não tem o suporte para ANSI Escape Codes
                portanto é smente o texto padrão de terminal
                E execução ele não tem diferenças com a versão VSC
                apenas customização e intuitividade

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
    system("cls");
}

// Verifica um char* buffer para determinar se pode ser passado para int
int checkIntNumbers(char* buffer) {
    for(int i = 0; i < strlen(buffer)-1; i++) {
        if(isdigit(buffer[i])) continue;

        // Se não cair no continue acima, é por que a verificação deu false
        // Logo o caractere não é um dígito válido
        printf_s("Input não pode ser convertido para int.\n");
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
        printf_s("Input não pode ser convertido para float.\n");
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
        printf_s("Erro abrindo o arquivo.\n");
        printf_s("Pressione qualquer tecla para continuar.");
        getchar();
        fclose(fptr);
        return;
    }

    while(running) {
        if(!read_code) {
            printf_s("Insira o codigo do livro: ");
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
                printf_s("Erro ao obter os dados.\n");
                continue;
            }
        } else {
            printf_s("Codigo: %d\n", sbook.code);
        }

        if(!read_name){
            printf_s("\nInsira o titulo do livro: ");
            fflush(stdin);
            if((fgets(sbook.title, sizeof(sbook.title), stdin)) != NULL) {
                clearBuffer(sbook.title);
                clearTerminal();
                sbook.title[strlen(sbook.title)-1] = '\0';
                read_name++;
                continue;
            } else {
                clearTerminal();
                printf_s("Erro ao obter os dados.\n");
                continue;
            }
        } else {
            printf_s("Titulo: %.20s\n", sbook.title);
        }

        if(!read_price) {
            printf_s("\nInsira o preco do livro: ");
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
                printf_s("Erro ao obter os dados.\n");
                continue;
            }

        } else {
            printf_s("Preco: %.2f\n", sbook.price);
        }

        if((read_code) & (read_name) & (read_price)) {
            clearTerminal();
            printf_s("Codigo   Titulo               Preco  ");
            printf_s("\n%-8d %-20.20s %.2f", sbook.code, sbook.title, sbook.price);

            printf_s("\n\nDeseja alterar algum dado [S/N]: ");
            if((fgets(short_buffer, sizeof(short_buffer), stdin)) != NULL) {
                clearBuffer(short_buffer);
                if(toupper(short_buffer[0]) == 'N') {
                    clearTerminal();
                    fwrite(&sbook, sizeof(sbook), 1, fptr);
                    running--;
                } else {
                    printf_s("---------- Escolha o dado a ser Alterado ----------\n\n");
                    printf_s("[1]: Codigo;\n");
                    printf_s("[2]: Titulo;\n");
                    printf_s("[3]: Preco.\n\n");
                    fgets(short_buffer, sizeof(short_buffer), stdin);

                    if(checkIntNumbers(short_buffer)) {
                        sscanf_s(short_buffer, "%d", &change_code);
                        switch(change_code) {
                            case 1: read_code--; break;
                            case 2: read_name--; break;
                            case 3: read_price--; break;
                            default:
                                clearTerminal();
                                printf_s("Comando nao reconhecido, repita.\n");
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
        printf_s("Erro abrindo o arquivo.\n");
        printf_s("Pressione qualquer tecla para continuar.");
        getchar();
        fclose(fptr);
        return;
    }

    printf_s("Codigo   Titulo               Preco  ");
    while(fread_s(&sbook, sizeof(sbook), sizeof(sbook), 1, fptr)) {
        printf_s("\n%-8d %-20.20s %.2f", sbook.code, sbook.title, sbook.price);
        has_books++;
    }

    if(!has_books) printf_s("Nenhum livro encontrado.");
    printf_s("\n\nPressione qualquer tecla para continuar.");
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
        printf_s("Erro abrindo o arquivo.\n");
        printf_s("Pressione qualquer tecla para continuar.");
        getchar();
        fclose(fptr);
        return;
    }

    while(fread_s(&sbook, sizeof(sbook), sizeof(sbook), 1, fptr)) {
        if(sbook.price > higher_price) higher_price = sbook.price;
        has_books++;
    }

    if(higher_price != -1) {
        printf_s("Livro(s) mais caro(s):\n\n");
        printf_s("Codigo   Titulo               Preco  ");
        rewind(fptr);
        while(fread_s(&sbook, sizeof(sbook), sizeof(sbook), 1, fptr)) {
            if(sbook.price < higher_price) continue;
            printf_s("\n%-8d %-20.20s %.2f", sbook.code, sbook.title, sbook.price);
        }
    } else {
        printf_s("Nenhum livro encontrado.");
    }

    printf_s("\n\nPressione qualquer tecla para continuar.");
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
        printf_s("Erro abrindo o arquivo.\n");
        printf_s("Pressione qualquer tecla para continuar.");
        getchar();
        fclose(fptr);
        return;
    }

    while(!value) {
        clearTerminal();
        printf_s("Digite o quantos %% deseja aumentar o preco dos Livros: ");
        if((fgets(short_buffer, sizeof(short_buffer), stdin)) != NULL) {
            clearBuffer(short_buffer);
            if(checkFloatNumbers(short_buffer)) sscanf_s(short_buffer, "%f", &value);
        }
    }

    printf_s("Status Codigo   Titulo               Preco  ");
    while(fread_s(&sbook, sizeof(sbook), sizeof(sbook), 1, fptr)) {
        printf_s("\nANTIGO %-8d %-20.20s %.2f", sbook.code, sbook.title, sbook.price);
    }

    fseek(fptr, 0L, SEEK_SET);
    while(fread_s(&sbook, sizeof(sbook), sizeof(sbook), 1, fptr)) {
        sbook.price += value < 1 ? sbook.price*value : sbook.price*(value/100);

        if(!(fseek(fptr, -sizeof(book), SEEK_CUR))) fwrite(&sbook, sizeof(sbook), 1, fptr);
        changes_iterator++;
        fseek(fptr, changes_iterator*sizeof(book), SEEK_SET);
    }

    fseek(fptr, 0L, SEEK_SET);
    printf_s("\n\nStatus Codigo   Titulo               Preco  ");
    while(fread_s(&sbook, sizeof(sbook), sizeof(sbook), 1, fptr)) {
        printf_s("\nNOVO   %-8d %-20.20s %.2f", sbook.code, sbook.title, sbook.price);
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
        printf_s("Erro abrindo o arquivo.\n");
        printf_s("Pressione qualquer tecla para continuar.");
        getchar();
        fclose(fptr);
        return;
    }

    while(!codigo) {
        clearTerminal();
        printf_s("Digite o codigo do livro que deseja procurar: ");
        if((fgets(short_buffer, sizeof(short_buffer), stdin)) != NULL) {
            clearBuffer(short_buffer);
            if(checkIntNumbers(short_buffer)) sscanf_s(short_buffer, "%d", &codigo);
        }
    }

    while((!found) & (fread_s(&sbook, sizeof(sbook), sizeof(sbook), 1, fptr))) {
        if(sbook.code == codigo) {
            clearTerminal();
            printf_s("Codigo   Titulo               Preco  ");
            printf_s("\n%-8d %-20.20s %.2f", sbook.code, sbook.title, sbook.price);
            printf_s("\n\nPressione qualquer tecla para continuar.");
            found++;
        }
    }

    if(!found) printf_s("Livro com codigo [%d] nao encontrado.", codigo);
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
        printf_s("Erro abrindo o arquivo.\n");
        printf_s("Pressione qualquer tecla para continuar.");
        getchar();
        fclose(fptr);
        return;
    }

    printf_s("Digite o titulo do livro que deseja procurar: ");
    if((fgets(buffer, sizeof(buffer), stdin)) != NULL) {
        clearBuffer(buffer);
        buffer[strlen(buffer)-1] = '\0';
    }

    clearTerminal();
    while((!found) & (fread_s(&sbook, sizeof(sbook), sizeof(sbook), 1, fptr))) {
        if(!(strcmp(sbook.title, buffer))) {
            printf_s("Codigo   Titulo               Preco  ");
            printf_s("\n%-8d %-20.20s %.2f", sbook.code, sbook.title, sbook.price);
            printf_s("\n\nPressione qualquer tecla para continuar.");
            found++;
        }
    }

    if(!found) printf_s("Livro com titulo [%s] nao encontrado.", buffer);
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
        printf_s("Erro abrindo o arquivo.\n");
        printf_s("Pressione qualquer tecla para continuar.");
        getchar();
        fclose(fptr);
        return;
    }

    printf_s("Digite a palavra no titulo do livro que deseja procurar: ");
    if((fgets(buffer, sizeof(buffer), stdin)) != NULL) {
        clearBuffer(buffer);
        buffer[strlen(buffer)-1] = '\0';
    }

    clearTerminal();
    while(fread_s(&sbook, sizeof(sbook), sizeof(sbook), 1, fptr)) {
        if((strstr(sbook.title, buffer)) != NULL) {
            if(!found) printf_s("Codigo   Titulo               Preco  ");
            printf_s("\n%-8d %-20.20s %.2f", sbook.code, sbook.title, sbook.price);
            found++;
        }
    }

    if(!found) printf_s("Livro com palavra [%s] no titulo nao encontrado.", buffer);
    printf_s("\n\nPressione qualquer tecla para continuar.");
    getchar();
    fclose(fptr);
} // Fim searchBookByKeyword

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
        printf_s("Erro abrindo o arquivo.\n");
        printf_s("Pressione qualquer tecla para continuar.");
        getchar();
        fclose(fptr);
        return;
    }

    while(!codigo) {
        clearTerminal();
        printf_s("Digite o codigo do livro que deseja procurar: ");
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
        printf_s("Codigo   Titulo               Preco  ");
        printf_s("\n%-8d %-20.20s %.2f\n\n", sbook.code, sbook.title, sbook.price);

        printf_s("---------- Escolha qual dado alterar ----------%s\n\n");
        printf_s("[1]:  Alterar Titulo;\n");
        printf_s("[2]:  Alterar Preco;\n");
        printf_s("[0]:  Parar de Alterar\n");

        fgets(short_buffer, sizeof(short_buffer), stdin);
        clearBuffer(short_buffer);
        if(checkIntNumbers(short_buffer)) {
            sscanf_s(short_buffer, "%d", &changes_iterator);
            switch(changes_iterator) {
                case 1:
                    changes_made++;
                    printf_s("Digite o novo Titulo: ");
                    fgets(sbook.title, sizeof(sbook.title), stdin);
                    sbook.title[strlen(sbook.title)-1] = '\0';
                    break;
                case 2:
                    changes_made++;
                    printf_s("Digite o novo Preco: ");
                    if((fgets(short_buffer, sizeof(short_buffer), stdin)) != NULL) {
                        if(checkFloatNumbers(short_buffer)) sscanf_s(short_buffer, "%f", &sbook.price);
                    }
                    break;
                case 0:
                    running--;
                    break;
                default:
                    printf_s("Comando nao reconhecido.\n");
                    break;
            }
        }
    } while(running);

    if(found) {
        if(changes_made) {
            printf_s("Deseja aplicar as alteracoes [S/N]: ");
            if((fgets(short_buffer, sizeof(short_buffer), stdin)) != NULL) {
                clearBuffer(short_buffer);
                if(toupper(short_buffer[0]) == 'S') {
                    if(!(fseek(fptr, file_index*sizeof(book), SEEK_SET)))
                    fwrite(&sbook, sizeof(book), 1, fptr);
                    printf_s("\nLivro com codigo [%d] modificado com sucesso.", codigo);
                } else printf_s("\nLivro com codigo [%d] nao modificado.", codigo);
            }
        }else printf_s("\nLivro com codigo [%d] nao modificado.", codigo);
    } else printf_s("Livro com codigo [%d] nao encontrado.", codigo);

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
        printf_s("Erro abrindo o arquivo fonte.\n");
        printf_s("Pressione qualquer tecla para continuar.");
        getchar();
        fclose(source);
        return;
    }

    if((fopen_s(&destiny, DESTINY, WRITE))) {
        printf_s("Erro abrindo o arquivo destino.\n");
        printf_s("Pressione qualquer tecla para continuar.");
        getchar();
        fclose(destiny);
        return;
    }

    while(!codigo) {
        clearTerminal();
        printf_s("Digite o codigo do livro que deseja procurar: ");
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
        printf_s("Codigo   Titulo               Preco  ");
        printf_s("\n%-8d %-20.20s %.2f\n\n", sbook.code, sbook.title, sbook.price);

        printf_s("---------- Deseja remover o Livro ----------\n\n");
        printf_s("[0]:  Nao;\n");
        printf_s("[1]:  Sim;\n");

        fgets(short_buffer, sizeof(short_buffer), stdin);
        clearBuffer(short_buffer);
        if(checkIntNumbers(short_buffer)) {
            sscanf_s(short_buffer, "%d", &removed);
            if(removed) {
                if(!(fseek(source, 0L, SEEK_SET))) while(fread_s(&sbook, sizeof(book), sizeof(book), 1, source)) {
                    if(sbook.code != codigo) fwrite(&sbook, sizeof(book), 1, destiny);
                }

                if((fclose(source)) | (fclose(destiny))) {
                    printf_s("Arquivos nao foram fechados corretamente.");
                    printf_s("\nLivro com codigo [%d] nao removido.", codigo);
                    getchar();
                    return;
                }

                system("Del books.dat");
                system("ren books-new.dat books.dat");

                printf_s("\nLivro com codigo [%d] removido com sucesso.", codigo);
                getchar();
                return;
            } else {
                running--;
                printf_s("\nLivro com codigo [%d] nao removido.", codigo);
            }
        }
    } while(running);

    if(!found) printf_s("Livro com codigo [%d] nao encontrado.", codigo);
    if((fclose(source)) | (fclose(destiny))) {
        printf_s("Arquivos nao foram fechados corretamente.");
    }
    getchar();
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
        printf_s("Erro abrindo o arquivo.\n");
        printf_s("Pressione qualquer tecla para continuar.");
        getchar();
        fclose(fptr);
        return;
    }

    while(running) {
        if(!read_code) {
            printf_s("Insira o codigo do Cliente: ");
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
                printf_s("Erro ao obter os dados.\n");
                continue;
            }
        } else {
            printf_s("Codigo: %d\n", sclient.code);
        }

        if(!read_name){
            printf_s("\nInsira o nome do Cliente: ");
            fflush(stdin);
            if((fgets(sclient.name, sizeof(sclient.name), stdin)) != NULL) {
                clearBuffer(sclient.name);
                clearTerminal();
                sclient.name[strlen(sclient.name)-1] = '\0';
                read_name++;
                continue;
            } else {
                clearTerminal();
                printf_s("Erro ao obter os dados.\n");
                continue;
            }
        } else {
            printf_s("Nome: %.20s\n", sclient.name);
        }

        if(!read_email){
            printf_s("\nInsira o email do Cliente: ");
            fflush(stdin);
            if((fgets(sclient.email, sizeof(sclient.email), stdin)) != NULL) {
                clearBuffer(sclient.email);
                clearTerminal();
                sclient.email[strlen(sclient.email)-1] = '\0';
                read_email++;
                continue;
            } else {
                clearTerminal();
                printf_s("Erro ao obter os dados.\n");
                continue;
            }
        } else {
            printf_s("Email: %.20s\n", sclient.email);
        }

        if(!read_fone){
            printf_s("\nInsira o telefone do Cliente: ");
            fflush(stdin);
            if((fgets(sclient.fone, sizeof(sclient.fone), stdin)) != NULL) {
                clearBuffer(sclient.fone);
                clearTerminal();
                sclient.fone[strlen(sclient.fone)-1] = '\0';
                read_fone++;
                continue;
            } else {
                clearTerminal();
                printf_s("Erro ao obter os dados.\n");
                continue;
            }
        } else {
            printf_s("Telefone: %.20s\n", sclient.fone);
        }

        if((read_code) & (read_name) & (read_email) & (read_fone)) {
            clearTerminal();
            printf_s("Codigo   Nome                 Email           Fone        ");
            printf_s("\n%-8d %-20.20s %-15.15s %-12.12s", sclient.code, sclient.name, sclient.email, sclient.fone);

            printf_s("\n\nDeseja alterar algum dado [S/N]: ");
            if((fgets(short_buffer, sizeof(short_buffer), stdin)) != NULL) {
                clearBuffer(short_buffer);
                if(toupper(short_buffer[0]) == 'N') {
                    clearTerminal();
                    fwrite(&sclient, sizeof(client), 1, fptr);
                    running--;
                } else {
                    printf_s("---------- Escolha o dado a ser Alterado ----------\n\n");
                    printf_s("[1]: Codigo;\n");
                    printf_s("[2]: Nome;\n");
                    printf_s("[3]: Email.\n\n");
                    printf_s("[4]: Telefone.\n\n");
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
                                printf_s("Comando nao reconhecido, repita.\n");
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
        printf_s("Erro abrindo o arquivo.\n");
        printf_s("Pressione qualquer tecla para continuar.");
        getchar();
        fclose(fptr);
        return;
    }

    printf_s("Codigo   Nome                 Email           Fone        ");
    while(fread_s(&sclient, sizeof(client), sizeof(client), 1, fptr)) {
        printf_s("\n%-8d %-20.20s %-15.15s %-12.12s", sclient.code, sclient.name, sclient.email, sclient.fone);
        has_clients++;
    }

    if(!has_clients) printf_s("Nenhum cliente encontrado.");
    printf_s("\n\nPressione qualquer tecla para continuar.");
    getchar();
    fclose(fptr);
} // Fim listClients

client searchClient(int code) {

    FILE *fptr;
    client sclient;
    int found = 0;
    if((fopen_s(&fptr, CLIENTS, READ))) {
        printf_s("Erro abrindo o arquivo.\n");
        printf_s("Pressione qualquer tecla para continuar.");
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
        printf_s("Erro abrindo o arquivo.\n");
        printf_s("Pressione qualquer tecla para continuar.");
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
        printf_s("Erro abrindo o arquivo.\n");
        printf_s("Pressione qualquer tecla para continuar.");
        getchar();
        fclose(fptr);
        return;
    }

    while(running) {
        if(!read_bcode) {
            printf_s("Insira o codigo do Livro: ");
            if((fgets(short_buffer, sizeof(selling), stdin)) != NULL) {
                clearBuffer(short_buffer);
                clearTerminal();
                if(checkIntNumbers(short_buffer)) {
                    sscanf_s(short_buffer, "%d", &ssellings.book_code);

                    sbook = searchBook(ssellings.book_code);
                    if(!sbook.code) {
                        printf_s("\nLivro nao cadastrado.");
                    } else read_bcode++;

                    continue;
                } else {
                    continue;
                }
            } else {
                clearTerminal();
                printf_s("Erro ao obter os dados.%n");
                continue;
            }
        } else {
            printf_s("Codigo do Livro: %d\n", ssellings.book_code);
        }

        if(!read_ccode) {
            printf_s("Insira o codigo do Cliente: ");
            if((fgets(short_buffer, sizeof(selling), stdin)) != NULL) {
                clearBuffer(short_buffer);
                clearTerminal();
                if(checkIntNumbers(short_buffer)) {
                    sscanf_s(short_buffer, "%d", &ssellings.client_code);

                    sclient = searchClient(ssellings.client_code);
                    if(!sclient.code) {
                        printf_s("\nCliente nao cadastrado.");
                    } else read_ccode++;

                    continue;
                } else {
                    continue;
                }
            } else {
                clearTerminal();
                printf_s("Erro ao obter os dados.\n");
                continue;
            }
        } else {
            printf_s("Codigo do Cliente: %d\n", ssellings.client_code);
        }

        if(!read_scode) {
            printf_s("Insira o codigo da Venda: ");
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
                printf_s("Erro ao obter os dados.\n");
                continue;
            }
        } else {
            printf_s("Codigo da Venda: %d\n", ssellings.sell_code);
        }

        if(!read_quantity) {
            printf_s("Insira a quantidade de Livros comprados: ");
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
                printf_s("Erro ao obter os dados.\n");
                continue;
            }
        } else {
            printf_s("Codigo do Livro: %d\n", ssellings.quantity);
        }

        if((read_scode) & (read_bcode) & (read_ccode) & (read_quantity)) {
            clearTerminal();
            printf_s("Venda    Livro    Cliente  Quantidade");
            printf_s("\n%-8d %-8d %-8d %-8d", ssellings.sell_code, ssellings.book_code, ssellings.client_code, ssellings.quantity);

            printf_s("\n\nDeseja alterar algum dado [S/N]: ");
            if((fgets(short_buffer, sizeof(short_buffer), stdin)) != NULL) {
                clearBuffer(short_buffer);
                if(toupper(short_buffer[0]) == 'N') {
                    clearTerminal();
                    fwrite(&ssellings, sizeof(selling), 1, fptr);
                    printf_s("Venda efetuada com sucesso.\n");
                    printf_s("Pressione qualquer tecla para continuar.");
                    getchar();
                    running--;
                } else {
                    printf_s("---------- Escolha o dado a ser Alterado ----------\n\n");
                    printf_s("[1]: Codigo Venda;\n");
                    printf_s("[2]: Codigo Livro;\n");
                    printf_s("[3]: Codigo Cliente.\n\n");
                    printf_s("[4]: Quantidade.\n\n");
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
                                printf_s("Comando nao reconhecido, repita.\n");
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
        printf_s("Erro abrindo o arquivo.\n");
        printf_s("Pressione qualquer tecla para continuar.");
        getchar();
        fclose(fptr);
        return;
    }

    printf_s("Venda    Livro    Cliente  Quantidade");
    while(fread_s(&ssellings, sizeof(selling), sizeof(selling), 1, fptr)) {
        printf_s("\n%-8d %-8d %-8d %-8d", ssellings.sell_code, ssellings.book_code, ssellings.client_code, ssellings.quantity);
        has_selling++;
    }

    if(!has_selling) printf_s("Nenhuma venda encontrada.");
    printf_s("\n\nPressione qualquer tecla para continuar.");
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
        printf_s("Erro abrindo o arquivo.\n");
        printf_s("Pressione qualquer tecla para continuar.");
        getchar();
        fclose(fclient);
        return;
    }

    while(!codigo) {
        clearTerminal();
        printf_s("Digite o codigo do cliente que deseja procurar: ");
        if((fgets(short_buffer, sizeof(short_buffer), stdin)) != NULL) {
            clearBuffer(short_buffer);
            if(checkIntNumbers(short_buffer)) sscanf_s(short_buffer, "%d", &codigo);
        }
    }

    while((!found) & (fread_s(&sclient, sizeof(client), sizeof(client), 1, fclient))) {
        if(sclient.code == codigo) {
            printf_s("Codigo   Nome                 Email           Fone        ");
            printf_s("\n%-8d %-20.20s %-15.15s %-12.12s", sclient.code, sclient.name, sclient.email, sclient.fone);
            found++;
        }
    }

    if(found) {

        int has_selling = 0;

        FILE *fsellings;
        selling ssellings;

        if((fopen_s(&fsellings, SELLINGS, READ))) {
            printf_s("Erro abrindo o arquivo.\n");
            printf_s("Pressione qualquer tecla para continuar.");
            getchar();
            fclose(fsellings);
            return;
        }

        while(fread_s(&ssellings, sizeof(selling), sizeof(selling), 1, fsellings)) {
            if(!has_selling) {
                printf_s("\n\nTodas as compras do cliente\n");
                printf_s("Venda    Livro    Quantidade");
            }
            printf_s("\n%-8d %-8d %-8d", ssellings.sell_code, ssellings.book_code, ssellings.quantity);
            has_selling++;
        }

        if(!has_selling) printf_s("\nNenhuma venda encontrada.");
        fclose(fsellings);
    } else printf_s("Cliente com codigo [%d] nao encontrado.", codigo);

    printf_s("\n\nPressione qualquer tecla para continuar.");
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
        printf_s("Erro abrindo o arquivo.\n");
        printf_s("Pressione qualquer tecla para continuar.");
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
        printf_s("Nenhuma venda encontrada.");
        printf_s("\n\nPressione qualquer tecla para continuar.");
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
        printf_s("Erro abrindo o arquivo.\n");
        printf_s("Pressione qualquer tecla para continuar.");
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
            printf_s("Codigo   Nome                 Email           Fone        ");
            while(fread_s(&sclient, sizeof(client), sizeof(client), 1, fptr)) {
                for(int i = 0; i <= count_clients; i++) if(client_codes[i] == sclient.code) {
                    printf_s("\n%-8d %-20.20s %-15.15s %-12.12s", sclient.code, sclient.name, sclient.email, sclient.fone);
                }

            }

            free(client_codes);
        }
    } else printf_s("Nenhum cliente encontrado.");

    printf_s("\n\nPressione qualquer tecla para continuar.");
    getchar();
    fclose(fptr);
} // Fim listClientsWithSellings

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
                printf_s("Encontrado erro na entrada, digite novamente. (erros para finalizar aplicacao: %d)\n",5-input_error_iterator);

                if(input_error_iterator > 3) running--;
            }

            if(command_unknow) {
                printf_s("Comando nao reconhecido.\n");
                command_unknow--;
            }

            printf_s("---------- Livraria ----------\n\n");
            // Livros
            printf_s("[1]:  Adicionar Livro;\n");
            printf_s("[2]:  Exibir Livros;\n");
            printf_s("[3]:  Exibir Livro(s) mais Caro(s);\n");
            printf_s("[4]:  Aumentar Preco dos Livros;\n");
            printf_s("[5]:  Consultar Livro pelo Codigo;\n");
            printf_s("[6]:  Consultar Livro pelo Titulo;\n");
            printf_s("[7]:  Consultar Livro por palavra-chave no Titulo;\n");
            printf_s("[8]:  Alterar dados de um Livro;\n");
            printf_s("[9]:  Excluir um Livro;\n");

            // Clientes
            printf_s("[10]: Cadastrar Cliente;\n");
            printf_s("[11]: Exibir Clientes;\n");
            printf_s("[12]: Exibir todas as Compras de um Cliente;\n");
            printf_s("[13]: Exibir todos os Clientes que compraram um Livro;\n");

            // Vendas
            printf_s("[14]: Efetuar Venda;\n");
            printf_s("[15]: Listar Vendas;\n");

            printf_s("[99]: Finalizar aplicacao.\n\n");
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
