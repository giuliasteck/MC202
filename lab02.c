
/*
 * Nome: Giulia Steck - 173458
 *
 * Entrada: O programa tem como entrada o nome dos 7 pintores em ordem aleatória. Em seguida, tem-se N linhas como
 * entrada, na qual inserimos o nome dos artistas e as coordenadas x e y pelas quais ele é responsável por pintar,
 * coordenadas essas referentes aos pontos da borda superior da parede não pintas.
 * Logo depois, mais N linhas no mesmo formato, referentes aos pontos superiores da borda pintada.
 *
 * Saída: Temos como saída os nomes dos pintores na mesma ordem em que foram colocados na entrada, seguido pelas
 * áreas totais que eles são responsáveis para pintar.
 */

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= Cabeçalhos de Funções =-=-=-=-=-=-=-=-= -=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include <stdio.h>
#include <string.h>

#define NOME_MAX 30

typedef struct _ponto {
double x;
double y;
char nome[NOME_MAX];
} ponto;

typedef struct _pintor {
char nome[NOME_MAX];
double area;
} pintor;

/* Inicia Pintores                                                                                         *
 * Objetivo:    Le os nomes dos pintores e os armazena em um vetor de structs                              *
 * Saída:       Não retorna nenhum valor como saida                                                        *
 * Parâmetros:                                                                                             *
 *      - pintor *pintores: Ponteiro para o vetor de pintores a ser preenchido                             *
 */

void inicia_pintores(pintor *pintores)
{
	
	for (int i = 0; i < 7; i++)
	{
		scanf("%s", pintores[i].nome);
	}
}


/* Le borda                                                                         *
 * Objetivo:    Ler a grade de pontos que compoe a borda da parede                  *
 * Saída:       Não retorna nenhum valor como saida                                 *
 * Parâmetros:                                                                      *
 *      - ponto borda: Ponteiro para o vetor de pontos da borda                     *
 */

void le_borda(ponto *borda, int n)
{

	for(int i = 0; i < n; i++)
	{
		scanf("%lf %lf %s", &borda[i].x, &borda[i].y, borda[i].nome);
	}
}

/* Computa Area                                                                             *
 * Objetivo:    Computar o valor da area a ser pintada por cada pintor                      *
 * Saída:       Não retorna nenhum valor como saida                                         *
 * Parâmetros:                                                                              *
 *      - ponto *superior: Vetor de pontos que representa a borda superior da parede        *
 *      - ponto *pintada: Vetor de pontos que representa a borda superior da area pintada   *
 *      - int n: Inteiro que representa o numero de pontos da discretizaçao das bordas      *
 *      - pintor *pintores: Vetor de structs dos pintores como nome e area                  * 
 */

void computa_area(ponto *superior, ponto *pintada, int n, pintor *pintores)
{
	double funcao_x_sup, funcao_y_sup;
	double funcao_x_inf, funcao_y_inf;
	double area_trapezio_sup, area_trapezio_inf;

	
	/*
	 * O loop verifica as coordenadas referentes à cada pintor na struct com os pontos. Em  * 
	 * seguida, calcula a área de toda a parede - incluindo as partes já pintadas -  e      *  
	 * depois subtrai desse valor a área da parede já pintada. A cada novo loop de j, a     *
	 * área pintada por cada pintor é atualizada na struct pintor.                          *
	 */

	for (int i = 0; i < 7; i++)
	{
		for (int j=0; j < n-1; j++)
		
			if (strcmp(pintores[i].nome, superior[j].nome) == 0)
			{
				funcao_x_sup = superior[j+1].x - superior[j].x;
				funcao_y_sup = superior[j+1].y + superior[j].y;
				area_trapezio_sup = (funcao_y_sup*funcao_x_sup)/2;

				funcao_x_inf = pintada[j+1].x - pintada[j].x;
				funcao_y_inf = pintada[j+1].y + pintada[j].y;
				area_trapezio_inf = (funcao_y_inf*funcao_x_inf)/2;
				pintores[i].area += area_trapezio_sup - area_trapezio_inf;
			}
	}
}



/* Imprime Areas                                                                                        *
 * Objetivo:    Imprimir a area a ser pintada por cada pintor                                           *
 * Saída:       Não retorna nenhum valor como saida                                                     *
 * Parâmetros:                                                                                          *
 *      - pintor *pintores:  Vetor de structs dos pintores como nome e area                             *
 */

void imprime_areas(pintor *pintores){
	for (int i = 0; i < 7; i++)
	{
		printf("%s: ", pintores[i].nome);
		printf("%.2f UA\n", pintores[i].area);
	}
}


/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= Função Principal (Main) -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */


int main()
{

	int n;
	pintor pintores[8];     //Vetor que aponta para struct pintor
	ponto superior[201];    //Vetor que aponta para struct ponto e salva pontos superiores
	ponto pintada[201];     //Vetor que aponta para struct ponto e salva pontos da borda pintada

	inicia_pintores(pintores);

	scanf ("%d", &n);       //Leitura de n

	//Ler pontos da borda
	le_borda(superior, n);
	le_borda(pintada, n);

	computa_area(superior, pintada, n, pintores);

	imprime_areas(pintores);



}
