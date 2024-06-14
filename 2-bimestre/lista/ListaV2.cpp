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
	struct no *p;
	
	//Colocar em v a informação do nó que será removido
	*v = L->info;
	
	//Guarda em p o endereço do nó que será removido
	p = L;
	
	//Fazer o L apontar para o segundo nó, que passará a ser o primeiro
	L = L->prox;
	
	//Liberar espaço de memória do nó sendo removido
	free(p);
	
	return L;
	
}//Fim removerDoInicio()

struct no * removerDoFim(struct no *L,int *v){
	struct no *p, *q;
	
	//Localizar o último nó da Lista, o qual será removido
	p = L;
	while (p->prox!=NULL)
			p = p->prox; //Anda o p
	
	//Pegar a informação do nó que será removido
	*v = p->info;
	
	if (L==p){//Lista só tem 1 nó
		L=NULL;
	}else{//Lista tem 2 ou mais nós
			//Fazer o Encadeamento - Colocar NULL no penúltimo nó 
			q = L;
			while (q->prox!=p)
					q = q->prox; //Posiciona q no nó antes do p
					
			q->prox = NULL;
	}
	//Libera espaço de memória do nó sendo removido
	free(p);
	
	return L;
	
}//Fim removerDoFim()

struct no * localizarRemover(struct no *L,int v){
		struct no *p, *q;
		
	//Localizar o nó que contém o valor a ser removido
	p = L;
	while((p!=NULL)&&(p->info!=v)){
			p = p->prox;
	}
	
	if (p==NULL){//Não encontrou um nó que  contém o valor procurado
		printf("\nValor NAO localizado!");
		return L;
	}
	
	//Se encontrou o nó com o valor, o p está apontando para ele
	if (p==L){ //O nó a ser removido é o primeiro da Lista
		L = p->prox; //Faz o L apontar para o segundo nó
	}else{ //O nó a ser removido está entre dois outros nós ou está no final da Lista
		q = L; //Aponta q para o primeiro nó
		while (q->prox!=p)
				q = q->prox; //Posiciona q no nó anterior ao p
		
		q->prox = p->prox; //Faz o encadeamento
	}
			
	free(p); //Libera espaço de memória
	printf("\nInformacao removida com sucesso.");
	return L;
	
}//Fim localizarRemover()

struct no * inserirOrdemCrescente(struct no *L,int v){
	struct no *n,*p,*q;
	
	//Alocar espaço de memória para o novo nó
	n = (struct no *) malloc(sizeof(struct no));
	n->info = v;
	
	if (L==NULL){ //Lista Vazia
		n->prox = NULL;
		L=n;
		return L;
	}
	
	//Localizar a posição onde vou inserir o novo nó
	p = L;
	while ((p->prox!=NULL)&&(p->info<v))
			p = p->prox;
	
	if (p->info<v){ //p parou no último nó e tenho que inserir depois (no fim)
		p->prox = n;
		n->prox = NULL;
	}else if (p==L){ //p aponta para o primeiro nó e tenho que inserir no Inicio
		n->prox = p;
		L = n;
	} else {//p aponta para um nó que contém um valor maior do que o valor que 
					//tenho que inserir. Portanto, tenho que inserir antes do p
		q = L;
		while (q->prox!=p) //posiciona q no nó anterior ao p
				q = q->prox;
				
		//Faz o encadeamento do novo nó entre dois nós		
		q->prox = n;
		n->prox = p; 
	}
	return L;
	
}//Fim inserirOrdemCrescente()

int comprimentoLista(struct no *L){
		struct no *p;
		int cont=0;
	
	p = L; //Aponta p para o primeiro nó da Lista	
	while(p!=NULL){
		cont++;
		p = p->prox; //Passa o p para o próximo nó
	}
	
	return cont;
}//Fim comprimentoLista()

int existe(struct no *L, int v){
	struct no *p;
	
	p=L;
	while ((p!=NULL)&&(p->info!=v)){
		p = p->prox; //Anda o p
	}
	
	if (p==NULL){ //Não achou
		return 0;
	}else{
		return 1;
	}
}//Fim existe()

int iguais(struct no *L1, struct no *L2){
	struct no *p, *q;
	
	if (comprimentoLista(L1)!=comprimentoLista(L2)){
		return 0; //As listas NÃO são iguais
	}
	
	p=L1;
	q=L2;
	
	while ((p!=NULL)&&(p->info==q->info)){
			p = p->prox;
			q = q->prox;
	}
			
	if (p==NULL){
		return 1; //Listas IGUAIS
	}else{
		return 0; //Listas NÃO IGUAIS
	}
}//Fim iguais()

