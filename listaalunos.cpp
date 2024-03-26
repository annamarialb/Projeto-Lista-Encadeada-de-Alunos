#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define MAX 10

// Projeto Lista sequencial e encadeada: Lista Alunos

typedef struct aluno{
	char nome[50];
	int rgm;
}Aluno;

typedef struct alunos{
	Aluno vetor[MAX];
	int n;
}Alunos;

typedef struct Disciplina {
    char nome[50];
    struct Disciplina *proxima;
} Disciplina;


Alunos criar() {
	Alunos alunos;
	
	alunos.n = -1;
	
	return alunos;
}

int isVazia(Alunos * alunos) {
	return (alunos->n == -1);
}

int isCheia(Alunos * alunos) {
	return (alunos->n == MAX-1);
}

int getTamanho(Alunos * alunos) {
	return alunos->n + 1;
}

int lerNumero() { //função para ler a entrada do usuário
    
    int numero;
    scanf("%d", &numero);
    getchar();
    return numero;
    
}

int main (int argc, char *argv[]) {
	setlocale (LC_ALL, "portuguese");
	
	Alunos meusalunos;
	
	meusalunos = criar();
	
	int loop = 1;
	int numero = 0;
	
	while(loop == 1){
    	system("cls");
	printf("\n\t\n\n");
	printf("1. Cadastrar alunos\n");
	printf("2. Listar alunos\n");
	printf("3. Buscar alunos\n");
	printf("4. Sair\n\n");
	printf("Digite o número da opção que deseja: ");
	numero = lerNumero();
    	
	switch (numero) {
            case 1:{
                printf("Cadastrar aluno: ");
		break;
		}
            case 2:{
               	printf("Listar alunos: ");
		break;
		}
            case 3:{
                printf("Buscar alunos: ");
		break;
		}
            case 4:{
                printf("\nSaindo...");
                loop = 0;
		break;
		}
	    default:{
		printf("\nOpção Inválida!\n");
		break;
		}
        }
        if (loop != 0) {
		printf("\nDigite '1' para voltar ao menu, ou '0' para encerrar o programa.\n");
		loop = lerNumero();
	}
	}
	return 0;
}
