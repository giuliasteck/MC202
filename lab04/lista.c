#include "lista.h"

struct Lista mercados[MAX_MERCADOS];



No* EncontrarItem (Lista *lista, char *nome_item)
{
	No * NoAtual = lista -> primeiro;
	while(NoAtual != NULL)
	{
		if(strcmp(NoAtual -> produto.nome,nome_item)==0)
		{
			return NoAtual;
			break;
		}
		
		NoAtual = NoAtual -> prox;
	}

	return NoAtual;

}

void analisarString (char *stringVelha, char *novaString)
{
	int iVelho = 0;
	int iNovo = 0;
	char stringMontada[MAX_NOME];

	while(stringVelha[iVelho] != '\0')
	{
		if (stringVelha[iVelho] == '(' || stringVelha[iVelho] == ',' || stringVelha[iVelho] == ')')
		{
			iVelho ++;
			continue;
		}

		else
		{
			stringMontada[iNovo] = stringVelha[iVelho];
			iNovo ++;
			iVelho ++;
		}
	}
	stringMontada[iNovo] = '\0';
	strcpy(novaString, stringMontada);
}



void limpar (Lista *lista)
{
	No *NoAtual = lista -> primeiro, *temp;
	while (NoAtual != NULL)
	{
		temp = NoAtual;
		NoAtual = NoAtual -> prox;
		free(temp);
	}
	lista -> primeiro = NULL;
}

/**********************************************************/

void imprimirLista(Lista *lista)
{
	No *NoAtual = lista -> primeiro;
	if (NoAtual != NULL)
	{
		while (NoAtual != NULL)
		{
			printf("item: %s, quantidade: %d\n", NoAtual -> produto.nome, NoAtual ->produto.quantidade);

			NoAtual = NoAtual -> prox;
		}
	}
}

void juntarListas(Lista *lista_1, Lista *lista_2)
{
	int qntd2;
	No *NoAtual = lista_2 -> primeiro;

	for (NoAtual = lista_2 -> primeiro; NoAtual != NULL; NoAtual =NoAtual -> prox)
	{
		char* nome2 = NoAtual -> produto.nome;
		qntd2 = NoAtual -> produto.quantidade;
		No* ItemEncontrado = EncontrarItem(lista_1,nome2);


		if(ItemEncontrado != NULL)
		{
			ItemEncontrado -> produto.quantidade += qntd2;
		}

		else
		{
			adicionarFim(lista_1, NoAtual-> produto);
		}

	}

}

void trocarItens(Lista *lista_1, Lista *lista_2, char *nome_item1, char *nome_item2)
{
	No *No1 = EncontrarItem(lista_1, nome_item1);
	No *No2 = EncontrarItem(lista_2, nome_item2);

	Item temp= No1 -> produto;
	No1 -> produto = No2 -> produto;
	No2 -> produto = temp;
}

void adicionarFim(Lista *lista, Item item)
{
	No *NoAtual = lista -> primeiro;

	while(NoAtual != NULL && NoAtual -> prox != NULL)
	{
		NoAtual = NoAtual -> prox;
	}
	NoAtual -> prox = (No*)malloc(sizeof(No));
	NoAtual -> prox -> produto = item;
	NoAtual -> prox -> prox = NULL;
}

void adicionarAntes(Lista *lista, Item item, char *nome_item)
{
	No *NoItem = EncontrarItem(lista, nome_item);
	No *NoAtual = lista -> primeiro;

	if(NoItem == lista -> primeiro)
	{
		lista -> primeiro = (No*)malloc(sizeof(No));
		lista -> primeiro -> produto = item;
		lista -> primeiro -> prox = NoItem;
	}

	else
	{
		while(NoAtual != NULL)
		{
			if(NoAtual -> prox == NoItem)
			{
				NoAtual -> prox = (No*)malloc(sizeof(No));
				NoAtual -> prox -> produto = item;
				NoAtual -> prox -> prox = NoItem;
				break;	
			}
			NoAtual = NoAtual -> prox;
		}
	}
}

void adicionarDepois(Lista *lista, Item item, char *nome_item)
{
	No *NoItem = EncontrarItem(lista, nome_item);

	if (NoItem -> prox == NULL)
	{
		adicionarFim(lista, item);
	}

	else
	{
		No* temp = NoItem -> prox;
		NoItem -> prox = (No*)malloc(sizeof(No));
		NoItem -> prox -> produto = item;
		NoItem -> prox -> prox = temp;
	}
}

void diminuirQuantidade(Lista *lista, char *nome_item, int qtd)
{
	No *NoItem = EncontrarItem(lista, nome_item);

	NoItem -> produto.quantidade = NoItem -> produto.quantidade - qtd;

	if (NoItem -> produto.quantidade <= 0)
	{
		excluirItem(lista,nome_item);
	}
}

void excluirItem(Lista *lista, char *nome_item)
{
	No *NoAtual = lista -> primeiro;
	No *NoDepois = lista -> primeiro -> prox;

	if (EncontrarItem(lista, nome_item) == NULL)
	{
		return;
	}
		
	if(lista->primeiro->prox == NULL)
	{
		if(strcmp(lista->primeiro->produto.nome, nome_item)==0)
		{
			free(lista->primeiro);
			lista -> primeiro = NULL;
			return;
		}
	}

	if(strcmp(lista->primeiro->produto.nome, nome_item)==0)
	{
		No *temp = lista ->primeiro -> prox;
		free(lista->primeiro);
		NoAtual = lista -> primeiro;
		lista->primeiro = temp;
	}

	while(NoDepois != NULL)
	{
		if(strcmp(NoDepois->produto.nome, nome_item) == 0)
		{
			NoAtual-> prox = NoDepois -> prox;
			free(NoDepois);
			break;
		}
		NoAtual = NoAtual -> prox;
		NoDepois = NoDepois -> prox;
	}


		
}


void inverterLista(Lista *lista)
{
	int i = 0;
	int j=0;

	No *UltimoNo = lista -> primeiro;
	while (UltimoNo -> prox != NULL)
	{
		UltimoNo = UltimoNo -> prox;
	}

	
	No *NoRecorrente = lista -> primeiro;
	while(NoRecorrente != NULL)
	{
		if(NoRecorrente -> produto.quantidade < UltimoNo -> produto.quantidade)
		{
			NoRecorrente -> produto.quantidade += UltimoNo -> produto.quantidade;
		}
		NoRecorrente = NoRecorrente -> prox;
	}



	
	No *NoAntes = lista -> primeiro;

	while (NoAntes != NULL)
	{
		i++;
		NoAntes = NoAntes -> prox;
	}

	
	No *listaInversao = (No*)malloc(sizeof(No)*i);
	for(No *NoAtual = lista -> primeiro; NoAtual != NULL; NoAtual = NoAtual -> prox)
	{
		listaInversao[j] = *NoAtual;
		j++;
	}

	for(No* NoAtual = lista -> primeiro; NoAtual !=NULL; NoAtual = NoAtual -> prox)
	{
		NoAtual -> produto = listaInversao[j-1].produto;
		
		if(j == 1)
		{
			NoAtual -> prox = NULL;
			break;
		}
		j--;
	}

	free(listaInversao);
}


