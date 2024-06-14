#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct no{
	char nome[30];
	float altura;
	struct no *prox;
};

struct no * inserirNoInicio(struct no *L,char nome[30],float altura){
	struct no *p;
	
	//Alocar espaço de memória para o novo nó
	p = (struct no *) malloc(sizeof(struct no));
	
	//Coloca a informação no novo nó
	strcpy(p->nome,nome);
	p->altura = altura;
	
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
		printf("(%s,%.2f)-> ",p->nome,p->altura);
		p = p->prox; //Passa o p para o próximo nó
	}
}//Fim mostrarLista()

struct no * inserirNoFim(struct no *L,char nome[30],float altura){
	struct no *n, *p;
	
	n = (struct no *) malloc(sizeof(struct no));
	
	strcpy(n->nome,nome); //Coloca a informação no novo nó
	n->altura = altura;
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

struct no * removerDoInicio(struct no *L, char nome[30],float *altura){
	struct no *p;
	
	//Colocar em v a informação do nó que será removido
	strcpy(nome,L->nome);
	*altura = L->altura;
	
	//Guarda em p o endereço do nó que será removido
	p = L;
	
	//Fazer o L apontar para o segundo nó, que passará a ser o primeiro
	L = L->prox;
	
	//Liberar espaço de memória do nó sendo removido
	free(p);
	
	return L;
	
}//Fim removerDoInicio()

struct no * removerDoFim(struct no *L,char nome[30],float *altura){
	struct no *p, *q;
	
	//Localizar o último nó da Lista, o qual será removido
	p = L;
	while (p->prox!=NULL)
			p = p->prox; //Anda o p
	
