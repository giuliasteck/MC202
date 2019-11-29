/*****************************************
 ********** Nome: Giulia Steck ***********
 ************** RA: 173458 ***************
 *********** Turma: MC202 - GH ***********
 *****************************************/

/********************************************************************************
 * Entradas: Inteiro n que representa a quantidade total de peças na partida,
 * seguido de n numeros inteiros que são os valores de cada peça. Diferentes
 * entradas (X, C, K, O, T t) que representam ações diferentes na jogada e a
 * sequência final dada por cada jogador.
 *
 * Saída: indica se o jogador referente aos números pares ganhou, ou o referen-
 * te aos números ímpares, ou se foi um empate;
 *********************************************************************************/


#include <stdio.h>
#include <stdlib.h>

//Definição da fila e da pilha, que serão implementados
//com a ajuda de listas ligas

typedef struct No
{
	int num;
	struct No *prox;
	struct No *ant;
} No;

typedef struct Estrutura
{
	No *primeiro;
} Estrutura;

/*************** FILA E PILHA ********************/
//Adiciona um elemento no fim da estrutura (Pilha e Fila)
void QueuePush(Estrutura *estrutura, int num);

//Remove o elemento da estrutura (usado na Pilha)
void pop(Estrutura *estrutura);

//Remove o primeiro elemento da estrutura (usado para Fila)
void dequeue(Estrutura *estrutura);

/************ FACILITAR IMPLEMENTAÇÃO ***********/
//Retorna o endereço do último nó de um estrutura.
No* ultimoItem (Estrutura *estrutura);

/****************** JOGADAS ********************/
//Jogada Keep Safe, que retira o elemento da jogada e o adiicona em uma Pilha
void KeepSafe (Estrutura *estrutura, Estrutura *PilhaImpar, Estrutura *PilhaPar);

//Jogada Out
void Out (Estrutura *estrutura);

//Jogada Come Back, que recupera o ultimo elemento salvo na Pilha (Keep Save) e
//o posiciona no final da jogada
void ComeBack (Estrutura *estrutura, Estrutura *PilhaImpar, Estrutura *PilhaPar);

//Retira uma peça após tempo definido e esse tempo é adicionado ao fim de uma Fila
void Trap (Estrutura *Fila, Estrutura *estrutura);

/****************** ARMADILHA ******************/
//Diminui o tempo faltante para a armadilha ser acionada a cada nova jogada
void contagemArmadilha (Estrutura *Fila);

//Indica se o jogo está em um momento em que a armadilha será acionada
int VerificarArmadilha (Estrutura *Fila);

/****************** RESULTADO ***************/
//Recebe chutes de cada um dos jogadores
Estrutura ReceberValores ();

//Compara os chutes com o estado atual do jogo para definir que será o vencedor
int Vencedor (Estrutura *jogo, Estrutura *chute);

/****************** DEBUGAR ***************/
//Imprime as estruturas utilizadas para facilitar encontrar possíveis erros no código
void Imprimir (Estrutura *estrutura);

/************** LIMPAR MEMÓRIA **********/
//Limpa estruturas após serem utilizadas
void limpar (Estrutura *estrutura);


int main ()
{
	//Define e inicializa as estruturas a serem utilizadas
	char partida = 0;
	Estrutura PilhaImpar, PilhaPar, Fila, Jogo;
	PilhaImpar.primeiro = NULL;
	PilhaPar.primeiro = NULL;
	Fila.primeiro = NULL;
	Jogo.primeiro = NULL;
	
	int n, num;
	scanf ("%d", &n);

	//Leitura dos valores iniciais no jogo
	for (int i = 0; i < n; i++)
	{
		scanf ("%d", &num);
		QueuePush (&Jogo, num);
		//Imprimir(&Jogo);
	}
	
	while(partida != 'X') //Caso X encerra as jogadas
	{
		scanf(" %c", &partida);

		if (VerificarArmadilha(&Fila)) //Armadilha deve ser ativada
		{
			//printf("oi");

			if(partida == 'K') //Keep Safe
			{
				KeepSafe(&Jogo, &PilhaImpar, &PilhaPar);
			}

			
			if(partida == 'O' || partida == 'C') //Out e Come Back
			{
				dequeue(&Jogo);
			}

			if(partida == 'T') //Trap
			{
				int tempo;
				scanf ("%d", &tempo);
				//printf("%d", tempo);
				dequeue(&Jogo);
			}
		}
		

		else
		{
			if(partida == 'K')
			{
				KeepSafe(&Jogo, &PilhaImpar, &PilhaPar);
				//Imprimir(&Jogo);
				//Imprimir(&PilhaImpar);
				//Imprimir(&PilhaPar);
			}
		
			if(partida == 'O') 
			{
				Out(&Jogo);
				//Imprimir(&Jogo);
			}

			if(partida == 'C')
			{
				ComeBack(&Jogo, &PilhaImpar, &PilhaPar);
				//Imprimir(&Jogo);
			}


			if (partida == 'T')
			{
				Trap(&Fila, &Jogo);
				//Imprimir(&Fila);
				//Imprimir(&Jogo);
			}
		}
	
		//Atualiza o tempo restante para armadilha ser disparada a cada novo loop
		contagemArmadilha(&Fila); 
	}


	Estrutura ChuteJogadorP = ReceberValores();
	Estrutura ChuteJogadorI = ReceberValores();
	
	int PontosP = Vencedor(&Jogo, &ChuteJogadorP);
	int PontosI = Vencedor(&Jogo, &ChuteJogadorI);

	if (PontosP > PontosI)
	{
		printf("P\n");
	}
	else if (PontosP == PontosI)
	{
		printf("E\n");
	}
	else
	{
		printf("I\n");
	}


	limpar(&Jogo);
	limpar(&PilhaImpar);
	limpar(&PilhaPar);
	limpar(&Fila);
	limpar(&ChuteJogadorI);
	limpar(&ChuteJogadorP);

}


