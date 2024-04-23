#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LIVROS "livros.dat"
#define CLIENTES "clientes.dat"
#define VENDAS "vendas.dat"

struct reg_livro{
	int codigo;
	char titulo[50];
	float preco;
};

struct reg_cliente{
	int codigo;
	char nome[50];
	char email[50];
	char fone[15];
};

struct reg_venda{
	int codvenda;
	int codcliente;
	int codlivro;
	int qtde;
};


void cadastrarLivro(){
	FILE *fplivros;
	struct reg_livro livro;
	char op;
	
	//Fazer a Entrada dos dados do Livro
	printf("\nDigite o Codigo: ");
	fflush(stdin); scanf("%i",&livro.codigo);
	
	printf("Titulo: ");
	fflush(stdin); gets(livro.titulo);
	
	printf("Preco: ");
	fflush(stdin); scanf("%f",&livro.preco);	
	
	printf("\nSalvar Livro(S/N)? ");
	fflush(stdin); scanf("%c",&op);
	
	if ((op=='n')||(op=='N')){
		printf("\nOperacao Cancelada!");
		return;  //retorna para o Menu Principal
	}
	
	//Abrir o Arquivo
	fplivros = fopen("livros.dat","ab");
	
	//Salvar no Arquivo
	fwrite(&livro,sizeof(livro),1,fplivros);
	
	fclose(fplivros);
	
	printf("\nLivro Cadastrado com Sucesso.");
	
}//Fim cadastrarLivro()

void listarLivros(){
	FILE *fplivros;
	struct reg_livro livro;
	
	//Abrir o Arquivo de Livros
	fplivros = fopen(LIVROS,"rb");
	
	printf("\n# # # # #   Livraria Tech Info   # # # # #");
	printf("\n     Relatorio de Todos os Livros");
	printf("\nCodigo Titulo                                   Preco");
	//Ler registro por registro e mostrar na tela
	while (fread(&livro,sizeof(livro),1,fplivros)==1){	
		printf("\n%-6i %-40s %.2f",livro.codigo,livro.titulo,livro.preco);
  }
	
	//Fechar o Arquivo
	fclose(fplivros);
}//Fim listarLivros()

void consultarLivroPeloCodigo(){
	FILE *fplivros;
	struct reg_livro livro;
	int cod, achou=0;
	
	//Solicitar o Código do Livro a ser Localizado
	printf("\nDigite o Codigo do Livro a ser Localizado: ");
	fflush(stdin); scanf("%i",&cod);
	
	//Abrir o Arquivo
	fplivros = fopen(LIVROS,"rb");
	
	//Ler registro por registro para localizar o Livro
	while ((achou==0)&&(fread(&livro,sizeof(livro),1,fplivros)==1)){
		printf("\nEntrou");
		if (livro.codigo==cod){ //Achei o Livro
			printf("\nCodigo: %i",livro.codigo);
			printf("\nTitulo: %s",livro.titulo);
			printf("\nPreco: %5.2f",livro.preco);
			achou=1;
		}
	}
	
	if (achou==0){
		printf("\nNenhum livro com este codigo foi localizado!");
	}
	
	//Fechar o Arquivo
	fclose(fplivros);
	
	printf("\nfechou o Arquivo.");
	
}//Fim consultarLivroPeloCodigo()

void consultarLivroPeloTitulo(){
	FILE *fplivros;
	struct reg_livro livro;
	int achou=0;
	char tit[50];
	
	//Solicitar o Titulo do Livro a ser Localizado
	printf("\nDigite o Titulo do Livro a ser Localizado: ");
	fflush(stdin); gets(tit);
	
	//Abrir o Arquivo
	fplivros = fopen(LIVROS,"rb");
	
	//Ler registro por registro para localizar o Livro
	while ((achou==0)&&(fread(&livro,sizeof(livro),1,fplivros)==1)){
		if (strcmp(livro.titulo,tit)==0){ //Achei o Livro
			printf("\nCodigo: %i",livro.codigo);
			printf("\nTitulo: %s",livro.titulo);
			printf("\nPreco: %5.2f",livro.preco);
			achou=1;
		}
	}
	
	if (achou==0){
		printf("\nNenhum livro com este codigo foi localizado!");
	}
	
	//Fechar o Arquivo
	fclose(fplivros);
	
}//Fim consultarLivroPeloTitulo()

