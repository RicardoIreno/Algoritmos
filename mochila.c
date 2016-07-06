/*
PROBLEMA DA MOCHILA USANDO PROGRAMAÇÃO DINÂMICA
===============================================
Seja:
	Objetos: {x1, x2, x3, x4}
	Valores: {10,  7, 25, 24}
	Pesos:   { 2,  1,  6,  5}
	E uma mochila de maxMidade 7.
Qual é a combinação de objetos de maior valor 
que caiba na mochila.
===============================================
*/

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

typedef struct 
{
	char *nome;
	int valor;
	int peso;
} objeto;

int max (int a, int b) { if (a>b) return a; else return b;}

void imprime(int **matriz, int n, int maxM)
{
	int i, j;
	for (i=0; i<n; i++){
		printf("\n");
		for (j=0; j<maxM+1; j++) printf("%5d", matriz[i][j]);
	}
}

int *solver(objeto *obj, int n, int maxM )
{
	int i, j;
	int **matriz = (int **) calloc(n+1, sizeof(int *));
	
	matriz[0] = (int *) calloc(maxM+1, sizeof(int)); 

	for (i=1; i<n+1; i++)
	{	
		matriz[i] = (int *) calloc(maxM+1, sizeof(int));	
		for (j=1; j<maxM+1; j++)
			if ( obj[i-1].peso > j ) matriz[i][j] = matriz[i-1][j]; 
			else   	  
			  matriz[i][j] = max( (matriz[i-1][ j - obj[i-1].peso ] + obj[i-1].valor), matriz[i-1][j]);
			  // max{ f(Xn-1, W-Pn) + Vn , f(Xn-1, W) } (tá dentro, tá fora)
	}
	imprime(matriz, n+1, maxM);
	printf("\nValor máximo: %d\n",matriz[n][maxM] );

	int *resp = calloc(n, sizeof(int));
	
	i=n; j=maxM;
	for (; i>0; i--)
		if ( matriz[i][j] > matriz[i-1][j] ) {
			resp[i-1] = 1;  
			j-=obj[i-1].peso;
		}

	for (i = 0; i < n; i++)	free(matriz[i]);
	free(matriz);
	return resp;
}

void imprimeResp(objeto *obj, int *resp, int n)
{
	int i=0, tp=0, tv=0;
	printf("\n\n      Item      Valor  Peso\n");
	for (; i<n; i++ )
		if (resp[i])
		{
			printf("%10s %10d %5d \n", obj[i].nome, obj[i].valor, obj[i].peso);
			tp+= obj[i].peso;
			tv+= obj[i].valor;
		}
	printf("\nValor máximo: %d\nPeso na mochila: %d",tv, tp );	
}

int main()
{
	objeto obj[] = {
	    {"mapa",    10,   2},
	    {"faca",     7,   1},
	    {"cantil",  25,   6},
	    {"b�ssula", 24,   5},
	};
	int n = 4;
	int maxM = 7;
	int *resposta;
	resposta = solver(obj, n, maxM);

	imprimeResp(obj, resposta, n);
}
