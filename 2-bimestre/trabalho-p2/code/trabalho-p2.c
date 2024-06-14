//      @author                 Diogo Tiago Bertoldo
//      @github                 www.github.com/axlentrise
//      @compiler               GGC 13.1
//      @so                     Windows 11
//      
//      @note: Desenvolvido independentemente por mim para
//             o trabalho da P2, dessa vez feito de forma
//             mais simples, focando na funcionalidade.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// making the code cleaner
typedef struct node node;
#define CLEAR  "\e[1;1H\e[2J"   // clears the console
#define BUFFER 32               // smol buffer

// Base struct of my nodes
struct node {
    int info;
    node* next;
};

// verify an char** input to see if its parseble, then parse it to the variable adress
int checkInput(char* buffer, int* option) {
    for(int i = 0; i < strlen(buffer)-1; i++) {
        if(isdigit(buffer[i])) continue;
        return 0;
    }
    sscanf(buffer, "%d", option);
    return 1;
}

// creates and adds a new node to the start of the given list
node* add_start(node* list, int value) {
    node* ptr = malloc(sizeof(node));

    ptr->info = value;
    ptr->next = list;

    list = ptr;

    return list;
}

node* add_crescent(node* list, int value) {
    if(!list) return add_start(list, value);

    node* nnode = malloc(sizeof(node));
    node* search_ptr = list;
    node* ptr = list;

    nnode->info = value;

    // Search for the node with the info greater than value
    while((search_ptr->next) && (search_ptr->info < value)) search_ptr = search_ptr->next;

    // adds at the end
    if(search_ptr->info < value) {
        search_ptr->next = nnode;
        nnode->next = NULL;
    } else if(search_ptr == list) {
        nnode->next = search_ptr;
        list = nnode;
    } else {
        // iff was not added at the start or end of the list, adds the value in the right place
        ptr = list;
        while(ptr->next != search_ptr) ptr = ptr->next;

        ptr->next = nnode;
        nnode->next = search_ptr;
    }

    return list;
}

// creates and adds a new node to the end of the given list
node* add_end(node* list, int value) {

    node* nnode = malloc(sizeof(node));
    node* ptr = list;

    nnode->info = value;
    nnode->next = NULL;

    if(!ptr) {
        list = nnode;
        return list;
    }

    while(ptr->next) ptr = ptr->next;

    ptr->next = nnode;

    return list;
}

// Show the list if any value was added, or a message saying its empty
void show_list(node* list) {
    int counter = 0;
    node* ptr = list;

    if(!ptr) {
        printf("Lista vazia.");
        return;
    }

    while(ptr) {
        if(!counter) {
            printf("[ ");
            counter++;
        }
        
        printf("%d -> ", ptr->info);
        ptr = ptr->next;
    }

    if(!ptr) printf("null ]");
}

// Remove the first node from the List
node* remove_first(node* list, int* value) {
    node* holder = list;

    *value = list->info;
    list = list->next;

    free(holder);
    return list;
}

// Remove the last node from the List
node* remove_last(node* list, int* value) {
    node* search_ptr = list;
    node* ptr = list;

    while(search_ptr->next) search_ptr = search_ptr->next;

    *value = search_ptr->info;
    if(search_ptr == list) {
        list = NULL;
    } else {
        while(ptr->next != search_ptr) ptr = ptr->next;

        ptr->next = NULL;
    }

    free(search_ptr);
    return list;
}

// Remove a value from the List
node* remove_value(node* list, int value) {
    node* search_ptr = list;
    node* ptr = list;

    while((search_ptr) && (search_ptr->info != value)) search_ptr = search_ptr->next;

    if(!search_ptr) {
        printf("\nO valor %d nao existe na Lista.", value);
        return list;
    }

    if(search_ptr == list) {
        return remove_first(list, &value);
    } else {
        while(ptr->next != search_ptr) ptr = ptr->next;

        ptr->next = search_ptr->next;
    }

    printf("\nO valor %d foi removido da Lista.", value);
    free(search_ptr);
    return list;
}

// Returns the List length
int length(node* list) {
    node* ptr = list;
    int counter = 0;

    while(ptr) {
        ptr = ptr->next;
        counter++;
    }

    return counter;
}

// Search for a value in the List
int search(node* list, int value) {
    node* ptr = list;

    while(ptr && ptr->info != value) ptr = ptr->next;
    return ptr ? 1 : 0;
}

