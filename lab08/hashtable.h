#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_MAX 50

int vingador;

/*Definição da Lista Ligada que será
 * utilizada para lidar com os confron-
 * tos eventuais na HashTable */

typedef struct No
{
	int chave;
	char pedra [NOME_MAX];
	struct No *ant, *prox;
} No;

typedef struct Lista
{
	No* primeiro;
} Lista;

typedef struct HashTable
{
	int bloco;
	Lista *ListaHash;
} HashTable;

//void RemoverPrimeiro (Lista *lista);

/********** FUNÇÕES PARA MANIPULAÇÃO DA HASHTABLE **********/

/* Função da HashTable */
int HashEspalhamento (int chave, int blocos);

/* Função para alocar memória necessária para a HashTable */
void construirHashTable (HashTable *hash, int blocos);

/* Insere uma pedra e sua respectiva chave na HashTable */
void inserirPedra (HashTable *hash, char *pedra, int chave);

/* Remove uma pedra de uma determinada chave */
void removerPedra (HashTable *hash, int chave);

/******* FUNÇÕES PARA EXECUTAR AS JOGADAS **********/

/* Executa a jogada M, que verifica se a pedra que o
 * mago pediu está presente na HashTable ou não */
void jogadaM (HashTable *hash, int *resultado);

/* Executa a jogada P, na qual algumas pedras podem
 * ser trazidas de volta */
void jogadaP (HashTable *hash);

/* Executa a jogada T, na qual algumas pedras são
 * removidas */
void jogadaT (HashTable *hash, int *vingador);

/************** FUNÇÕES AUXILIARES ******************/

/* Encontra o nó referente à uma chave, facilitando 
 * a localização na HashTablede elementos desejados */
No *EncontrarPosicao (HashTable *hash, int chave);

/* Utilizada para debugar programa */
void imprimir (Lista *lista);

/* Desaloca a memória da HashTable - 
 * utilizada no fim
 * da execução do programa */
void limparHashTable(HashTable *hash);



