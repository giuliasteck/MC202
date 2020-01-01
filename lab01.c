#include <stdio.h>

/****Disciplina: Estrutura de Dados - Turma G*****/
/************ Tarefa de Laboratório 1 ************/
/********** Nome: Giulia Steck - 173458 **********/

/*Problema: Verificar se disposição de monitores em
uma sala de aula para observar se alunos estão colando
é segura ou não. Sendo que uma disposição segura diz 
respeito à quando os monitores são capazes de observar
todos os alunos.

Entradas: m e n, que são números inteiros que representam,
respectivamente, número de linhas e colunas da matriz. S, 
que expressa o número de monitores na sala. X e Y que apontam
a coordenada desses monitores na matriz, sendo X referente à
linha da matriz, e Y à colunas. A referente ao alcance da visão
de cada monitor.

Saída: T ou F. Sendo T referente à uma disposição segura dos
monitoes e F indicando que ela não é segura.*/



int main() {
	
	int m, n;  			     //Tamanho da matriz
	int s;     				 //Número de monitores
    int	x, y;  			     //Posição do monitor
	int a;     				 //Alcance do monitor
	int z;     				 //Variável acumuladora, pra checar zeros da matriz
   			
	scanf("%d %d", &m, &n);  //Entrada das dimensões da matriz
	scanf("%d", &s); 		 //Entrada da quantidade de monitores

	int matrix[m][n];		 //Definição da matriz m por n


   /* 
	* Criação de uma matriz m por n na qual todos
	* os seus elementos são iguais à zero. 
	*/
	for(int i = 0; i < m; i++) 
	{
		for(int j = 0; j < n; j++) 
		{
			matrix[i][j] = 0;
		}
	}

	/* 
	 * Nessa parte do código, a cada nova entrada do usuário
	 * com as coordenadas e alcande de cada monitor, os zeros
	 * na matriz passam a ser substituidos por um, tanto na 
	 * posição em que cada um deles ocupam, quanto nas posições
	 * as quais eles têm alcance. 
	 */
	for (int i=0; i < s; i++)
	{ 
		scanf(" ( %d, %d, %d )", &x, &y, &a);
		x = x - 1;
		y = y - 1;
		matrix[x][y]=1;

		/* 
		 * Antes do alcance de cada monitor ser marcado na matriz,
		 * é verificado através dos if's se seu alcance ultrapassa
		 * os limites da matriz. Sendo assim, é evitado que o programa
		 * acesse posições inválidas dela.
		 */
		for(int i=1;i<=a;i++)
		{
			if (x+i<m){
				matrix[x+i][y]=1;
			}
			if (y+i<n){
				matrix[x][y+i]=1;
			}
			if (x-i>=0){	
				matrix[x-i][y]=1;
			}
			if (y-i>=0){	
				matrix[x][y-i]=1;
			}
			if (x+i<m && y+i<n){
				matrix[x+i][y+i]=1;
			}
			if (x+i<m && y-i>=0){
				matrix [x+i][y-i]=1;
			}
			if (x-i>=0 && y+1<n){
				matrix [x-i][y+i]=1;
			}
			if (x-i>=0 && y-i>=0){
				matrix[x-i][y-i]=1;
			}
		}
	}
	

		/*
		 * Nessa parte do código, a cada zero
		 * encontrado na matriz, adiciona-se 1
		 * à variável z.
		 */
		for(int i=0;i<m;i++){
			for(int j=0; j<n; j++){
				if (matrix[i][j] == 0){
					z = z+1;
				}
			}
		}

		/*
		 * Se z for igual à zero, significa que
		 * os monitores se encontram dispostos de
		 * forma segura - não há nenhum zero na matriz.
		 * Sendo assim "T" é printado.
		 */
		if (z > 0){
			printf("F\n");
		}
		else{
			printf("T\n");
		}

}

