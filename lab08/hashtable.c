#include "hashtable.h"

int HashEspalhamento (int chave, int bloco)
{
	return chave % bloco;
}

void construirHashTable (HashTable *hash, int bloco)
{
	hash -> bloco = bloco;
	hash -> ListaHash = (Lista*)malloc(bloco * sizeof(Lista));
	for (int i=0; i < bloco; i++)
		hash -> ListaHash[i].primeiro = NULL;  
}

void inserirPedra (HashTable *hash, char *pedra, int chave)
{
	int i = HashEspalhamento (chave, hash -> bloco);
	
	/* Verifica se a pedra vai ser inserida em uma lista ainda vazia */
	if (hash -> ListaHash[i].primeiro == NULL)
	{
		hash -> ListaHash[i].primeiro = (No*)malloc(sizeof(No));
		strcpy (hash -> ListaHash[i].primeiro -> pedra, pedra);
		hash -> ListaHash[i].primeiro -> chave = chave;
		hash -> ListaHash[i].primeiro -> ant = NULL;
		hash -> ListaHash[i].primeiro -> prox = NULL;
	}

	else
	{
		No *NovoNo = (No*)malloc(sizeof(No));
		strcpy (NovoNo->pedra, pedra);
		NovoNo -> chave = chave;
		NovoNo -> prox = hash -> ListaHash[i].primeiro;
		NovoNo -> ant = NULL;
		hash -> ListaHash[i].primeiro -> ant = NovoNo; 
		hash -> ListaHash[i].primeiro = NovoNo;
	}
}

void removerPedra (HashTable *hash, int chave)
{

	int i = HashEspalhamento (chave, hash -> bloco);
		
	/* Encontra nó referente a pedra que se deseja retirar */
	No *NoChave = EncontrarPosicao (hash, chave);

	/* Remoção da Pedra da HashTable */
	if (NoChave == NULL)
		return;

	if (NoChave -> ant == NULL){

		if (hash -> ListaHash[i].primeiro -> prox == NULL)
		{
			free(hash -> ListaHash[i].primeiro);
			hash -> ListaHash[i].primeiro = NULL;
			return;
		}

		No *NoSeg = hash -> ListaHash[i].primeiro -> prox;
		free (hash -> ListaHash[i].primeiro);
		hash -> ListaHash[i].primeiro = NoSeg;
		hash -> ListaHash[i].primeiro -> ant = NULL;
		return;
	}

	if (NoChave -> prox == NULL){
		NoChave -> ant -> prox = NULL;
		free(NoChave);
		return;
	}

	NoChave -> ant -> prox = NoChave -> prox;
	NoChave -> prox -> ant = NoChave -> ant;
	free(NoChave);	
}


void jogadaM (HashTable *hash, int *resultado)
{
	int chave;
	scanf ("%d", &chave);
	
	No* NoChave = EncontrarPosicao (hash, chave);
	
	if (NoChave == NULL)
		*resultado = 0;

	else
	{
		*resultado = 1;
		printf("%s\n", NoChave -> pedra);
	}
}

void jogadaP (HashTable *hash)
{
	int pedras;
	int chave;
	char pedra[NOME_MAX];

	scanf ("%d", &pedras);

	for (int j=0; j < pedras; j++)
	{
		scanf ("%d %s", &chave, pedra);
		inserirPedra (hash, pedra, chave);
	}
}


void jogadaT (HashTable *hash, int *vingador)
{
	int AfastaVingador;
	int pedras;
	int chave;

	scanf ("%d", &AfastaVingador);
	*vingador += AfastaVingador;

	scanf ("%d", &pedras);
	for (int j = 0; j < pedras; j++)
	{
		scanf ("%d", &chave);

		removerPedra (hash, chave);
	}

}

No* EncontrarPosicao (HashTable *hash, int chave)
{
	int i = HashEspalhamento (chave, hash -> bloco);
	No *NoChave = NULL;
	No *NoAtual = hash -> ListaHash[i].primeiro;
	
	//Encontrar de qual chave se trata
	if (hash -> ListaHash[i].primeiro == NULL)
		return NULL;

	while (NoAtual -> chave != chave && NoAtual != NULL)
	{
		NoAtual = NoAtual -> prox;
	}

	if (NoAtual -> chave == chave)
		NoChave  = NoAtual;
	
	return NoChave;
}


void Imprimir(Lista *lista)
{
	No *NoAtual = lista -> primeiro;
	if (NoAtual != NULL)
	{
		while (NoAtual != NULL)
		{
			printf("%d = %s", NoAtual -> chave, NoAtual -> pedra);
			NoAtual = NoAtual -> prox;
		}
	printf("\n");
	}
}


void limparHashTable(HashTable* hash)
{
    for (int i = 0; i < hash->bloco; i++)
	{
		if(hash -> ListaHash[i].primeiro == NULL)
			return;	
		
		if (hash -> ListaHash[i].primeiro -> prox == NULL)	
		{
			free(hash -> ListaHash[i].primeiro);
			hash -> ListaHash[i].primeiro = NULL;
			return;
		}

		No *NoSeg = hash -> ListaHash[i].primeiro -> prox;
		free (hash -> ListaHash[i].primeiro);
		hash -> ListaHash[i].primeiro = NoSeg;
		hash -> ListaHash[i].primeiro -> ant = NULL;
		}
}