/********** OPERAÇÕES FILA E PILHA ***********/
void QueuePush (Estrutura *estrutura, int num)
{
	if (estrutura->primeiro == NULL)
	{
		estrutura -> primeiro = (No*)malloc(sizeof(No));
		estrutura -> primeiro -> num = num;
		estrutura -> primeiro -> prox = NULL;
		estrutura -> primeiro -> ant = NULL;
		return;	
	}

	No *NoFim = estrutura -> primeiro;

	while (NoFim -> prox !=NULL)
	{
		NoFim = NoFim -> prox;
	}	
	
	NoFim -> prox = (No*)malloc(sizeof(No));
	NoFim -> prox -> num = num;
	NoFim -> ant = NoFim;
	NoFim -> prox -> prox = NULL;
	return;		
}


void pop(Estrutura *estrutura)
{
	if (estrutura -> primeiro == NULL)
	{
		return;
	}

	if (estrutura -> primeiro -> prox == NULL)
	{
		free(estrutura -> primeiro);
		estrutura -> primeiro = NULL;
		return;	
	}

	
	
	No *NoPenultimo = estrutura -> primeiro;

	while (NoPenultimo -> prox -> prox != NULL)
	{
		NoPenultimo = NoPenultimo -> prox;
	}

	free(NoPenultimo -> prox);
	NoPenultimo -> prox = NULL;
	

}

void dequeue(Estrutura *estrutura)
{
	if (estrutura -> primeiro == NULL)
	{
		return;
	}

	if (estrutura -> primeiro -> prox == NULL)
	{
		free(estrutura -> primeiro);
		estrutura -> primeiro = NULL;
		return;
	}

	No *NoSeg = estrutura -> primeiro -> prox;
	free (estrutura -> primeiro);
	estrutura -> primeiro = NoSeg;
	estrutura -> primeiro -> ant = NULL;

}

/********** ÚTIL PARA JOGADAS ***************/
No* ultimoItem (Estrutura *estrutura)
{
	if (estrutura -> primeiro == NULL)
	{
		return NULL;
	}

	if (estrutura -> primeiro -> prox == NULL)
	{
		return estrutura -> primeiro;
	}

	No *Ultimo = estrutura -> primeiro;

	while (Ultimo -> prox != NULL)
	{
		Ultimo = Ultimo -> prox;
	}
	return Ultimo;
}	


/*********** OPERAÇÕES JOGADAS ***************/
void KeepSafe (Estrutura *estrutura, Estrutura *PilhaImpar, Estrutura *PilhaPar)
{
	if (estrutura -> primeiro == NULL)
	{
		return;
	}

	int ValorSalvo = estrutura -> primeiro -> num;

	if (ValorSalvo % 2 == 0)
	{
		QueuePush (PilhaPar, ValorSalvo);
		dequeue(estrutura);
	}

	else 
	{
		QueuePush (PilhaImpar, ValorSalvo);
		dequeue(estrutura);
	}
}

void Out (Estrutura *estrutura)
{
	if (estrutura -> primeiro == NULL || estrutura -> primeiro -> prox == NULL)
	{
		return;
	}

	if ((estrutura -> primeiro -> num > estrutura -> primeiro -> prox -> num) && (estrutura -> primeiro -> num %2 != estrutura -> primeiro -> prox -> num %2))
	{
		if (estrutura -> primeiro -> prox -> prox == NULL)
		{
			free (estrutura -> primeiro -> prox);
			estrutura -> primeiro -> prox = NULL;
		}

		else
		{
			No *TerceiroNo = estrutura -> primeiro -> prox -> prox;
			free (estrutura -> primeiro -> prox);
			estrutura -> primeiro -> prox = TerceiroNo;
			TerceiroNo -> ant = estrutura -> primeiro;
		}

	}

		int PrimeiroValor = estrutura -> primeiro -> num;
		dequeue(estrutura);
		QueuePush (estrutura, PrimeiroValor);
}