main(){
	struct no *Lista, *Lista1;
	int op, opcao,val;
	
	Lista = NULL; //Lista Vazia
	Lista1 = NULL; //Lista Vazia
	
	do {
		printf("\n\n # # # #  Lista Encadeada  # # # #");
		printf("\n# 1) Inserir no Inicio da Lista    #");
		printf("\n# 2) Mostrar Lista                 #");
		printf("\n# 3) Inserir no Fim da Lista       #");
		printf("\n# 4) Remover do Inicio da Lista    #");
		printf("\n# 5) Remover do Fim da Lista       #");
		printf("\n# 6) Remover o no que contem um valor#");
		printf("\n# 7) Inserir em ordem Crescente    #");
		printf("\n# 8) Comprimento da Lista          #");
		printf("\n# 9) Existe um valor na Lista?     #");
		printf("\n#10) Verificar Listas sao Iguais   #");
		
		printf("\n# 0) Sair                          #");
		printf("\nOpcao-> ");
		
		fflush(stdin); scanf("%i",&op);
		switch(op){
			case 1: //Inserir no Inicio da Lista
				printf("\nInserir no Inicio: ");
				printf("\nDigite o Valor a ser Inserido: ");
				fflush(stdin); scanf("%i",&val);
				printf("Inserir em qual Lista(0-Lista, 1-Lista1): ");
				fflush(stdin); scanf("%i",&opcao);
				if (opcao==0)
					Lista = inserirNoInicio(Lista,val);
				else
					Lista1 = inserirNoInicio(Lista1,val);
				break;
			case 2: //Mostrar a Lista
			  printf("\nLista-> ");
				mostrarLista(Lista);
			  printf("\nLista1-> ");
				mostrarLista(Lista1);				
				break;
			case 3: //Inserir no Fim da Lista
				printf("\nInserir no Fim: ");
				printf("\nDigite o Valor a ser Inserido: ");
				fflush(stdin); scanf("%i",&val);	
				printf("Inserir em qual Lista(0-Lista, 1-Lista1): ");
				fflush(stdin); scanf("%i",&opcao);
				if (opcao==0)
					Lista = inserirNoFim(Lista,val);
				else
					Lista1 = inserirNoFim(Lista1,val);
				break;		
			case 4: //Remover do Início da Lista
				if (Lista==NULL){
					printf("\nLista Vazia. Impossivel remover!");
				}else{
					Lista = removerDoInicio(Lista,&val);
					printf("\nValor removido: %i",val);
				}
				break;
			case 5: //Remover do Fim da Lista
				if (Lista==NULL){
					printf("\nLista Vazia. Impossivel remover!");
				}else{
					Lista = removerDoFim(Lista,&val);
					printf("\nValor removido: %i",val);
				}
				break;			
			case 6: //Remover o nó que contém um determinado valor
				if (Lista==NULL){
					printf("\nLista Vazia. Impossivel remover!");
				}else{
					printf("\nDigite o valor a ser removido: ");
					fflush(stdin); scanf("%i",&val);				
					Lista = localizarRemover(Lista,val);
				}
				break;	
			case 7: //Inserir um valor em ordem crescente
				printf("\nInserir em Ordem Crescente: ");
				printf("\nDigite o Valor a ser Inserido: ");
				fflush(stdin); scanf("%i",&val);	
				Lista = inserirOrdemCrescente(Lista,val);
				break;													
			case 8: //Comprimento de uma lista
				printf("\nComprimento da lista Lista: %i",comprimentoLista(Lista));
				printf("\nComprimento da lista Lista1: %i",comprimentoLista(Lista1));
				break;
			case 9: //Existe um valor na Lista?
				printf("\nDigite o Valor a ser Verificado: ");
				fflush(stdin); scanf("%i",&val);	
				if (existe(Lista,val)){
					printf("\nO valor %i existe na Lista",val);
				}else{
					printf("\nO valor %i NAO existe na Lista",val);
				}		
				break;	
			case 10: //Verificar se duas Listas são Iguais
				if (iguais(Lista,Lista1)){
					printf("\nAs Listas SAO iguais.");
				}else{
					printf("\nAs Listas NAO sao iguais!");
				}
				break;
		}
	}while (op!=0);
	
}//Fim main
