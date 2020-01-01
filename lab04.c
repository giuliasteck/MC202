#include "lista.h"


int main()
{

	//Declarar vetor de listas ligadas
	struct Lista mercados[MAX_MERCADOS];

		for (int i=0; i<MAX_MERCADOS; i++)
		{	
			mercados[i].primeiro = NULL;
		}


		int N;
		scanf("%d", &N);
		
		for(int k=0; k<N; k++)
		{
			
			char email[MAX_NOME] = {0};
			scanf ("%s", email);

			if(email[0] == 'A')
			{
				Item item;
				int iMercado;
				char nome[MAX_NOME] = {0};
				char nomeItem[MAX_NOME] = {0};
				char quantidadeItem[MAX_NOME] = {0};
				char nomeItemNovo[MAX_NOME] = {0};
				char quantidadeItemNovo[MAX_NOME] = {0};
				
				scanf("%d", &iMercado);
				scanf("%s", nome);
				scanf("%s", nomeItem);
				scanf("%s", quantidadeItem);

				analisarString(quantidadeItem, quantidadeItemNovo);
				analisarString(nomeItem, nomeItemNovo);

				item.quantidade = atoi(quantidadeItemNovo);
				strcpy(item.nome, nomeItemNovo);
						
				adicionarAntes(&mercados[iMercado], item, nome);

			}
			
			if (email[0] == 'C')
			{
				Item item;
				char nomeItem[MAX_NOME] = {0};
				char quantidadeItem[MAX_NOME] = {0};
				char nomeItemNovo[MAX_NOME] = {0};
			   	char quantidadeItemNovo [MAX_NOME] = {0};

				scanf(" %s", nomeItem);
				scanf(" %s", quantidadeItem);

				analisarString(nomeItem, nomeItemNovo);
				analisarString(quantidadeItem, quantidadeItemNovo);

				item.quantidade = atoi(quantidadeItemNovo);
				strcpy(item.nome, nomeItemNovo);
				
				//CRIANDO LISTA
				
				for (int j=0; j<MAX_MERCADOS; j++)
				{
					if(mercados[j].primeiro == NULL)
					{
						mercados[j].primeiro= (No*)malloc(sizeof(No));
						mercados[j].primeiro -> produto = item;
						mercados[j].primeiro -> prox = NULL;
						j = MAX_MERCADOS;
					}
				}
			}

			if(email[0] == 'D')
			{

				Item item;
				int iMercado;
				char nome[MAX_NOME] = {0};
				char nomeItem[MAX_NOME] = {0};
				char quantidadeItem[MAX_NOME] = {0};
				char nomeItemNovo[MAX_NOME] = {0};
				char quantidadeItemNovo[MAX_NOME] = {0};

				scanf("%d", &iMercado);
				scanf("%s", nome);
				scanf("%s", nomeItem);
				scanf("%s", quantidadeItem);

				analisarString(quantidadeItem, quantidadeItemNovo);
				analisarString(nomeItem, nomeItemNovo);

				item.quantidade = atoi(quantidadeItemNovo);
				strcpy(item.nome, nomeItemNovo);

				adicionarDepois(&mercados[iMercado], item, nome);

			}


			if (email[0] == 'E')
			{
				int iMercado;
				char nome[MAX_NOME] = {0};
				int quantidade;

				scanf("%d", &iMercado);
				scanf("%s", nome);
				scanf("%d", &quantidade);

				diminuirQuantidade(&mercados[iMercado], nome, quantidade);
			}

			if (email[0] == 'F')
			{
				Item item;
				int iMercado;
				char nomeItem[MAX_NOME] = {0};
				char quantidadeItem[MAX_NOME+1] = {0};
				char nomeItemNovo[MAX_NOME] = {0};
			   	char quantidadeItemNovo [MAX_NOME] = {0};

				scanf("%d", &iMercado);
				scanf("%s", nomeItem);
				scanf("%s", quantidadeItem);

				analisarString(quantidadeItem, quantidadeItemNovo);
				analisarString(nomeItem, nomeItemNovo);

				item.quantidade = atoi(quantidadeItemNovo);
				strcpy(item.nome, nomeItemNovo);

				adicionarFim(&mercados[iMercado], item);
			}


			if (email[0] == 'I')
			{
				int index;
				scanf("%d", &index);

				inverterLista(&mercados[index]);
			
			}

			
			if (email[0] =='J')
			{
				int iMercado1, iMercado2;
				scanf("%d", &iMercado1);
				scanf ("%d", &iMercado2);

				juntarListas(&mercados[iMercado1], &mercados[iMercado2]);
				limpar(&mercados[iMercado2]);
			}

			if(email[0] == 'T')
			{
				int iMercado1, iMercado2;
				char nomeItem1[MAX_NOME], nomeItem2[MAX_NOME];
				
				scanf("%d", &iMercado1);
				scanf("%d", &iMercado2);
				scanf("%s", nomeItem1);
				scanf("%s", nomeItem2);

				trocarItens(&mercados[iMercado1], &mercados[iMercado2], nomeItem1, nomeItem2);
			}
			
			if(email[0] == 'X')
			{
				int iMercado;
				char nomeItem[MAX_NOME];

				scanf("%d", &iMercado);
				scanf("%s", nomeItem);

				excluirItem(&mercados[iMercado], nomeItem);
			}
			
			for (int i=0; i<MAX_MERCADOS; i++)
			{
				if(mercados[i].primeiro != NULL)
				{
					printf("Lista %d:\n", i);
					imprimirLista(&mercados[i]);
				}
			}

		
		}

		for (int i=0; i<MAX_MERCADOS; i++)
		{
			if(mercados[i].primeiro != NULL)
			{
				printf("Lista %d:\n", i);
				imprimirLista(&mercados[i]);
			}
		}
		
}

	
