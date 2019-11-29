/**************************************************************
 *                 LAB06 - RUMO AO TOPO                       *
 *                Giulia Steck - 173458                       *
 * Entrada: número inteiro  de jogadores, seguido pelo        *
 * nome, nacionalidade e grupo de cada um. Logo em seguida,   *
 * entradas que indicam a pontuação de cada jogador em cada   *
 * fase e o tempo total que cada um demorou para resolver os  *
 * problemas.                                                 *
 *                                                            *
 * Saída: Dados sobre o jogador vitorioso e o estado de cada  *
 * linha da árvore.                                           *
 **************************************************************/        


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define Max 30

/******************* aux.h **********************/

/* Estrutura que define um competidor nos Jogos */
struct _no{
  char nome[Max], pais[Max];
  char g;
  int pontos;
  int tempototal;
  struct _no *esq;
  struct _no *dir;
};

typedef struct _no no;

/* Imprime o estado de um grupo de forma recursiva */
void exibe(no* grupo){

  printf("(");

  /* Caso o grupo nao seja vazio */
  if(grupo != NULL){
    printf("%s ", grupo->nome);
    
	exibe(grupo->esq);
    exibe(grupo->dir);
  }
  printf(")");

}

/*Criação do nó raiz da árvore*/
typedef struct ArvoreBinaria{
	no* raiz;
	int altura;
} ArvoreBinaria;

/*********** FUNÇÕES DA ÁRVORE BINÁRIA ***********/
/*Criação dos nós da árvore*/
void ConstruirArvore (ArvoreBinaria *chave);

/*Preenchimento dos nós alocados na função anterior com as informações sobre cada jogador*/
void PreencherArvore (ArvoreBinaria *chave, char *nome, char *pais, char grupo, int numeroGrupo);

/*Encontra a posição de um jogador na árvore binária*/
no* OrientacaoBinario (ArvoreBinaria *chave, int posicao);

/*Procura jogadores de mesma nacionalidade e troca a posição deles de acordo com as regras do campeonato*/
void TrocarJogadores (ArvoreBinaria *chave);

/*Encontra nó que origina seus filhos. Necessário, pois estamos percorrendo a árvore de baixo para cima*/
void EncontrarNoPai (no *chave,no **nopai, char *jogador1, char *jogador2);

/*Preenche o nó pai de acordo com as informações do debate entre seus filhos*/
void AtualizarResultados (ArvoreBinaria *chave, char *jogador1,int ponto1, int tempo1, char *jogador2, int ponto2, int tempo2);

void EncontrarVencedorEtapa (char *nomePai, char*nomeFilho1, char*nomeFilho2, char* paisPai, char* paisFilho1, char* paisFilho2, int ponto1, int ponto2, int tempo1, int tempo2);

/*Imprime cada linha de cada grupo*/
void ImprimirFinal (ArvoreBinaria *chave);

/******* FUNÇÕES COMPLEMENTARES *********/
/*Calcula a pontuação total do vencedor do campeonato. Necessário para função imprimir final*/
int PontuacaoTotal (ArvoreBinaria *chave);

/*Transforma um número inteiro em binário. Necessário para função OrientacaoBinario*/
int* InteiroBinario(int altura, int n);

/*Encontra a altura da árvore baseado no número de jogadores*/
int EncontrarAltura (int jogadores);

/*Variação da função exibe, presente no aux.h. Porém, atende a necessidade de imprimir o grupoB de forma inversa*/
void exibeB(no *grupo);

/**************** MAIN *******************/

int main(){
	char nome[Max];
	char pais[Max];
	char grupo;

	int jogadores;
	int jogaA = 0;
	int jogaB = 0;
	
	scanf ("%d", &jogadores);
	
	ArvoreBinaria chave;
	chave.raiz = NULL;
	chave.altura = EncontrarAltura(jogadores)-1;
   	ConstruirArvore(&chave);	

	for(int i=0; i<jogadores; i++){
		scanf("%s %s %c", nome, pais, &grupo);

		/*O indice jogaA é atualizado sempre que um novo nó do grupo A é preenchido.  *
		 * Posteriormente, esse indice é transformado para um número binário, que     *
		 * orienta a busca por ele dentro da árvore binária                           */
		if (grupo == 'A'){
			PreencherArvore(&chave, nome, pais, grupo, jogaA);
			jogaA ++;
		}

		else{
			PreencherArvore(&chave, nome, pais, grupo, jogaB);
			jogaB++;
		}
	}
	
	TrocarJogadores(&chave);

	int ValorInicial = 1;

	for (int i = 0; i < chave.altura+1; i++)
		ValorInicial *= 2; 	

	int NosArvore = ValorInicial -1;
	//printf("Nos %d", NosArvore);

	for(int j = 0; j < NosArvore - jogadores; j ++){
		char nome1[Max], nome2[Max];
		int ponto1, ponto2, tempo1, tempo2;

		scanf("%s %d %d %s %d %d", nome1, &ponto1,&ponto2, nome2,&tempo1, &tempo2);
		AtualizarResultados(&chave, nome1, ponto1, tempo1, nome2, ponto2, tempo2);
	}


	ImprimirFinal(&chave);

}

