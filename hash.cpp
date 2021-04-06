#include <stdio.h>
#include <stdlib.h>
#include <string.h> //biblioteca necessária para a função strcpy_s

struct Aluno //registro do aluno
{
	int chave;
	unsigned long int ru; //ru armazenado como unsigned long int para armazenar o número de 7 digitos
	char nome[30];
	char email[30];
	Aluno* prox;
};

struct Tabela //registro da tabela hash
{
	int Tamanho;
	struct Aluno** ListaChave;
};

Tabela* TabelaHash;

int menu() { //função do menu
	int op, c;
//	system("Cls");//caso queira limpar a tela do terminal. Desativado para tirar o print com todos os retornos do programa
	printf("\n#MENU#\n");
	printf("1. Pesquisar aluno\n");
	printf("2. Sair\n");
	printf("Digite sua escolha: ");
	scanf_s("%d", &op);
	while ((c = getchar()) != '\n' && c != EOF) {} // limpa o buffer do teclado
//	system("Cls");//caso queira limpar a tela do terminal. Desativado para tirar o print com todos os retornos do programa
	return op;
}

int CriarHash(unsigned long int num) //função que cria o hash a partir do ru pelo método da divisão
{
	return (num % 23); //Foi escolhido o tamanho de vetor 23 para evitar colisões
}

void InserirHash(unsigned long int ru, char* nome, char* email, struct Tabela* TabelaHash) //função que cria instancias novas de alunos, e adiciona o hash a tabela
{
	int pos;
	pos = CriarHash(ru);
	Aluno* NovoAluno; //cria a nova instancia de aluno
	NovoAluno = (struct Aluno*)malloc(sizeof(struct Aluno));
	NovoAluno->chave = pos; //adiciona os dados do novo aluno
	NovoAluno->ru = ru;
	strcpy_s(NovoAluno->nome, nome);
	strcpy_s(NovoAluno->email, email);
	NovoAluno->prox = NULL;

	NovoAluno->prox = TabelaHash->ListaChave[pos]; //liga o aluno a tabela hash
	TabelaHash->ListaChave[pos] = NovoAluno;
	return;
}

void PesquisarTabela(unsigned long int ru, struct Tabela* TabelaHash)//função que busca na tabela se um aluno está cadastrado recebendo o ru como parâmetro
{
	int pos;
	pos = CriarHash(ru);
	Aluno* AlunoBuscado = TabelaHash->ListaChave[pos];
	if (TabelaHash->ListaChave[pos] == NULL || AlunoBuscado->ru != ru) { //esta condição verifica se a posição não está vazia ou se o ru buscado não é uma colisão com outro aluno já cadastrado
		printf("Aluno nao encontrado\n");
	}
	else {
		printf("Aluno encontrado na posicao %d da tabela hash\n", pos); //se o aluno está cadastrado, imprime no terminal todos os seus dados
		printf("RU: %lu\n", AlunoBuscado->ru);
		printf("Nome: %s\n", AlunoBuscado->nome);
		printf("E-mail: %s\n", AlunoBuscado->email);
		return;
	}
}

int main() { //função main
	int op, c;
	unsigned long int ru;
	char n1[] = "Dorsey Mcneill"; char em1[] = "dorsey@yahoo.com"; //iniciando o programa com informações de 10 alunos
	char n2[] = "Rodrigo Mccallum"; char em2[] = "rodrigo@gmail.com";
	char n3[] = "Meridith Hindley"; char em3[] = "meridith@hotmail.com";
	char n4[] = "Marci Blackburn"; char em4[] = "marci@hotmail.com";
	char n5[] = "Deetta Leach"; char em5[] = "deetta@gmail.com";
	char n6[] = "Quiana Steadman"; char em6[] = "quiana@yahoo.com";
	char n7[] = "Norbert Walton"; char em7[] = "norbert@yahoo.com";
	char n8[] = "Ernest Spooner"; char em8[] = "ernest@gmail.com";
	char n9[] = "Thomas Fleming"; char em9[] = "thomas@hotmail.com";
	char n10[] = "Joao Nogueira"; char em10[] = "jffn_04@outlook.com";
	Tabela* TabelaHash = (struct Tabela*)malloc(sizeof(struct Tabela)); //aloca memória para a tabela hash, define o tamanho e aloca as posições para os alunos
	TabelaHash->Tamanho = 23;
	TabelaHash->ListaChave = (struct Aluno**)malloc(23 * sizeof(struct Aluno*));
	for (int i = 0; i < 23; i++)
		TabelaHash->ListaChave[i] = NULL;
	InserirHash(7840909, n1, em1, TabelaHash);//insere os dados dos 10 alunos na tabela hash
	InserirHash(9676896, n2, em2, TabelaHash);
	InserirHash(7282375, n3, em3, TabelaHash);
	InserirHash(4517322, n4, em4, TabelaHash);
	InserirHash(3923465, n5, em5, TabelaHash);
	InserirHash(9310846, n6, em6, TabelaHash);
	InserirHash(9145939, n7, em7, TabelaHash);
	InserirHash(4106366, n8, em8, TabelaHash);
	InserirHash(4805706, n9, em9, TabelaHash);
	InserirHash(3338731, n10, em10, TabelaHash);

	while (1)
	{
		op = menu();//chama o menu para oferecer as opções de busca ou término do programa
		switch (op)
		{
		case 1:
			printf("\n Digite o ru do aluno que deseja pesquisar:\n ");
			scanf_s("%d", &ru);
			while ((c = getchar()) != '\n' && c != EOF) {} // limpa o buffer do teclado
			PesquisarTabela(ru, TabelaHash);
			system("pause");
			break;
		case 2:
			return 0;
			break;
		default:
			printf("Valor invalido, escolha outro\n");
			break;
		}
	}
	return 0;
}