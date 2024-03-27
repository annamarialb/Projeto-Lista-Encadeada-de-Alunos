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

//lista sequencia: ALUNOS
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
	
	int (*compara)(Aluno, Aluno);
	int pos = 0;
	compara = compara;
		
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


void remover_aluno_por_rgm(Alunos *alunos, char rgm[]) {
    int posicao = -1;
   
    for (int i = 0; i <= alunos->n; i++) {
        if (strcmp(alunos->vetor[i].rgm, rgm) == 0) {
            posicao = i;
            break;
        }
    }

    if (posicao != -1) {
        
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

void remover_disciplina(Aluno *aluno, const char *nome_disciplina) {
    Disciplina *atual = aluno->disciplinas;
    Disciplina *anterior = NULL;
    int disciplina_encontrada = 0; // Variável para indicar se a disciplina foi encontrada
    
    
    while (atual != NULL) {
        if (strcmp(atual->nome, nome_disciplina) == 0) {
            disciplina_encontrada = 1;
            if (anterior == NULL) {
                // Se a disciplina a ser removida for a primeira da lista
                aluno->disciplinas = atual->proxima;
            } else {
                anterior->proxima = atual->proxima;
            }
            free(atual);
            printf("Disciplina %s removida com sucesso do aluno %s.\n", nome_disciplina, aluno->nome);
            return;
        }
        anterior = atual;
        atual = atual->proxima;
    }

    
    if (!disciplina_encontrada) {
        printf("Disciplina %s não encontrada para o aluno %s.\n", nome_disciplina, aluno->nome);
    }
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
		
		 if (alunos->vetor[i].disciplinas != NULL) {
            printf("Disciplinas:");
		
		Disciplina *disciplina_atual = alunos->vetor[i].disciplinas;
        printf("Disciplinas:");
        while (disciplina_atual != NULL) {
            printf(" %s", disciplina_atual->nome);
            disciplina_atual = disciplina_atual->proxima;
            
        }
        printf("\n");
	}
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


void inserir_disciplina(Aluno *aluno, const char *nome_disciplina) {
    Disciplina *nova_disciplina = (Disciplina*)malloc(sizeof(Disciplina));
    if (nova_disciplina == NULL) {
        printf("Erro: Não foi possível realocar memória para disciplina.\n");
        return;
    }
    strcpy(nova_disciplina->nome, nome_disciplina);
    nova_disciplina->proxima = aluno->disciplinas;
    
    if (aluno->disciplinas == NULL) {
        aluno->disciplinas = nova_disciplina;
    } else {
        // Percorre a lista até o último nó
        Disciplina *atual = aluno->disciplinas;
        while (atual->proxima != NULL) {
            atual = atual->proxima;
        }
        // Adiciona a nova disciplina ao final da lista
        atual->proxima = nova_disciplina;
    }
}

int lerNumero() { 
    
    int numero;
    scanf("%d", &numero);
    getchar();
    return numero;
    
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
	char nome_disciplina[100];
	
	while(loop == 1){
    system("cls");
	printf("\n\t\n\n");
	printf("1. Cadastrar alunos\n");
	printf("2. Listar alunos\n");
	printf("3. Buscar aluno\n");
	printf("4. Remover aluno\n");
	printf("5. Remover disciplina do aluno \n");
	printf("6. Sair\n\n");
	printf("Digite o número da opção que deseja: ");
	numero = lerNumero();
    
	char nomeDisciplina[50];	
	switch (numero) {
            case 1:{
                printf("\n-----Cadastrando aluno-----\n");
                printf("\nInforme o nome: ");
               fgets(aluno.nome, sizeof(aluno.nome), stdin);
                aluno.nome[strcspn(aluno.nome, "\n")] = 0; // Remover o caractere de nova linha
                printf("Informe o RGM: ");
                scanf("%s", aluno.rgm);
                 getchar(); // Limpar o buffer de entrada
                
                aluno.disciplinas = NULL;
                inserirOrdenado(&meusalunos, aluno);
                
                // Inserindo a primeira disciplina para o aluno
                printf("Informe o nome da disciplina: ");
                fflush(stdin); // Consumir o caractere de nova linha pendente
                fgets(nome_disciplina, sizeof(nome_disciplina), stdin);
                
				nome_disciplina[strcspn(nome_disciplina, "\n")] = 0; // Remover o caractere de nova linha
                inserir_disciplina(&meusalunos.vetor[meusalunos.n], nome_disciplina);
                
                // Perguntando se deseja inserir mais disciplinas
                int opcao_disciplina = 1;
                while (opcao_disciplina) {
                    printf("Deseja inserir mais uma disciplina para este aluno? (1-Sim | 0-Não): ");
                    opcao_disciplina = lerNumero();
                    if (opcao_disciplina) {
                        printf("Informe o nome da disciplina: ");
                        fflush(stdin);
                        fgets(nome_disciplina, sizeof(nome_disciplina), stdin);
                        
                    }
            	}
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
				printf("\n-----Removendo disciplina de um aluno-----\n");
                printf("Informe o RGM do aluno: ");
                scanf("%s", nomeBusca);
                int posicao = buscaSequencial(&meusalunos, nomeBusca);
                if (posicao != -1) {
                    printf("Informe o nome da disciplina a ser removida: ");
                    scanf("%s", nomeDisciplina);
                    remover_disciplina(&meusalunos.vetor[posicao], nomeDisciplina);
                } else {
                    printf("Aluno não encontrado.\n");
                }
				break;
			}
            case 6:{
                printf("\nSaindo...");
                loop = 0;
				break;
			}
	    	default:{
				printf("\n Opção inválida! \n");
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