void consultarLivroPalavraChaveTitulo(){
	FILE *fplivros;
	struct reg_livro livro;
	int achou=0;
	char palavra[50];
	
	//Solicitar a Palavra-chave do Livro a ser Localizado
	printf("\nDigite Palavra-Chave: ");
	fflush(stdin); gets(palavra);
	
	//Abrir o Arquivo
	fplivros = fopen(LIVROS,"rb");
	
		printf("\n# # # # #   Livraria Tech Info   # # # # #");
	printf("\n     Relatorio Livros com a palavra: %s no titulo:");
	printf("\nCodigo Titulo                                   Preco");
	//Ler registro por registro para localizar o Livro
	while (fread(&livro,sizeof(livro),1,fplivros)==1){
		if (strstr(livro.titulo,palavra)!=NULL){ //Achei o Livro
			printf("\n%-6i %-40s %.2f",livro.codigo,livro.titulo,livro.preco);
			achou=1;
		}
	}
	
	if (achou==0){
		printf("\nNenhum livro com esta Palavra-chave foi localizado!");
	}
	
	//Fechar o Arquivo
	fclose(fplivros);
	
}//Fim consultarLivroPalavraChaveTitulo()

void alterarLivro(){
	FILE *fplivros;
	struct reg_livro livro;
	int cod,achou=0;
	char conf;
	
	//Solicitar o codigo do Livro a ser Alterado
	printf("\nDigite o codigo do livro a ser alterado: ");
	fflush(stdin); scanf("%i",&cod);
	
	//Localizar o Livro
	//Abrir o Arquivo
	fplivros = fopen(LIVROS,"rb+");
	
	//Ler registro por registro para localizar o Livro
	while ((achou==0)&&(fread(&livro,sizeof(livro),1,fplivros)==1)){
		if (livro.codigo==cod){ //Achei o Livro
			printf("\nCodigo: %i",livro.codigo);
			printf("\nTitulo: %s",livro.titulo);
			printf("\nPreco: %5.2f",livro.preco);
			achou=1;
		}
	}
	
	if (achou==0){
		printf("\nNenhum livro com este codigo foi localizado!");
		fclose(fplivros);
		return; //Volta ao menu principal
	}
		
	printf("\nConfirma Livro?(S/N) ");
	fflush(stdin); scanf("%c",&conf);
	
	if ((conf=='N')||(conf=='n')){
		printf("\nLivro Nao confirmado!");
		fclose(fplivros);
		return; //Retorna ao menu Principal
	}
		
	//solicitar os novos Dados
	printf("\nDeseja alterar o Titulo?(S/N) ");
	fflush(stdin); scanf("%c",&conf);
	if ((conf=='S')||(conf=='s')){
		printf("\nDigite o Novo Titulo: ");
		fflush(stdin); gets(livro.titulo);
	}
	
	printf("\nDeseja alterar o Preco?(S/N) ");
	fflush(stdin); scanf("%c",&conf);
	if ((conf=='S')||(conf=='s')){
		printf("\nDigite o Novo Preco: ");
		fflush(stdin); scanf("%f",&livro.preco);
	}
	//Gravar a alteração no Arquivo
	//Voltar o ponteiro para o registro Anterior
	fseek(fplivros,-sizeof(livro),1);
	
	//Gravar o registro
	fwrite(&livro,sizeof(livro),1,fplivros);
	
	//Fechar o Arquivo
	fclose(fplivros);
	
	printf("\nLivro alterado com sucesso.");
	
}//Fim alterarLivro()

void excluirLivro(){
	FILE *fplivros, *fplivrosnew;
	struct reg_livro livro;
	int cod,achou=0;
	char conf;
	
	//Solicitar o codigo do livro a ser Excluído
	printf("\nDigite o codigo do livro a ser Excluido: ");
	fflush(stdin); scanf("%i",&cod);
	
	//Localizar o Livro
	//Abrir o Arquivo
	fplivros = fopen(LIVROS,"rb+");
	
	//Ler registro por registro para localizar o Livro
	while ((achou==0)&&(fread(&livro,sizeof(livro),1,fplivros)==1)){
		if (livro.codigo==cod){ //Achei o Livro
			printf("\nCodigo: %i",livro.codigo);
			printf("\nTitulo: %s",livro.titulo);
			printf("\nPreco: %5.2f",livro.preco);
			achou=1;
		}
	}
	
	fclose(fplivros);
	
	if (achou==0){
		printf("\nNenhum livro com este codigo foi localizado!");
		fclose(fplivros);
		return; //Volta ao menu principal
	}
		
	printf("\nConfirma Exclusao?(S/N) ");
	fflush(stdin); scanf("%c",&conf);
	
	if ((conf=='N')||(conf=='n')){
		printf("\nExclusao Cancelada!");
		fclose(fplivros);
		return; //Retorna ao menu Principal
	}	
	
	//Excluir o registro do Arquivo - Exclusão Física
	fplivros = fopen(LIVROS,"rb");
	fplivrosnew = fopen("livrosnew.dat","wb");
	
	while(fread(&livro,sizeof(livro),1,fplivros)==1){
		if (livro.codigo!=cod)
			fwrite(&livro,sizeof(livro),1,fplivrosnew);
	}
	
	fclose(fplivros);
	fclose(fplivrosnew);
	
	system("Del livros.dat");  //Exluir o arquivo antigo
	system("ren livrosnew.dat livros.dat"); //Renomear o novo arquivo
	
	printf("\nLivro excluido com sucesso.");
}//Fim excluirLivro()