/********** FUNÇÕES AUXILIARES ***********/
void ConstruirArvore (ArvoreBinaria *chave){
	if (chave -> altura <= 0)
		return;

	if (chave -> raiz == NULL)
	{
		chave -> raiz = (no*)malloc(sizeof(no));
		chave -> raiz -> esq = NULL;
		chave -> raiz -> dir = NULL;
		chave -> raiz -> g = 'N';
		ConstruirArvore(chave);
	}

	else
	{
		chave -> raiz -> esq = (no*)malloc(sizeof(no));
		chave -> raiz -> esq -> esq = NULL;
		chave -> raiz -> esq -> dir = NULL;
		chave -> raiz -> g = 'A';

		chave ->raiz -> dir = (no*)malloc(sizeof(no));
		chave -> raiz -> dir -> esq = NULL;
		chave -> raiz -> dir -> dir = NULL;
		chave -> raiz -> g = 'B';

		ArvoreBinaria SubArvoreEsq;
		ArvoreBinaria SubArvoreDir;

		SubArvoreEsq.raiz = chave -> raiz -> esq;
		SubArvoreEsq.altura = chave -> altura - 1;
		
		SubArvoreDir.raiz = chave -> raiz -> dir;
		SubArvoreDir.altura = chave -> altura -1;

		ConstruirArvore(&SubArvoreEsq);
		ConstruirArvore(&SubArvoreDir);
	}
}


void PreencherArvore (ArvoreBinaria *chave, char *nome, char *pais, char grupo, int numeroGrupo){
	ArvoreBinaria SubArvore;
	SubArvore.altura = chave -> altura -1;

	/*A primeira busca da árvore binária a partir da raíz não é orientada por um número binário,  *
	 * uma vez que, não depende de um número variante e sim, de qual grupo o jogador pertence.    *
	 * No caso, se pertence ao grupo A, vai para o nó esquerdo após a raíz e, se pertence ao      *
	 * grupo B, para o direito. Após isso, as buscas são todas determinadas pelo indice em        *
	 * binário.                                                                                   */

	if (grupo == 'A')
		SubArvore.raiz = chave -> raiz -> esq;
	
	if(grupo == 'B')
		SubArvore.raiz = chave -> raiz -> dir;

	no* jogador = OrientacaoBinario (&SubArvore, numeroGrupo);
	
	strcpy(jogador->nome, nome);
	strcpy(jogador -> pais, pais);
	jogador -> g = grupo;
}

no* OrientacaoBinario (ArvoreBinaria *chave, int posicao)
{
	no* jogada = chave -> raiz;
	int tamanho = chave -> altura;

	int *orientacao = InteiroBinario (tamanho, posicao);
	for (int i = 0; i<tamanho; i++){
		if (orientacao[i] == 0)
			jogada = jogada -> esq;
		else
			jogada = jogada -> dir;
	}

	free(orientacao);
	return(jogada);
}

void TrocarJogadores (ArvoreBinaria *chave){

	char JogadorAux[Max];
	char PaisAux[Max];
	int ValorInicial = 1;

	for (int i = 0; i < chave -> altura+1; i++)
		ValorInicial *= 2; 	

	int jogadas = ValorInicial;

	for (int i = 0; i < jogadas; i = i+2){
		no *Jogador1 = OrientacaoBinario(chave, i);
		no *Jogador2 = OrientacaoBinario(chave, i+1);
	
		no* JogadorMesmoPais = NULL;

		//Caso sejam de países diferentes
		if (strcmp(Jogador1 -> pais, Jogador2 ->pais) != 0)
		{
		
			//Procura jogador do mesmo país e de nome diferente
			for(int j = 0; j < jogadas; j++){
				no* JogadorAnalisado = OrientacaoBinario(chave, j);

				if(strcmp(JogadorAnalisado -> nome, Jogador1 -> nome) != 0 && strcmp(JogadorAnalisado -> pais,Jogador1 -> pais) == 0 ){
					JogadorMesmoPais = JogadorAnalisado;

					strcpy(JogadorAux, Jogador2 -> nome);
					strcpy(PaisAux, Jogador2 -> pais);

					strcpy(Jogador2 -> nome, JogadorMesmoPais -> nome);
					strcpy(Jogador2 -> pais, JogadorMesmoPais -> pais);

					strcpy(JogadorMesmoPais -> nome, JogadorAux);
					strcpy (JogadorMesmoPais -> pais, PaisAux);
				}
			}
		}

	}

}

