#include <stdio.h>							   
#include <stdlib.h>
#include <string.h> //biblioteca necess�ria para a fun��o strcpy_s

struct musica { //registro das m�sicas
	char nomeMusica[50];
	char artista[50];
	double duracao; //dura��o armazenada como double (minutos.segundos) pois n�o ser�o efetuadas opera��es com os valores.
	struct musica* prox; //ponteiro para encadear o pr�ximo valor da lista
};

struct musica* Head; //cria��o do ponteiro Head, primeira musica da playlist

int menu() { //fun��o que implementa o menu
	int op, c;
//	system("Cls"); //caso queira limpar a tela do terminal. Desativado para tirar o print com todos os retornos do programa
	printf("\n##MENU##\n");
	printf("1.Inserir nova musica na playlist\n");
	printf("2.Exibir a playlist completa\n");
	printf("3.Sair\n");
	printf("Digite sua escolha: ");
	scanf_s("%d", &op);
	while ((c = getchar()) != '\n' && c != EOF) {} //limpeza de buffer do teclado.
//	system("Cls");
	return op;
}

void inserirMusica() { //fun��o que insere nova m�sica na playlist, sempre no final
	int c;
	struct musica* novaMusica;
	novaMusica = (struct musica*)malloc(sizeof(struct musica)); //aloca��o de mem�ria para a nova musica
	printf("\nInforme o nome da nova musica:\n");
	gets_s(novaMusica->nomeMusica);
	printf("Informe o artista da nova musica:\n");
	gets_s(novaMusica->artista);
	printf("Informe a duracao em minutos.segundos da nova musica:\n");
	scanf_s("%lf", &novaMusica->duracao);
	while ((c = getchar()) != '\n' && c != EOF) {} //limpeza de buffer do teclado.
	struct musica* ElementoVarredura;
	ElementoVarredura = (struct musica*)malloc(sizeof(struct musica)); //aloca��o de mem�ria para o elemento de varredura da fun��o

	if (Head == NULL) //se n�o houver nenhuma m�sica, a nova ser� a primeira (Head)
	{
		Head = novaMusica;
		Head->prox = NULL;
	}
	else //se j� houverem musicas na playlist, como � o caso, a �ltima ter� seu ponteiro atualizado, apontando para a nova m�sica, e esta ter� seu ponteiro null
	{
		ElementoVarredura = Head;
		while (ElementoVarredura->prox != NULL) {
			ElementoVarredura = ElementoVarredura->prox;
		}
		ElementoVarredura->prox = novaMusica;
		novaMusica->prox = NULL;
	}
	return;
}

void exibirPlaylis() { //fun��o que exibe as musicas da playlist
	printf("\n");
	struct musica* ElementoVarredura;
	ElementoVarredura = (struct musica*)malloc(sizeof(struct musica)); //aloca��o de mem�ria para o elemento de varredura da fun��o
	ElementoVarredura = Head;
	if (ElementoVarredura == NULL) { //caso n�o haja nenhuma m�sica
		return;
	}
	while (ElementoVarredura != NULL) { //enquanto o ponteiro n�o apontar para null, percorrer a lista exibindo os dados
		printf("Nome: ");
		printf("%s \n", ElementoVarredura->nomeMusica);
		printf("Artista: ");
		printf("%s \n", ElementoVarredura->artista);
		printf("Duracao (Minutos.Segundos): ");
		printf("%2.2lf \n \n", ElementoVarredura->duracao);
		ElementoVarredura = ElementoVarredura->prox;
	}
	printf("\n");

	system("pause");
	return;
}

int  main() { //fun��o main inicia criando duas m�sicas na playlist, indicando a primeira para o Head e encadeando a segunda, que aponta para null
	int op;
	struct musica* musica1;
	struct musica* musica2;
	musica1 = (struct musica*)malloc(sizeof(struct musica)); //aloca��o de mem�ria para a musica1
	strcpy_s(musica1->nomeMusica, "Main Title");
	strcpy_s(musica1->artista, "Ramin Djawadi");
	musica1->duracao = 1.46;
	Head = musica1;

	musica2 = (struct musica*)malloc(sizeof(struct musica)); //aloca��o de mem�ria para a musica2
	strcpy_s(musica2->nomeMusica, "Geralt of Rivia");
	strcpy_s(musica2->artista, "Sonya Belousova, Giona Ostinelli");
	musica2->duracao = 1.52;
	musica2->prox = NULL;
	musica1->prox = musica2;
	
	while (1) {
		op = menu();
		switch (op) { //chamada das fun��es do programa, conforme o retorno da fun��o menu
		case 1:
			inserirMusica();
			break;
		case 2:
			exibirPlaylis();
			break;
		case 3:
			return 0;
		default:
			printf("Valor invalido, escolha outro.\n");
		}
	}
	system("pause");
	return 0;
}