	//Pegar a informação do nó que será removido
	strcpy(nome,p->nome);
	*altura = p->altura;
	
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


int nroAtletas(struct no *L){
		struct no *p;
		int cont=0;
	
	p = L; //Aponta p para o primeiro nó da Lista	
	while(p!=NULL){
		cont++;
		p = p->prox; //Passa o p para o próximo nó
	}
	
	return cont;
}//Fim comprimentoLista()

void exibeMaiores(struct no *L,float altMin){
	struct no *p;
	
	p = L;
	
	printf("\n\nAtletas com altura Maior que %.2f",altMin);
	printf("\nNome            - Altura");
	while (p!=NULL){
		if (p->altura>altMin){
			printf("\n%-15s - %.2f",p->nome,p->altura);
		}
		p = p->prox;
	}
	
}//Fim exibeMaiores()

void dividirLista(struct no *LAtletas,struct no **LMenor,struct no **LMaior,float altura){
	struct no *p;
	
	p = LAtletas;
	while (p!=NULL){
		if (p->altura<=altura){
			//Inserir na lista LMenor
			*LMenor = inserirNoFim(*LMenor,p->nome,p->altura);
		}else{
			//Inserir na Lista LMaior
			*LMaior = inserirNoFim(*LMaior,p->nome,p->altura);
		}
		p = p->prox;
	}
	
}//Fim dividirLista()

void dividirListaInLoco(struct no *LAtletas,struct no **LMenor,struct no **LMaior,float altura){
	struct no *p, *pmaior, *pmenor;
	
	p = LAtletas;

	while (p!=NULL){
		if (p->altura<=altura){ //Atleta com altura menor-> inserir na LMenor
			if (*LMenor==NULL){ //estou inserindo o primeiro na LMenor
				*LMenor = p;
				pmenor = p;
			}else{ //Já tem nó na LMenor
				pmenor->prox = p;
				pmenor = p;
			}		
		}else{ //Inserir na LMaior
			if (*LMaior==NULL){ //estou inserindo o primeiro na LMaior
				*LMaior = p;
				pmaior = p;
			}else{ //Já tem nó na LMaior
				pmaior->prox = p;
				pmaior = p;
			}					
		}		
		p = p->prox;
	}
	pmenor->prox = NULL; //Finaliza a LMenor
	pmaior->prox = NULL; //Finaliza a LMaior
	
}//Fim dividirListaInLoco()

main(){
	struct no *LAtletas, *LMaior, *LMenor;
	char nome[30];
	float altura;
	int op;
	
	LAtletas = NULL; //Lista Vazia
	LMenor = NULL;
	LMaior = NULL;
	
	do {
		printf("\n\n # # # #  Lista Encadeada  # # # #");
		printf("\n# 1) Inserir no Inicio da Lista    #");
		printf("\n# 2) Mostrar Lista                 #");
		printf("\n# 3) Inserir no Fim da Lista       #");
		printf("\n# 4) Remover do Inicio da Lista    #");
		printf("\n# 5) Remover do Fim da Lista       #");
		printf("\n# 6) Nro de Atletas                #");
		printf("\n# 7) Exibe Atletas maiores que uma altura #");
		printf("\n# 8) Dividir a Lista em Menor ou Maior que uma altura");
		printf("\n# 9) Dividir a Lista em Menor ou Maior que uma altura(in loco)");
		
		printf("\n# 0) Sair                          #");
		printf("\nOpcao-> ");
		
		fflush(stdin); scanf("%i",&op);
		switch(op){
			case 1: //Inserir no Inicio da Lista
				printf("\nInserir no Inicio: ");
				printf("\nDigite o Nome do Atleta: ");
				fflush(stdin); gets(nome);
				printf("Digite a Altura do Atleta:");
				fflush(stdin); scanf("%f",&altura);
				LAtletas = inserirNoInicio(LAtletas,nome,altura);
				break;
			case 2: //Mostrar a Lista
			  printf("\nLAtletas-> ");
				mostrarLista(LAtletas);
				break;
			case 3: //Inserir no Fim da Lista
				printf("\nInserir no Fim: ");
				printf("\nDigite o Nome do Atleta: ");
				fflush(stdin); gets(nome);
				printf("Digite a Altura do Atleta:");
				fflush(stdin); scanf("%f",&altura);
				LAtletas = inserirNoFim(LAtletas,nome,altura);
				break;		
			case 4: //Remover do Início da Lista
				if (LAtletas==NULL){
					printf("\nLista Vazia. Impossivel remover!");
				}else{
					LAtletas = removerDoInicio(LAtletas,nome,&altura);
					printf("\nNome do Atleta removido: %s",nome);
					printf("\nAltura do Atleta removido: %.2f",altura);
				}
				break;
			case 5: //Remover do Fim da Lista
				if (LAtletas==NULL){
					printf("\nLista Vazia. Impossivel remover!");
				}else{
					LAtletas = removerDoFim(LAtletas,nome,&altura);
					printf("\nNome do Atleta removido: %s",nome);
					printf("\nAltura do Atleta removido: %.2f",altura);
				}
				break;					
			case 6: //Nro de Atletas
				printf("\nNro de Atletas: %i",nroAtletas(LAtletas));
				break;
			case 7: //Exibe Maiores que uma altura
				printf("\nDigite a altura minima: ");
				fflush(stdin); scanf("%f",&altura);
				exibeMaiores(LAtletas,altura);
				break;
			case 8: //Dividir a Lista em Menor e Maior que uma altura
				printf("\nDigite a altura: ");
				fflush(stdin); scanf("%f",&altura);
				dividirLista(LAtletas,&LMenor,&LMaior,altura);
			  printf("\nLAtletas-> ");
				mostrarLista(LAtletas);
			  printf("\nLMenor-> ");
				mostrarLista(LMenor);
			  printf("\nLMaior-> ");
				mostrarLista(LMaior);												
				break;
			case 9: //Dividir a Lista em Menor e Maior que uma altura (in loco)
							//Sem criar novos nós nas novas Listas
				printf("\nDigite a altura: ");
				fflush(stdin); scanf("%f",&altura);
				dividirListaInLoco(LAtletas,&LMenor,&LMaior,altura);
			  printf("\nLAtletas-> ");
				mostrarLista(LAtletas);
			  printf("\nLMenor-> ");
				mostrarLista(LMenor);
			  printf("\nLMaior-> ");
				mostrarLista(LMaior);												
				break;
		}
	}while (op!=0);
	
}//Fim main
