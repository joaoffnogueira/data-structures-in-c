#include <stdio.h>							   
#include <stdlib.h>
#include <string.h> //biblioteca necessária para a função strcpy_s

struct musica { //registro das músicas
	char nomeMusica[50];
	char artista[50];
	double duracao; //duração armazenada como double (minutos.segundos) pois não serão efetuadas operações com os valores.
	struct musica* prox; //ponteiro para encadear o próximo valor da lista
};

struct musica* Head; //criação do ponteiro Head, primeira musica da playlist

int menu() { //função que implementa o menu
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

void inserirMusica() { //função que insere nova música na playlist, sempre no final
	int c;
	struct musica* novaMusica;
	novaMusica = (struct musica*)malloc(sizeof(struct musica)); //alocação de memória para a nova musica
	printf("\nInforme o nome da nova musica:\n");
	gets_s(novaMusica->nomeMusica);
	printf("Informe o artista da nova musica:\n");
	gets_s(novaMusica->artista);
	printf("Informe a duracao em minutos.segundos da nova musica:\n");
	scanf_s("%lf", &novaMusica->duracao);
	while ((c = getchar()) != '\n' && c != EOF) {} //limpeza de buffer do teclado.
	struct musica* ElementoVarredura;
	ElementoVarredura = (struct musica*)malloc(sizeof(struct musica)); //alocação de memória para o elemento de varredura da função

	if (Head == NULL) //se não houver nenhuma música, a nova será a primeira (Head)
	{
		Head = novaMusica;
		Head->prox = NULL;
	}
	else //se já houverem musicas na playlist, como é o caso, a última terá seu ponteiro atualizado, apontando para a nova música, e esta terá seu ponteiro null
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

void exibirPlaylis() { //função que exibe as musicas da playlist
	printf("\n");
	struct musica* ElementoVarredura;
	ElementoVarredura = (struct musica*)malloc(sizeof(struct musica)); //alocação de memória para o elemento de varredura da função
	ElementoVarredura = Head;
	if (ElementoVarredura == NULL) { //caso não haja nenhuma música
		return;
	}
	while (ElementoVarredura != NULL) { //enquanto o ponteiro não apontar para null, percorrer a lista exibindo os dados
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

int  main() { //função main inicia criando duas músicas na playlist, indicando a primeira para o Head e encadeando a segunda, que aponta para null
	int op;
	struct musica* musica1;
	struct musica* musica2;
	musica1 = (struct musica*)malloc(sizeof(struct musica)); //alocação de memória para a musica1
	strcpy_s(musica1->nomeMusica, "Main Title");
	strcpy_s(musica1->artista, "Ramin Djawadi");
	musica1->duracao = 1.46;
	Head = musica1;

	musica2 = (struct musica*)malloc(sizeof(struct musica)); //alocação de memória para a musica2
	strcpy_s(musica2->nomeMusica, "Geralt of Rivia");
	strcpy_s(musica2->artista, "Sonya Belousova, Giona Ostinelli");
	musica2->duracao = 1.52;
	musica2->prox = NULL;
	musica1->prox = musica2;
	
	while (1) {
		op = menu();
		switch (op) { //chamada das funções do programa, conforme o retorno da função menu
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