#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define MAX 60

// Projeto Lista sequencial e encadeada: Lista Alunos

typedef struct aluno{
	char nome[50];
	char rgm[20];
	struct Disciplina *disciplinas;
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

int deslocaDireita(Alunos * alunos, int pos) {
    int i;

    for (i=alunos->n + 1; i>pos; i--)
        alunos->vetor[i] = alunos->vetor[i-1];

    return 1;
}

int inserir (Alunos * alunos, int pos, Aluno dado) {
    if ( isCheia(alunos) || (pos > alunos->n + 1) || (pos < 0) )
        return 0;

    deslocaDireita(alunos, pos);
    alunos->vetor[pos] = dado;
    (alunos->n)++;
    return 1;
}

int inserirOrdenado(Alunos * alunos, Aluno dado) {
	if(isCheia(alunos))
		return 0;
	int compara(Aluno dado1, Aluno dado2);
	int pos = 0;
		
	while(pos <= alunos->n && compara(alunos->vetor[pos], dado) < 0)
		pos++;
		
	if(pos <= alunos->n)
		deslocaDireita(alunos, pos);
		
	alunos->vetor[pos] = dado;
	(alunos->n)++;
	
	return 1;
}

int deslocaEsquerda(Alunos * alunos, int pos) {
    int i;

    for (i=pos; i<(alunos->n); i++)
        alunos->vetor[i] = alunos->vetor[i+1];

    return 1;
}

// Função para remover um aluno por RGM
void remover_aluno_por_rgm(Alunos *alunos, char rgm[]) {
    int posicao = -1;
    // Encontrar a posição do aluno na lista usando o RGM
    for (int i = 0; i <= alunos->n; i++) {
        if (strcmp(alunos->vetor[i].rgm, rgm) == 0) {
            posicao = i;
            break;
        }
    }

    if (posicao != -1) {
        // Remover o aluno da lista
        for (int i = posicao; i < alunos->n; i++) {
            alunos->vetor[i] = alunos->vetor[i + 1];
        }
        alunos->n--;
        printf("Aluno com RGM %s removido com sucesso.\n", rgm);
    } else {
        printf("Aluno com RGM %s não encontrado.\n", rgm);
    }
}

int remover (Alunos * alunos, int pos) {
    if ( (pos > alunos->n) || (pos < 0) )
        return 0;

    deslocaEsquerda(alunos, pos);

    (alunos->n)--;
    return 1;
}

Aluno * getElemento(Alunos * alunos, int pos) {
    if ( (pos > alunos->n) || (pos < 0) )
        return 0;

    return &(alunos->vetor[pos]);
}

int compara(Aluno dado1, Aluno dado2) {
    return strcmp(dado1.rgm, dado2.rgm);
}

int getPosicao(Alunos * alunos, Aluno dado) {
    int i;
    
    for (i=0; i<=alunos->n; i++)
        if (compara(alunos->vetor[i], dado)==0)
            return i;

    return -1;
}

void mostrar(Alunos * alunos) {
	int	i;
	
	for (i = 0; i <= alunos->n; i++) {
		printf("\nAluno [%d] com: RGM: [%s] | Nome: [%s]\n", i + 1, alunos->vetor[i].rgm, alunos->vetor[i].nome);
	}
}

int buscaSequencial(Alunos * alunos, char rgm[]) {
    int i;
    for (i = 0; i <= alunos->n; i++) {
        if (strcmp(alunos->vetor[i].rgm, rgm) == 0) {
            printf("\n---RGM encontrado na posição %d.---\n", i + 1);
            return i;
        }
    }
    printf("RGM do aluno não existe.\n");
    return -1;
}

int lerNumero() { //função para ler a entrada do usuário
    
    int numero;
    scanf("%d", &numero);
    getchar();
    return numero;
    
}

void adicionarDisciplina(Aluno *aluno, const char nomeDisciplina[]){
	Disciplina *novaDisciplina = (Disciplina *)malloc(sizeof(Disciplina));
	if (novaDisciplina == NULL){
		printf("Erro ao adicionar disciplina.\n");
		return;
	}
	
	strcpy(novaDisciplina->nome, nomeDisciplina);
	novaDisciplina->proxima=NULL;
	
if (aluno->disciplinas == NULL) {
        aluno->disciplinas = novaDisciplina;
    } else {
        Disciplina *atual = aluno->disciplinas;
        while (atual->proxima != NULL) {
            atual = atual->proxima;
        }
        atual->proxima = novaDisciplina;
    }
}



int main (int argc, char *argv[]) {
	setlocale (LC_ALL, "portuguese");
	
	Alunos meusalunos;
	Aluno aluno;
	
	meusalunos = criar();
	
	int pos;
	int loop = 1;
	int numero = 0;
	char nomeBusca[20];
	
	while(loop == 1){
    system("cls");
	printf("\n\t\n\n");
	printf("1. Cadastrar alunos\n");
	printf("2. Listar alunos\n");
	printf("3. Buscar aluno\n");
	printf("4. Remover aluno\n");
	printf("5. Sair\n\n");
	printf("Digite o número da opção que deseja: ");
	numero = lerNumero();
    	
	switch (numero) {
            case 1:{
                printf("\n-----Cadastrando aluno-----\n");
                printf("\nInforme o nome: ");
                scanf("%s", aluno.nome);
                printf("Informe o RGM: ");
                scanf("%s", aluno.rgm);
                
                while (getchar() != '\n');
                
                char nomeDisciplina[50];
                printf("Informe a disciplina do aluno:\n");
                fgets(nomeDisciplina, sizeof(nomeDisciplina), stdin);
                strtok(nomeDisciplina, "\n"); 
                adicionarDisciplina(&aluno, nomeDisciplina);
                
                printf("Disciplina cadastrada com sucesso! Deseja adicionar mais disciplinas?\n");
                printf("1 - Sim\n");
                printf("2 - N�o\n");

                int opcao;
                scanf("%d", &opcao);
                while (opcao == 1) {
        
                while (getchar() != '\n');

                printf("Informe outra disciplina do aluno:\n");
                scanf("%s", nomeDisciplina);
                
                adicionarDisciplina(&aluno, nomeDisciplina);
                printf("Disciplina cadastrada com sucesso! Deseja adicionar mais disciplinas?\n");
                printf("1 - Sim\n");
                printf("2 - N�o\n");

                scanf("%d", &opcao);
               }

    printf("Cadastro realizado com sucesso! Deseja voltar ao menu?\n");
    printf("1 - Sim\n");
    printf("2 - N�o\n");

    scanf("%d", &opcao);

    if (opcao == 2) {
        break;
    }

    inserirOrdenado(&meusalunos, aluno);
    break;
}
            
            case 2:{
               	printf("\n-----Listando alunos-----\n");
                mostrar(&meusalunos);
				break;
			}
            case 3:{
                printf("\n-----Buscando aluno-----\n");
                printf("\nInforme o RGM que deseja buscar: ");
                scanf("%s", nomeBusca);
                buscaSequencial(&meusalunos, nomeBusca);
				break;
			}
			case 4:{
				printf("\n-----Removendo aluno-----\n");
				
				mostrar(&meusalunos);
				
				printf("\nInforme o RGM que deseja apagar: ");
                scanf("%s", nomeBusca);
   				remover_aluno_por_rgm(&meusalunos, nomeBusca);
                
                mostrar(&meusalunos);
				break;
			}
            case 5:{
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
		
		while (getchar() != '\n');
	}
	return 0;
}