void cadastrarCliente(){
		FILE *fpclientes;
	struct reg_cliente cliente;
	char op;
	
	//Fazer a Entrada dos dados do cliente
	printf("\nDigite o Codigo: ");
	fflush(stdin); scanf("%i",&cliente.codigo);
	
	printf("Nome: ");
	fflush(stdin); gets(cliente.nome);
	
	printf("Email: ");
	fflush(stdin); gets(cliente.email);

	printf("Fone: ");
	fflush(stdin); gets(cliente.fone);
	
	printf("\nSalvar Cliente(S/N)? ");
	fflush(stdin); scanf("%c",&op);
	
	if ((op=='n')||(op=='N')){
		printf("\nOperacao Cancelada!");
		return;  //retorna para o Menu Principal
	}
	
	//Abrir o Arquivo
	fpclientes = fopen(CLIENTES,"ab");
	
	//Salvar no Arquivo
	fwrite(&cliente,sizeof(cliente),1,fpclientes);
	
	fclose(fpclientes);
	
	printf("\nCliente Cadastrado com Sucesso.");
}//Fim cadastrarCliente()

void listarClientes(){
	FILE *fpclientes;
	struct reg_cliente cliente;
	
	//Abrir o Arquivo de Clientes
	fpclientes = fopen(CLIENTES,"rb");
	
	printf("\n# # # # #   Livraria Tech Info   # # # # #");
	printf("\n     Relatorio de Todos os Clientes");
	printf("\nCodigo Nome                         Email                     Fone");
	//Ler registro por registro e mostrar na tela
	while (fread(&cliente,sizeof(cliente),1,fpclientes)==1){	
		printf("\n%-6i %-28s %-25s %s",cliente.codigo,cliente.nome,cliente.email,cliente.fone);
  }
	
	//Fechar o Arquivo
	fclose(fpclientes);
}//Fim listarClientes()

struct reg_cliente localizarCliente(int codcli){
	FILE *fpcliente;
	struct reg_cliente cliente;
	int achou=0;
	
	fpcliente = fopen(CLIENTES,"rb");
	
	while((achou==0)&&(fread(&cliente,sizeof(cliente),1,fpcliente)==1)){
		if(cliente.codigo==codcli){
			achou=1;
		}
	}
	fclose(fpcliente);
	
	if (achou!=0){ //Localizou o cliente
		return cliente;
	}else{//NÃO localizou o Cliente
		cliente.codigo=-1;
	}
	
}//Fim localizarCliente()

struct reg_livro localizarLivro(int codliv){
	FILE *fplivro;
	struct reg_livro livro;
	int achou=0;
	
	fplivro = fopen(LIVROS,"rb");
	
	while((achou==0)&&(fread(&livro,sizeof(livro),1,fplivro)==1)){
		if(livro.codigo==codliv){
			achou=1;
		}
	}
	fclose(fplivro);
	
	if (achou!=0){ //Localizou o livro
		return livro;
	}else{//NÃO localizou o livro
		livro.codigo=-1;
	}
	
}//Fim localizarLivro()