void ComeBack (Estrutura *estrutura, Estrutura *PilhaImpar, Estrutura *PilhaPar)
{
	int ValorJogadaAtual = estrutura -> primeiro -> num;
	int ValorKeepSafe;
	
	if (ValorJogadaAtual % 2 != 0)
	{
		if (PilhaImpar -> primeiro == NULL)
		{
			return;
		}
	
		else
		{
		No * UltimoNo = ultimoItem(PilhaImpar);
		ValorKeepSafe = UltimoNo  -> num;
		pop(PilhaImpar);

		dequeue(estrutura);
		QueuePush (estrutura, ValorJogadaAtual);
		QueuePush (estrutura, ValorKeepSafe);

		return;
		}
	}

	
	else 
	{
		if (PilhaPar -> primeiro == NULL)
		{
			return;
		}

		else
		{
		No * UltimoNo = ultimoItem(PilhaPar);
		ValorKeepSafe = UltimoNo  -> num;
		pop(PilhaPar);

		dequeue(estrutura);
		QueuePush (estrutura, ValorJogadaAtual);
		QueuePush (estrutura, ValorKeepSafe);

		return;
		}
	}

	return;

}

void Trap (Estrutura *Fila, Estrutura *estrutura)
{
	int tempo;
	scanf ("%d", &tempo);
	QueuePush(Fila, tempo);

	No *ant, *depois;
	int temp;

	
	//Traps são ordenadas para facilitar a checagem de serem acionadas.
	//No caso, só será necessário checar a primeira posição da Trap
	//para saber se ela deve ser disparada ou não, ao invés de percorrer
	//toda a fila

	for (ant = Fila->primeiro; ant -> prox != NULL; ant = ant -> prox)
	{
		for (depois = ant -> prox; depois !=NULL; depois = depois -> prox)
		{
			if(ant -> num > depois -> num)
			{
				temp = ant -> num;
				ant -> num = depois -> num;
				depois -> num = temp;
			}
		}
	}

	int PrimeiroValor = estrutura -> primeiro -> num;
	dequeue (estrutura);
	QueuePush (estrutura, PrimeiroValor);
}

/********************* ARMADILHA ****************/
void contagemArmadilha (Estrutura *Fila)
{
	if (Fila -> primeiro == NULL)
	{
		return;
	}

	No *Armadilha = Fila -> primeiro;

	while (Armadilha != NULL)
	{
		Armadilha -> num = Armadilha -> num - 1;
		
		if (Armadilha -> num < 0)
		{
			dequeue(Fila);
		}
		
		Armadilha = Armadilha -> prox;
	}


}

int VerificarArmadilha (Estrutura *Fila)
{
	if (Fila -> primeiro == NULL)
	{
		return 0;
	}
	if (Fila -> primeiro -> num == 0)
	{
		return 1;
	}

	else
	{
		return 0;
	}

	return 0;
}
/***************** DEFINIR VENCEDORES ****************/

Estrutura ReceberValores ()
{
	Estrutura chute;
	chute.primeiro = NULL;
	int valor;

	while (1)
	{
		scanf (" %d", &valor);
		
		if (valor != -1)
		{
			QueuePush(&chute, valor);
		}

		else
		{
			break;
		}
	}

	return chute;
}

int Vencedor (Estrutura *jogo, Estrutura *chute)
{
	No *NoChute = chute -> primeiro;
	No *NoJogo = jogo -> primeiro;
	int pontuacao = 0;
	
	if (jogo -> primeiro == NULL && chute -> primeiro == NULL)
	{
		pontuacao ++;;
	}

	if (jogo -> primeiro == NULL && chute -> primeiro !=NULL)
	{
		return 0;
	}


	if (jogo -> primeiro != NULL && chute -> primeiro == NULL)
	{
		return 0;
	}	

	while(NoChute != NULL && NoJogo != NULL)
	{
		if(NoChute -> num == NoJogo -> num)
		{
			pontuacao ++;
		}

		NoChute = NoChute -> prox;
		NoJogo = NoJogo -> prox;
	}

	return pontuacao;

}

/********** DEBUGAR **********/
void Imprimir(Estrutura *lista)
{
	No *NoAtual = lista -> primeiro;
	if (NoAtual != NULL)
	{
		while (NoAtual != NULL)
		{
			printf("%d, ", NoAtual -> num);
			NoAtual = NoAtual -> prox;
		}
	printf("\n");
	}
}

/************* LIMPAR MEMÓRIA ***********/
void limpar (Estrutura *estrutura)
{
	while (estrutura -> primeiro != NULL)
	{
		dequeue(estrutura);
	}
}
