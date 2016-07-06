/*
..........................................................
 Faculdade de Tecnologia de São Paulo                   
 Análise de Algoritmos - Prof. Grace Borges    		 
 Comparação de diferentes técnicas de ordenação - v1    
 Ricardo Ireno - 132200644								            
 Março de 2016                              			 
..........................................................
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>

typedef struct {int compa, troca; } count;
void troca(int *a, int *b) {int x=*a; *a=*b; *b=x;}
void zeraContador(count c){ c.compa=0; c.troca=0; }

void mostraContador(count c) { 
	printf("Total de comparações: %5d\nTotal de trocas: %5d\n",c.compa, c.troca );
}
void imprimeVetor(int v[], int n) {
	int i = 0;
	while (i<n) { printf("%d, ",v[i++] ); }
	printf("\n\n");	
}

void resetVetor(int v[], int n) {	
	int j=0;
	for (; n>0; n--){ v[j] = n; j++; } 
}

void automato(count c, int v[], int n ) {
	mostraContador(c);
	imprimeVetor(v, n);
	zeraContador(c);
	resetVetor(v, n);
}



//................................................

count seleciona(int v[], int n) {
	count c;
	int maior=0, aux, i;
	c.compa=0; c.troca=0;

	for (i=1; i<n; i++)	{
		if ( v[i] > v[maior] ) maior=i;	
		c.compa+=2;
	}
	troca(&v[n-1], &v[maior]);
	c.troca++;
	return c;
}

count selection_sort2(int v[], int n){
	count c, aux;
	c.compa=0;
	for(; n>1; n--) {
		c.compa++;
		aux = seleciona(v, n); // não funciona quando passado diretamente para 'c'.
		c.compa += aux.compa;
		c.troca += aux.troca;
	}
	return c;
}

//................................................

count insertion_sort(int v[], int n) {
	count c;
	c.compa=0; c.troca=0;
	int i, j, x;
	for (j=1; j<n; j++) {
		c.compa++;
		x=v[j];
		for(i=j-1; i>=0 && v[i]> x; i--) {
			c.compa +=2;
			v[i+1]=v[i]; 
			c.troca++;
		}
		v[i+1] = x; 
		c.troca++;
	}
	return c;
}

count selection_sort(int v[], int n){
	count c;
	c.compa=0; c.troca=0;
	int i, j, k;
	for (i=1; i<=n-1; i++){
		c.compa++;
		k = 0;
		for (j=1; j<=n-i; j++){
			c.compa++;
			if (v[j] > v[k]){
				k = j;
			}
		}
		troca(&v[k], &v[j-1]); 
		c.troca++;
	  }
	 return c; 
  }



count bubble_sort(int v[], int n){
	count c;
	c.compa=0; c.troca=0;
	int i, j;
	for ( i=1; i<=n-1; i++){
		c.compa++;
		for ( j=0; j<n-i; j++){
			c.compa++;
			if (v[j] > v[j+1]){
				troca(&v[j], &v[j+1]); 
				c.troca++;
			}
		}
	}
	return c;
}


count intercala(int v[], int p, int m, int u){
	count c;
	c.compa=0; c.troca=0;
	int *w = (int *) malloc( (u-p+1)* sizeof(int) );
	if (w == NULL) abort();
	int i = p, j = m+1, k=0;
	while (i<=m && j<=u){
		c.compa+=2;		
		if (v[i] < v[j]){
			c.compa++;
			w[k++] = v[i++]; 
			c.troca++;
		} 
		else {
			w[k++] = v[j++]; 
			c.troca++;
		}	
	}
	
	while (i<=m){ 
		c.compa++;
		w[k++] = v[i++]; 
		c.troca++;
		
	} 
	while (j<=u) {
		c.compa++;
		w[k++] = v[j++]; 
		c.troca;
	}
	
	for (k = 0; k<=u-p; k++){
		v[p+k] = w[k]; 
		c.troca++;
	}
	free(w);
	return c;
}


count merge_sort(int v[], int p, int u){
	count c; count aux;
	c.compa=0; c.troca=0;
	if (p == u) return c;
	int m = (p + u)/2;
	merge_sort( v, p, m);
	merge_sort( v, m+1, u);
	aux = intercala( v, p, m, u);
	c.compa += aux.compa;
	c.troca += aux.troca;
	return c;

}


//................................................


int main(void)
{
	int v[21];
	int n=20;
	count c;

	setlocale (LC_ALL, "Portuguese");

	resetVetor(v, n);
	printf("Vetor usado \n");
	imprimeVetor(v, n);

	printf("selection Sort \n");
	c = selection_sort(v, n);
	automato( c, v, n);

	printf("Selecion Sort v2 \n");
	c = selection_sort2(v, n);
	automato( c, v, n);

	printf("Insertion Sort \n");
	c = insertion_sort(v, n);
	automato( c, v, n);

	printf("Bubble Sort \n");
	c = bubble_sort(v, n);
	automato( c, v, n);
	
	printf("Merge Sort \n");
	c = merge_sort(v, 0, n);
	automato( c, v, n);
	return 0;

}