void efetuarVenda(){
	FILE *fpvendas;
	struct reg_venda venda;
	struct reg_livro livro;
	struct reg_cliente cliente;
	int codcli, codliv;
	char opcao;
	
	//Solicitar o codigo da Venda
	printf("\nDigite o Codigo da Venda: ");
	fflush(stdin); scanf("%i",&venda.codvenda);
	
  //Solicitar o codigo do Cliente
  printf("\nDigite o codigo do Cliente: ");
  fflush(stdin); scanf("%i",&codcli);
  
  //Localizar o cliente e pedir confirmação
  cliente = localizarCliente(codcli);
  if (cliente.codigo==-1){
  	printf("\nCliente NAO Localizado!!!");
  	return; //Retorna ao Menu Principal
	}
	
	printf("\nCodigo: %i - Nome: %s",cliente.codigo,cliente.nome);
	printf("\nConfirma Cliente?(S/N) ");
	fflush(stdin); scanf("%c",&opcao);
	if ((opcao=='N')||(opcao=='n')){
		printf("\nCliente NAO Confirmado.");
		return; //Retorna ao Menu Principal
	}
  //Solicitar o código do Livro 
  printf("\nDigite o codigo do Livro: ");
  fflush(stdin); scanf("%i",&codliv);
  
  //Localizar o Livro e pedir confirmação
  livro = localizarLivro(codliv);
  if (livro.codigo==-1){
  	printf("\nLivro NAO Localizado!!!");
  	return; //Retorna ao Menu Principal
	}
	
	printf("\nCodigo: %i Titulo: %s Preco: %.2f",livro.codigo,livro.titulo, livro.preco);
	printf("\nConfirma Livro?(S/N) ");
	fflush(stdin); scanf("%c",&opcao);
	if ((opcao=='N')||(opcao=='n')){
		printf("\nLivro NAO Confirmado.");
		return; //Retorna ao Menu Principal
	}  
  
  //Solicitar qtde
  printf("\nDigite a qtde: ");
  fflush(stdin); scanf("%i",&venda.qtde);
  
  //Confirmar Venda
  printf("\nGravar Venda?(S/N) ");
  fflush(stdin); scanf("%c",&opcao);
  if ((opcao=='N')||(opcao=='n')){
		printf("\nOperacao Cancelada!");
		return; //Retorna ao Menu Principal
	}  
  
  //Gravar Venda
  venda.codcliente = cliente.codigo;
  venda.codlivro = livro.codigo;
  
	fpvendas = fopen(VENDAS,"ab");	
	fwrite(&venda,sizeof(venda),1,fpvendas);
	fclose(fpvendas);
	
	printf("\nVenda realizada com sucesso.");
}//Fim efetuarVenda()

void listarVendas(){
	FILE *fpvendas;
	struct reg_venda venda;
	
	fpvendas = fopen(VENDAS,"rb");
	
	printf("\nListagem das Vendas:\n");
	
	while (fread(&venda,sizeof(venda),1,fpvendas)==1){
		printf("\nCodigo Venda: %i",venda.codvenda);
		printf("\nCodigo Cliente: %i",venda.codcliente);
		printf("\nCodigo Livro: %i",venda.codlivro);
		printf("\nQtde: %i",venda.qtde);
		printf("\n---------------------------------------------");
	}
	fclose(fpvendas);
	
}//Fim listarVendas()

main(){
	int op;
	
	do{
		
		printf("\n\n\n############ Livraria Tech Info ###############");
		printf("\n1) Cadastrar Livro");
		printf("\n2) Listar Todos Livros");
		printf("\n3) Consultar Livro pelo Codigo");
		printf("\n4) Consultar Livro pelo Titulo");
		printf("\n5) Consultar Livro por palavra-chave no Titulo");
		printf("\n6) Alterar dados do Livro");
		printf("\n7) Excluir um Livro");


		printf("\n8) Cadastrar Cliente");
		printf("\n9) Listar Todos os Clientes");

		printf("\n10) Efetuar Venda");
		printf("\n11) Listar Vendas");

		
		printf("\n12) Listar Livro(s) mais Caro(s)"); // TODO
		printf("\n13) Aumentar o Preço dos Livros"); // TODO
		printf("\n14) Listar Todas as compras de um Cliente"); // TODO
		printf("\n15) Mostar todos os Clientes que Compraram um Livro"); // TODO
		printf("\n0) Sair");
		
		printf("\nOpcao-> ");
		fflush(stdin); scanf("%i",&op);
		
		switch(op){
			case 1: //Cadastrar um Novo Livro
					cadastrarLivro();
					break;
			case 2: //Listar todos os Livros
					listarLivros();
					break;
			case 3: //Conusltar Livro pelo Código
					consultarLivroPeloCodigo();
					break;
			case 4: //Conusltar Livro pelo Titulo
					consultarLivroPeloTitulo();
					break;
			case 5: //Conusltar Livro por palavra-chave no Titulo
					consultarLivroPalavraChaveTitulo();
					break;
			case 6: //Alterar dados do Livro
					alterarLivro();
					break;
			case 7: //Excluir um Livro
					excluirLivro();
					break;
			case 8: //Cadastrar um Cliente
					cadastrarCliente();
					break;
			case 9: //Listar clientes
					listarClientes();
					break;
			case 10: //Efetuar Venda
					efetuarVenda();
					break;
			case 11: //Listar Vendas
					listarVendas();
					break;
		}
		
	}while (op!=0);
	
	
	
}//Fim main()