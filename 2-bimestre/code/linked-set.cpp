#include <stdio.h>
#include <stdlib.h>

struct no{
	int info;
	struct no *prox;
};

struct no * inserirNoInicio(struct no *L,int v){
	struct no *p;
	
	//Alocar espaço de memória para o novo nó
	p = (struct no *) malloc(sizeof(struct no));
	
	//Coloca a informação no novo nó
	p->info = v;
	
	//Fazer o Encadeamento do novo nó no início da Lista
	p->prox = L;
	
	//Fazer o L apontar para o novo nó que passará a ser o primeiro
	L = p;
	
	return L;
	
}//Fim inserirNoInicio()

void mostrarLista(struct no *L){
	struct no *p;
	
	if (L==NULL){
		printf("Lista Vazia!");
		return;
	}
	
	p = L; //Aponta p para o primeiro nó da Lista	
	while(p!=NULL){
		printf("%i-> ",p->info);
		p = p->prox; //Passa o p para o próximo nó
	}
}//Fim mostrarLista()

struct no * inserirNoFim(struct no *L,int v){
	struct no *n, *p;
	
	n = (struct no *) malloc(sizeof(struct no));
	
	n->info = v; //Coloca a informação no novo nó
	n->prox = NULL; //Coloca NULL, pois vai ser o último nó
	
	if (L==NULL){ //Lista Vazia
		L = n; //Faz L apontar para o novo nó que será o últimoe também o primeiro
		return L;
	}
	
	//Fazer o Encadeamento do novo nó
	
	//Percorrer a Lista para encontrar o último nó
	p = L; //Aponta o p para o primeiro nó
	while(p->prox!=NULL){
		p = p->prox;
	}
	
	p->prox = n; //Faz o encadeamento do novo nó
	
	return L;
}//Fim inserirNoFim()

struct no * removerDoInicio(struct no *L, int *v){
	
    struct no *p = L;
    
	
	
}//Fim removerDoInicio()

main(){
	struct no *Lista;
	int op,val;
	
	Lista = NULL; //Lista Vazia
	
	do {
		printf("\n\n # # # #  Lista Encadeada  # # # #");
		printf("\n# 1) Inserir no Inicio da Lista    #");
		printf("\n# 2) Mostrar Lista                 #");
		printf("\n# 3) Inserir no Fim da Lista       #");
		printf("\n# 4) Remover do Inicio da Lista    #");
		
		printf("\n# 0) Sair                          #");
		printf("\nOpcao-> ");
		
		fflush(stdin); scanf("%i",&op);
		switch(op){
			case 1: //Inserir no Inicio da Lista
				printf("\nInserir no Inicio: ");
				printf("\nDigite o Valor a ser Inserido: ");
				fflush(stdin); scanf("%i",&val);
				Lista = inserirNoInicio(Lista,val);
				break;
			case 2: //Mostrar a Lista
			  printf("\nLista-> ");
				mostrarLista(Lista);
				break;
			case 3: //Inserir no Fim da Lista
				printf("\nInserir no Fim: ");
				printf("\nDigite o Valor a ser Inserido: ");
				fflush(stdin); scanf("%i",&val);	
				Lista = inserirNoFim(Lista,val);
				break;		
			case 4: //Remover do Início da Lista
				Lista = removerDoInicio(Lista,&val);
				printf("\nValor removido: %i",val);
				break;
		}
	}while (op!=0);
	
}//Fim main
