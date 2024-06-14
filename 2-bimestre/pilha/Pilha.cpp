#include <stdio.h>
#include <stdlib.h>

struct no{
	int info;
	struct no *prox;
};

void push(struct no **P,int v){
	struct no *n;
	
	//Alocar espaço de memória para o novo nó
	n = (struct no *) malloc(sizeof(struct no));
	
	//Coloca a informação no novo nó
	n->info = v;
	
	//Fazer o Encadeamento do novo nó no início da Lista
	n->prox = *P;
	
	//Fazer o L apontar para o novo nó que passará a ser o primeiro
	*P = n;
	
}//Fim push()

int pop(struct no **P){
	struct no *p;
	int v;
	
	//Colocar em v a informação do nó que será removido
	v = (*P)->info;
	
	//Guarda em p o endereço do nó que será removido
	p = *P;
	
	//Fazer o P apontar para o segundo nó, que passará a ser o primeiro
	*P = (*P)->prox;
	
	//Liberar espaço de memória do nó sendo removido
	free(p);
	
	return v;
	
}//Fim pop()

void media(struct no **p) {
	struct no *aux = NULL;
	int val, cont = 0, sum = 0;
	float media;
	
	while(*p!=NULL) {
		val = pop(p);
		sum += val;
		cont++;

		push(&aux, val);
	}

	media = sum/cont;
	cont = 0;
	
	printf("Media dos valores: %.2f", media);

	while(aux!=NULL) {
		val = pop(&aux);
		if(val > media) {
			if(!cont) printf("\n\nMaiores que a Media:");
			printf("\n%d", val);
			cont++;
		}
		push(p, val);
	}
	
	if(!cont) printf("\nNenhum dos valores e maior que media");
} // Fim media

// printf("%s", CLEAR);
// printf("\n-------------- Trabalho P2 -------------");
// printf("\nMostrar Lista ..................... [01]");   // ok
// printf("\nInserir no inicio da Lista ........ [02]");   // ok
// printf("\nInserir no Fim da Lista ........... [03]");   // ok
// printf("\nInserir em Ordem Crescente ........ [04]");   // ok

// printf("\nRealizar um Push em uma das Listas  [05]");   // ok
// printf("\nRealizar um Pop em uma das Listas . [06]");   // ok

// printf("\nRemover do Inicio da Lista ........ [07]");   // ok
// printf("\nRemover do Fim da Lista ........... [08]");   // ok
// printf("\nRemover um Valor da Lista ......... [09]");   // ok

// printf("\nComprimento da Lista .............. [10]");   // ok
// printf("\nProcurar Valor na Lista ........... [11]");   // ok
// printf("\nComparar duas Listas .............. [12]");   // ok
// printf("\nMostrar Pilha ..................... [13]");   // ok

// printf("\nCriar Pilha impar e par ........... [14]");   // todo

void mostrarPilha(struct no **P){
	struct no *Paux=NULL; //Pilha auxiliar
	int val,cont=0;
	
	while (*P!=NULL){
		val = pop(P);  //Retira da Pilha Original
		if (cont==0){
				printf("%i\n",val);
		}else{
				printf("        %i\n",val);
		}
		push(&Paux,val);  //Coloca na Pilha Auxiliar
		cont++;
	}	

	while(Paux!=NULL){
		val = pop(&Paux);  //Retira da Pilha Auxiliar
		push(P,val);  //Coloca na Pilha Original
	}

}//Fim mostrarPilha()


main(){
	printf("\e[1;1H\e[2J");

	struct no *Pilha;
	int op,val;
	
	Pilha = NULL; //Pilha Vazia
	
	do {
		printf("\n\n# # # # #    P i l h a    # # # # #");
		printf("\n# 1) Inserir na Pilha (Push)       #");
		printf("\n# 2) Mostrar Pilha                 #");
		printf("\n# 3) Remover da Pilha (Pop)        #");
		printf("\n# 4) Valores maiores que a Media   #");
		printf("\n# 0) Sair                          #");
		printf("\nOpcao-> ");
		
		fflush(stdin); scanf("%i",&op);
		printf("\e[1;1H\e[2J");
		switch(op){
			case 1: //Inserir na Pilha
				printf("\nInserir na Pilha: ");
				printf("\nDigite o Valor a ser Inserido: ");
				fflush(stdin); scanf("%i",&val);
				push(&Pilha,val);
				break;
			case 2: //Mostrar a Pilha
			  printf("\nPilha-> ");
				mostrarPilha(&Pilha);
				break;
			case 3: //Remover da Pilha
				if (Pilha==NULL){
					printf("\nPilha Vazia. Impossivel remover!");
				}else{
					val = pop(&Pilha);
					printf("\nValor removido: %i",val);
				}
				break;
			case 4: // calcular media
				if(Pilha==NULL) {
					printf("\nPilha Vazia");
				} else {
					media(&Pilha);
				}
		}

	}while (op!=0);
	
}//Fim main
