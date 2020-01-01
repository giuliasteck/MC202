#include <stdio.h>
#include<string.h>
#include <stdlib.h>

#define MAX_MERCADOS 30
#define MAX_NOME 60

typedef struct Item {
char nome[MAX_NOME];
int quantidade;
} Item;

typedef struct No {
struct No *prox;
Item produto;
} No;

typedef struct Lista {
No *primeiro;
} Lista;

void imprimirLista(Lista *lista);

void juntarListas(Lista *lista_1, Lista *lista_2);

void trocarItens(Lista *lista_1, Lista *lista_2, char *nome_item1, char *nome_item2);

void adicionarFim(Lista *lista, Item item);

void adicionarAntes(Lista *lista, Item item, char *nome_item);

void adicionarDepois(Lista*lista, Item item, char *nome_item);

void diminuirQuantidade(Lista *lista, char *nome_item, int qtd);

void excluirItem(Lista *lista, char *nome_item);

void inverterLista(Lista *lista);


/************************************************************/

No* EncontrarItem (Lista *lista, char* nome_item);

void analisarString (char *StringVelha, char *novaString);

void limpar (Lista *lista);