void EncontrarNoPai (no *chave,no **nopai, char *jogador1, char *jogador2){
	if (chave -> esq == NULL)
		return;

	if (chave -> dir == NULL)
		return;
	
	if ((strcmp(chave ->  esq -> nome, jogador1) == 0 && strcmp(chave -> dir -> nome, jogador2) == 0) || (strcmp(chave -> esq -> nome, jogador2) == 0 && strcmp(chave -> dir -> nome, jogador1) == 0)){
		*nopai = chave;	
	}

	else{
		EncontrarNoPai(chave -> esq, nopai, jogador1, jogador2);
		EncontrarNoPai (chave -> dir, nopai, jogador1, jogador2);
	}
}

void AtualizarResultados (ArvoreBinaria *chave, char *jogador1,int ponto1, int tempo1, char *jogador2, int ponto2, int tempo2){
	if (chave -> raiz == NULL || chave -> raiz -> esq == NULL || chave -> raiz -> dir == NULL)
		return;

	no *NoPai = NULL;

	EncontrarNoPai(chave -> raiz, &NoPai, jogador1, jogador2);

	no *Jogador1;
	no *Jogador2;

	if (NoPai == NULL)
		return;

	if (strcmp(NoPai -> dir -> nome, jogador1) == 0){
		NoPai -> dir -> pontos = ponto1;
		NoPai -> dir -> tempototal = tempo1;
		NoPai -> esq -> pontos	= ponto2;
		NoPai -> esq -> tempototal = tempo2;

		Jogador1 = NoPai -> dir;
		Jogador2 = NoPai -> esq;	
	}

	if (strcmp(NoPai -> dir -> nome, jogador2) == 0){
		NoPai -> dir -> pontos = ponto2;
		NoPai -> dir -> tempototal = tempo2;
		NoPai -> esq -> pontos	= ponto1;
		NoPai -> esq -> tempototal = tempo1;

		Jogador2 = NoPai -> dir;
		Jogador1 = NoPai -> esq;	
	}

	EncontrarVencedorEtapa(NoPai->nome, Jogador1->nome, Jogador2 -> nome, NoPai -> pais, Jogador1 -> pais, Jogador2 -> pais, ponto1, ponto2, tempo1, tempo2);

	if (ponto1> ponto2)
		NoPai -> g = Jogador1 -> g;

	else if (ponto1<ponto2)
		NoPai -> g = Jogador2 -> g;

	else if (ponto1==ponto2){
		if(tempo1<tempo2)
			NoPai -> g = Jogador1 -> g;
		else
			NoPai ->g = Jogador2 -> g;
	}	
}

void EncontrarVencedorEtapa (char *nomePai, char*nomeFilho1, char*nomeFilho2, char* paisPai, char* paisFilho1, char* paisFilho2, int ponto1, int ponto2, int tempo1, int tempo2){
	if (ponto1 > ponto2){
		strcpy (nomePai, nomeFilho1);
		strcpy (paisPai, paisFilho1);

	}

	else if (ponto1 < ponto2){
		strcpy (nomePai, nomeFilho2);
		strcpy (paisPai, paisFilho2);
	}

	else if (ponto1 == ponto2){
		if (tempo1 < tempo2){
			strcpy (nomePai, nomeFilho1);
			strcpy (paisPai, paisFilho1);
		}

		else{
			strcpy (nomePai, nomeFilho2);
			strcpy (paisPai, paisFilho2);
		}
	}

}

int PontuacaoTotal (ArvoreBinaria *chave){
	no* ChavesVencedor = chave -> raiz;
	char vencedor[Max];
	strcpy(vencedor,chave -> raiz -> nome);
	int Pontucao = 0;
	
	while (ChavesVencedor -> esq != NULL && ChavesVencedor -> dir != NULL){
		if (strcmp (ChavesVencedor -> esq -> nome, vencedor) == 0)
			ChavesVencedor = ChavesVencedor -> esq;

		else
			ChavesVencedor = ChavesVencedor -> dir;

		Pontucao = Pontucao + ChavesVencedor -> pontos;
	}

	return Pontucao;

}

void ImprimirFinal (ArvoreBinaria *chave){

	int PontosVencedor;
	PontosVencedor = PontuacaoTotal(chave);

	printf("1 %s %s %c %d\n", chave -> raiz -> nome, chave -> raiz -> pais, chave -> raiz -> g, PontosVencedor);


	exibe(chave->raiz->esq);
	printf("\n");
	exibeB(chave ->raiz->dir);
	printf("\n");
}


/********** AUXILIARES ********************/
int* InteiroBinario(int tamanho, int n){
	int *binario = (int*)malloc(tamanho *sizeof(int));
	for (int i = tamanho - 1; i >= 0; i --){
		binario[i] = n % 2;
		n = n/2;
	}	

	return binario;
}

int EncontrarAltura (int jogadores){
	int altura;
	altura = (log10(jogadores)/log10(2)) + 1;
	return altura;
}

void exibeB(no* grupo){

  printf("(");

  /* Caso o grupo nao seja vazio */
  if(grupo != NULL){
    printf("%s ", grupo->nome);
    exibeB(grupo->dir);
    exibeB(grupo->esq);
  }
  printf(")");

}

