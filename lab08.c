/******************************************************
 *  		Giulia Steck - 173458             
 *  		   MC202 - TURMA G
 * Entrada: O programa recebe informações sobre
 * a distância do vingador e as pedras disponíveis
 * para abrir o portal, tal como o número máximo de
 * pedras que poderão utilizadas durante a partida.
 * A partir desses dados, executa as jogadas M, P e T.
 *
 * Saída: Avalia se será possível os jogadores abrirem
 * um portal. Isso ocorre se eles conseguirem todas as
 * pedras que forem sendo requisitadas pelo mago e rea-
 * lizarem isso antes do vingador alcançar o portal.
 *
 ******************************************************/

#include "hashtable.h"

int main()
{
	int vingador, maximoPedras, pedrasAtuais, jogadas;
	scanf ("%d", &vingador);
	scanf ("%d", &maximoPedras);
	scanf ("%d", &pedrasAtuais);

	HashTable hashtable;

	construirHashTable (&hashtable, maximoPedras);

	for (int i = 0; i < pedrasAtuais; i++)
	{
		int chave;
		char pedra[NOME_MAX];
		scanf("%d %s", &chave, pedra);
		inserirPedra (&hashtable, pedra, chave);
	}

	scanf("%d", &jogadas);

	for (int i = 0; i < jogadas; i++)
	{

		if (vingador == 0)
		{
			printf("F\n");
			return 0;
		}

		char jogo;
		scanf(" %c", &jogo);

		if (jogo == 'M')
		{
			int resultado;
			vingador --;

			jogadaM(&hashtable, &resultado);
		
			if (resultado == 0)
			{
				printf("F\n");
				return 0;
			}
		}

		else if (jogo == 'P')
			jogadaP (&hashtable);

		else if (jogo == 'T')
			jogadaT (&hashtable, &vingador);

	}


	printf ("T\n");
	limparHashTable(&hashtable);
	return 0;
}