// Compares the two List
int compare(node* first_list, node* secnd_list) {
    node* first_ptr = first_list;
    node* secnd_ptr = secnd_list;

    printf("\n");
    printf("Lista 1: ");
    show_list(first_list);
    printf("\n");
    printf("Lista 2: ");
    show_list(secnd_ptr);
    
    if(length(first_list) != length(secnd_list)) return 0;

    while(first_ptr && first_ptr->info == secnd_ptr->info) {
        first_ptr = first_ptr->next;
        secnd_ptr = secnd_ptr->next;
    }
    
    return first_ptr ? 0 : 1;
}

// Pushes a new node into the list
void push(node** stack, int value) {
    node* nnode = malloc(sizeof(node));

    nnode->info = value;
    nnode->next = *stack;

    *stack = nnode;
}

// Pops a node and return its value
int pop(node** stack) {
    node* nnode = *stack;
    int value = (*stack)->info;

    (*stack) = (*stack)->next;

    free(nnode);
    return value;
}

// Show the values of a given Stack
void show_stack(node** stack) {
    node* aux_stack = NULL;
    int value = 0;
    int counter = 0;

    while(*stack) {
        value = pop(stack);

        printf("#%d - [%d]\n", counter, value);
        push(&aux_stack, value);

        counter++;
    }

    while(aux_stack) {
        value = pop(&aux_stack);
        push(stack, value);
    }
}

// Auxiliar function for the get_evens_and_odds
void clear_stacks(node** even, node** odd) {
    while(odd) pop(odd);
    while(even) pop(even);
}

// Get evens and odds from a List
void get_evens_and_odds(node** list, node** even, node** odd) {
    node* aux_odd;
    node* aux_even;
    node* ptr = *list;

    clear_stacks(*even, *odd);

    while(ptr) {
        if(ptr->info % 2) {
            push(odd, ptr->info);
        } else push(even, ptr->info);

        ptr = ptr->next;
    }
}

// returns a List inverted
node* invert(node* list) {
    node* stack = NULL;
    node* ptr = list;
    node* new_list = NULL;
    int value;

    while(ptr) {
        push(&stack, ptr->info);
        ptr = ptr->next;
    }

    while(stack) {
        value = pop(&stack);
        new_list = add_end(new_list, value);
    }

    return new_list;
}

// returns the higher value of a List
int higher_value(node* list) {
    node* search_ptr = list;
    int higher = search_ptr->info;

    while(search_ptr) {
        if(higher < search_ptr->info) higher = search_ptr->info;
        search_ptr = search_ptr->next;
    }

    return higher;
}

// clones the even numbers of a stack
void clone_evens(node** stack) {
    node* aux_stack = NULL;
    int value = 0;

    while(*stack) push(&aux_stack, pop(stack));
    
    while(aux_stack) {
        value = pop(&aux_stack);
        push(stack, value);
        if(!(value % 2)) push(stack, value);
    }
}

// Main program
int main(int argc, char** argv) {

    node* first_list = NULL;
    node* secnd_list = NULL;
    node* first_stack = NULL;
    node* secnd_stack = NULL;

    int executing = 1;              // Control Variable
    int option = 1;                 // User console navigation
    int value = 0;                  // variable for user input
    char buffer[BUFFER] = {'\0'};   // Buffer for user input

    do {
        printf("%s", CLEAR);
        printf("\n-------------- Trabalho P2 -------------");
        printf("\nMostrar Lista ..................... [01]");   // ok
        printf("\nInserir no inicio da Lista ........ [02]");   // ok
        printf("\nInserir no Fim da Lista ........... [03]");   // ok
        printf("\nInserir em Ordem Crescente ........ [04]");   // ok

        printf("\nRealizar um Push em uma das Listas  [05]");   // ok
        printf("\nRealizar um Pop em uma das Listas . [06]");   // ok

        printf("\nRemover do Inicio da Lista ........ [07]");   // ok
        printf("\nRemover do Fim da Lista ........... [08]");   // ok
        printf("\nRemover um Valor da Lista ......... [09]");   // ok

        printf("\nComprimento da Lista .............. [10]");   // ok
        printf("\nProcurar Valor na Lista ........... [11]");   // ok
        printf("\nComparar duas Listas .............. [12]");   // ok
        printf("\nMostrar Pilha ..................... [13]");   // ok

        printf("\nCriar Pilha Impar e Par ........... [14]");   // ok
        printf("\nInverter Lista .................... [15]");   // ok
        printf("\nMaior valor de uma Lista .......... [16]");   // ok
        printf("\nClonar pares de uma Pilha ......... [17]");   // ok

        printf("\n\nEncerrar .......................... [00]");
        printf("\nEscolha: ");
        fgets(buffer, sizeof(buffer), stdin);

        if(checkInput(buffer, &option)) switch(option) {
            case 1: // Mostra as duas Listas
                printf("\n\nPrimeira Lista: ");
                show_list(first_list);
                printf("\nSegunda Lista: ");
                show_list(secnd_list);

                printf("\n\nPressione ENTER para continuar...");
                getchar();
                break;
            case 2: //Adiciona no inicio da Lista
                printf("\n\nDigite o Valor a ser Inserido: ");
                fgets(buffer, sizeof(buffer), stdin);
                if(checkInput(buffer, &value)) {
                    printf("\nQual lista deseja Adicionar:");
                    printf("\nPrimeira Lista ......... [1]");
                    printf("\nSegunda Lista .......... [2]");
                    printf("\nEscolha: ");
                    fgets(buffer, sizeof(buffer), stdin);
                    if(checkInput(buffer, &option)) switch(option) {
                        case 1:
                            printf("\n%d foi adicionado no inicio da primeira Lista.", value);
                            first_list = add_start(first_list, value);
                            break;
                        case 2:
                            printf("\n%d foi adicionado no inicio da segunda Lista.", value);
                            secnd_list = add_start(secnd_list, value);
                            break;
                        default: printf("\nNenhum comando valido inexistente. Tente novamente.");
                    } else printf("\nValor do comando digitado invalido.");
                } else printf("\nValor digitado invalido.");

                printf("\n\nPressione ENTER para continuar...");
                getchar();
                break;
            case 3: // Adiciona no fim da Lista
                printf("\n\nDigite o Valor a ser Inserido: ");
                fgets(buffer, sizeof(buffer), stdin);
                if(checkInput(buffer, &value)) {
                    printf("\nQual lista deseja Adicionar:");
                    printf("\nPrimeira Lista ......... [1]");
                    printf("\nSegunda Lista .......... [2]");
                    printf("\nEscolha: ");
                    fgets(buffer, sizeof(buffer), stdin);
                    if(checkInput(buffer, &option)) switch(option) {
                        case 1:
                            printf("\n%d foi adicionado ao fim da primeira Lista.", value);
                            first_list = add_end(first_list, value);
                            break;
                        case 2:
                            printf("\n%d foi adicionado ao fim da segunda Lista.", value);
                            secnd_list = add_end(secnd_list, value);
                            break;
                        default: printf("\nNenhum comando valido inexistente. Tente novamente.");
                    } else printf("\nValor do comando digitado invalido.");
                } else printf("\nValor digitado invalido.");

                printf("\n\nPressione ENTER para continuar...");
                getchar();
                break;
            case 4: // Adiciona na Lista de forma crescente
                printf("\n\nDigite o Valor a ser Inserido: ");
                fgets(buffer, sizeof(buffer), stdin);
                if(checkInput(buffer, &value)) {
                    printf("\nQual lista deseja Adicionar:");
                    printf("\nPrimeira Lista ......... [1]");
                    printf("\nSegunda Lista .......... [2]");
                    printf("\nEscolha: ");
                    fgets(buffer, sizeof(buffer), stdin);
                    if(checkInput(buffer, &option)) switch(option) {
                        case 1:
                            printf("\n%d foi adicionado a primeira Lista em ordem Crescente.", value);
                            first_list = add_crescent(first_list, value);
                            break;
                        case 2:
                            printf("\n%d foi adicionado a segunda Lista em ordem Crescente.", value);
                            secnd_list = add_crescent(secnd_list, value);
                            break;
                        default: printf("\nNenhum comando valido existente. Tente novamente.");
                    } else printf("\nValor do comando digitado invalido.");
                } else printf("\nValor digitado invalido.");

                printf("\n\nPressione ENTER para continuar...");
                getchar();
                break;
            case 05: // faz o Push de um valor em umas das Listas
                printf("\n\nDigite o Valor que sera feito o Push: ");
                fgets(buffer, sizeof(buffer), stdin);
                if(checkInput(buffer, &value)) {
                    printf("\nQual lista deseja realizar a operacao:");
                    printf("\nPrimeira Lista ................... [1]");
                    printf("\nSegunda Lista .................... [2]");
                    printf("\nEscolha: ");
                    fgets(buffer, sizeof(buffer), stdin);
                    if(checkInput(buffer, &option)) switch(option) {
                        case 1:
                            printf("\n\n%d foi adicionado a primeira Lista.", value);
                            push(&first_list, value);
                            break;
                        case 2:
                            printf("\n\n%d foi adicionado a segunda Lista.", value);
                            push(&secnd_list, value);
                            break;
                        default: printf("\nNenhum comando valido existente. Tente novamente.");
                    } else printf("\nValor do comando digitado invalido.");
                } else printf("\nValor digitado invalido.");

                printf("\n\nPressione ENTER para continuar...");
                getchar();
                break;
            case 06: // Faz o Pop em uma das Listas
                printf("\nQual lista deseja realizar a operacao:");
                printf("\nPrimeira Lista ................... [1]");
                printf("\nSegunda Lista .................... [2]");
                printf("\nEscolha: ");
                fgets(buffer, sizeof(buffer), stdin);
                if(checkInput(buffer, &option)) switch(option) {
                    case 1:
                        if(!first_list) {
                            printf("\n\nLista vazia.");
                            break;
                        }

                        printf("\n\n%d foi removido da primeira Lista.", pop(&first_list));
                        break;
                    case 2:
                        if(!secnd_list) {
                            printf("\n\nLista vazia.");
                            break;
                        }

                        printf("\n\n%d foi removido da segunda Lista.", pop(&first_list));
                        break;
                    default: printf("\nNenhum comando valido existente. Tente novamente.");
                } else printf("\nValor do comando digitado invalido.");

                printf("\n\nPressione ENTER para continuar...");
                getchar();
                break;
            case 7: // Remove do inicio da Lista
                printf("\nQual lista deseja Remover:");
                printf("\nPrimeira Lista ....... [1]");
                printf("\nSegunda Lista ........ [2]");
                printf("\nEscolha: ");
                fgets(buffer, sizeof(buffer), stdin);
                if(checkInput(buffer, &option)) switch(option) {
                    case 1:
                        if(!first_list) {
                            printf("\nLista vazia.");
                            break;
                        }

                        first_list = remove_first(first_list, &value);
                        printf("\n%d foi da primeira Lista.", value);
                        break;
                    case 2:
                        if(!secnd_list) {
                            printf("\nLista vazia.");
                            break;
                        }

                        secnd_list = remove_first(secnd_list, &value);
                        printf("\n%d foi da segunda Lista.", value);
                        break;
                    default: printf("\nNenhum comando valido existente. Tente novamente.");
                } else printf("\nValor do comando digitado invalido.");

                printf("\n\nPressione ENTER para continuar...");
                getchar();
                break;
            case 8: // Remove do fim da Lista
                printf("\nQual lista deseja Remover:");
                printf("\nPrimeira Lista ....... [1]");
                printf("\nSegunda Lista ........ [2]");
                printf("\nEscolha: ");
                fgets(buffer, sizeof(buffer), stdin);
                if(checkInput(buffer, &option)) switch(option) {
                    case 1:
                        if(!first_list) {
                            printf("\nLista vazia.");
                            break;
                        }

                        first_list = remove_last(first_list, &value);
                        printf("\n%d foi da primeira Lista.", value);
                        break;
                    case 2:
                        if(!secnd_list) {
                            printf("\nLista vazia.");
                            break;
                        }

                        secnd_list = remove_last(secnd_list, &value);
                        printf("\n%d foi da segunda Lista.", value);
                        break;
                    default: printf("\nNenhum comando valido existente. Tente novamente.");
                } else printf("\nValor do comando digitado invalido.");

                printf("\n\nPressione ENTER para continuar...");
                getchar();
                break;
            case 9: // Remove um valor da Lista
                printf("\n\nDigite o Valor a ser Removido: ");
                fgets(buffer, sizeof(buffer), stdin);
                if(checkInput(buffer, &value)) {
                    printf("\nQual lista deseja Remover:");
                    printf("\nPrimeira Lista ......... [1]");
                    printf("\nSegunda Lista .......... [2]");
                    printf("\nEscolha: ");
                    fgets(buffer, sizeof(buffer), stdin);
                    if(checkInput(buffer, &option)) switch(option) {
                        case 1:
                            if(!first_list) {
                                printf("\nLista vazia.");
                                break;
                            }

                            first_list = remove_value(first_list, value);
                            break;
                        case 2:
                            if(!secnd_list) {
                                printf("\nLista vazia.");
                                break;
                            }

                            secnd_list = remove_value(secnd_list, value);
                            break;
                        default: printf("\nNenhum comando valido existente. Tente novamente.");
                    } else printf("\nValor do comando digitado invalido.");
                } else printf("\nValor digitado invalido.");

                printf("\n\nPressione ENTER para continuar...");
                getchar();
                break;
            case 10: // Mostra o tamanho da Lista
                printf("\nQual lista deseja mostrar o Tamanho:");
                printf("\nPrimeira Lista ................. [1]");
                printf("\nSegunda Lista .................. [2]");
                printf("\nEscolha: ");
                fgets(buffer, sizeof(buffer), stdin);
                if(checkInput(buffer, &option)) switch(option) {
                    case 1:
                        if(!first_list) {
                            printf("\nLista vazia. Tamanho: 0.");
                            break;
                        }

                        printf("\nTamanho da primeira Lista: %d", length(first_list));
                        break;
                    case 2:
                        if(!secnd_list) {
                            printf("\nLista vazia. Tamanho: 0.");
                            break;
                        }

                        printf("\nTamanho da segunda Lista: %d", length(first_list));
                        break;
                    default: printf("\nNenhum comando valido existente. Tente novamente.");
                } else printf("\nValor do comando digitado invalido.");

                printf("\n\nPressione ENTER para continuar...");
                getchar();
                break;
            case 11: // Exibe se um valor existe na Lista
                printf("\n\nDigite o Valor a ser Procurado: ");
                fgets(buffer, sizeof(buffer), stdin);
                if(checkInput(buffer, &value)) {
                    printf("\nQual lista deseja procurar:");
                    printf("\nPrimeira Lista ........ [1]");
                    printf("\nSegunda Lista ......... [2]");
                    printf("\nEscolha: ");
                    fgets(buffer, sizeof(buffer), stdin);
                    if(checkInput(buffer, &option)) switch(option) {
                        case 1:
                            if(!first_list) {
                                printf("\nLista vazia.");
                                break;
                            }

                            if(search(first_list, value)) {
                                printf("\nO valor %d existe na Lista.", value);
                            } else printf("\nO valor %d nao existe na Lista.", value);
                            break;
                        case 2:
                            if(!secnd_list) {
                                printf("\nLista vazia.");
                                break;
                            }

                            if(search(secnd_list, value)) {
                                printf("\nO valor %d existe na Lista.", value);
                            } else printf("\nO valor %d nao existe na Lista.", value);
                            break;
                        default: printf("\nNenhum comando valido existente. Tente novamente.");
                    } else printf("\nValor do comando digitado invalido.");
                } else printf("\nValor digitado invalido.");

                printf("\n\nPressione ENTER para continuar...");
                getchar();
                break;
            case 12: // Compara as duas Listas
                if(compare(first_list, secnd_list)) {
                    printf("\nAs Listas sao iguais.");
                } else printf("\nAs Listas sao diferentes.");

                printf("\n\nPressione ENTER para continuar...");
                getchar();
                break;
            case 13: // Mostrar uma das Pilhas
                printf("\nQual Pilha mostrar os valores:");
                printf("\nPrimeira Pilha ........... [1]");
                printf("\nSegunda Pilha ............ [2]");
                printf("\nEscolha: ");
                fgets(buffer, sizeof(buffer), stdin);
                if(checkInput(buffer, &option)) switch(option) {
                    case 1:
                        if(!first_stack) {
                            printf("\n\nPilha vazia.");
                            break;
                        }

                        show_stack(&first_stack);
                        break;
                    case 2:
                        if(!secnd_stack) {
                            printf("\n\nPilha vazia.");
                            break;
                        }

                        show_stack(&secnd_stack);
                        break;
                    default: printf("\nNenhum comando valido existente. Tente novamente.");
                } else printf("\nValor do comando digitado invalido.");

                printf("\n\nPressione ENTER para continuar...");
                getchar();
                break;
            case 14: // Converter lista em duas pilhas
                printf("\nQual Lista deseja realizar a operacao:");
                printf("\nPrimeira Pilha ................... [1]");
                printf("\nSegunda Pilha .................... [2]");
                printf("\nEscolha: ");
                fgets(buffer, sizeof(buffer), stdin);
                if(checkInput(buffer, &option)) switch(option) {
                    case 1:
                        if(!first_list) {
                            printf("\n\nLista vazia.");
                            break;
                        }

                        get_evens_and_odds(&first_list, &first_stack, &secnd_stack);

                        printf("\n\nPares:\n");
                        show_stack(&first_stack);
                        printf("\nImpares:\n");
                        show_stack(&secnd_stack);
                        break;
                    case 2:
                        if(!secnd_list) {
                            printf("\n\nLista vazia.");
                            break;
                        }

                        get_evens_and_odds(&secnd_list, &first_stack, &secnd_stack);
                        
                        printf("\n\nPares:\n");
                        show_stack(&first_stack);
                        printf("\nImpares:\n");
                        show_stack(&secnd_stack);
                        break;
                    default: printf("\nNenhum comando valido existente. Tente novamente.");
                } else printf("\nValor do comando digitado invalido.");

                printf("\n\nPressione ENTER para continuar...");
                getchar();
                break;
            case 15: // Inverte uma lista
                printf("\nQual Lista deseja realizar a operacao:");
                printf("\nPrimeira Pilha ................... [1]");
                printf("\nSegunda Pilha .................... [2]");
                printf("\nEscolha: ");
                fgets(buffer, sizeof(buffer), stdin);
                if(checkInput(buffer, &option)) switch(option) {
                    case 1:
                        if(!first_list) {
                            printf("\n\nLista vazia.");
                            break;
                        }

                        printf("\n\nOriginal: ");
                        show_list(first_list);

                        first_list = invert(first_list);
                        printf("\nAlterada: ");
                        show_list(first_list);
                        break;
                    case 2:
                        if(!secnd_list) {
                            printf("\n\nLista vazia.");
                            break;
                        }

                        printf("\n\nOriginal: ");
                        show_list(secnd_list);

                        secnd_list = invert(secnd_list);
                        printf("\nAlterada: ");
                        show_list(secnd_list);
                        break;
                    default: printf("\nNenhum comando valido existente. Tente novamente.");
                } else printf("\nValor do comando digitado invalido.");

                printf("\n\nPressione ENTER para continuar...");
                getchar();
                break;
            case 16: // Retorna o valor mais alto de uma lista
                printf("\nQual Lista deseja realizar a operacao:");
                printf("\nPrimeira Pilha ................... [1]");
                printf("\nSegunda Pilha .................... [2]");
                printf("\nEscolha: ");
                fgets(buffer, sizeof(buffer), stdin);
                if(checkInput(buffer, &option)) switch(option) {
                    case 1:
                        if(!first_list) {
                            printf("\n\nLista vazia.");
                            break;
                        }

                        printf("\n\nLista Completa: ");
                        show_list(first_list);
                        printf("\nMaior valor: %d", higher_value(first_list));
                        break;
                    case 2:
                        if(!secnd_list) {
                            printf("\n\nLista vazia.");
                            break;
                        }

                        printf("\n\nLista Completa: ");
                        show_list(secnd_list);
                        printf("\nMaior valor: %d", higher_value(secnd_list));
                        break;
                    default: printf("\nNenhum comando valido existente. Tente novamente.");
                } else printf("\nValor do comando digitado invalido.");

                printf("\n\nPressione ENTER para continuar...");
                getchar();
                break;
            case 17: // Clona os pares da pilha
                printf("\nQual Pilha realizar a Clonagem dos Pares:");
                printf("\nPrimeira Pilha ...................... [1]");
                printf("\nSegunda Pilha ....................... [2]");
                printf("\nEscolha: ");
                fgets(buffer, sizeof(buffer), stdin);
                if(checkInput(buffer, &option)) switch(option) {
                    case 1:
                        if(!first_stack) {
                            printf("\n\nPilha vazia.");
                            break;
                        }

                        printf("\n\nOriginal:\n");
                        show_stack(&first_stack);
                        clone_evens(&first_stack);
                        printf("\nAlterada:\n");
                        show_stack(&first_stack);
                        break;
                    case 2:
                        if(!secnd_stack) {
                            printf("\n\nPilha vazia.");
                            break;
                        }

                        printf("\n\nOriginal:\n");
                        show_stack(&secnd_stack);
                        clone_evens(&secnd_stack);
                        printf("\nAlterada:\n");
                        show_stack(&secnd_stack);
                        break;
                    default: printf("\nNenhum comando valido existente. Tente novamente.");
                } else printf("\nValor do comando digitado invalido.");

                printf("\n\nPressione ENTER para continuar...");
                getchar();
                break;
            case 0: executing = 0; break;
            default: printf("\n\nNenhum comando valido inexistente. Tente novamente."); break;
        }

    } while(executing);

    return 0;
}