#include	<stdio.h>
#include	<stdlib.h>

#define infinite 65535
#define TAM 200

// Matriz de Adjacências
int adjacencia[TAM][TAM];

// conjunto lambda(MENOR CAMINHO/ANTECESSOR)
int lambda[TAM][2];

void preencherLambda(int tamanho)
{
	int i;
	for(i = 0; i < tamanho; i++)
	{
		lambda[i][0] = infinite;
		lambda[i][1] = -1;
	}
}

void preencherAdjacencia(int tamanho)
{
	int i,j;
	for(i = 0; i < tamanho; i++)
	{
		for(j = 0; j < tamanho; j++)
		{
			adjacencia[i][j] = -1;
		}
	}
}

void encontraCaminho(int atual, int nVertice)
{
	int i;
	for(i = 0; i < nVertice; i++)
	{
		if(adjacencia[atual][i] != -1)
		{
			if(lambda[atual][0]+adjacencia[atual][i] < lambda[i][0])
			{
				lambda[i][0] = lambda[atual][0]+adjacencia[atual][i];
				lambda[i][1] = atual;
				encontraCaminho(i, nVertice);
			}
		}
	}	
}

void exibeMenorCaminho(int ini, int fim)
{
	if(fim != ini)
	{
		exibeMenorCaminho(ini, lambda[fim][1]);
		printf("%d ",fim);
	}
	else
	{
		printf("%d ",ini);
	}
}

void encontrarMenorCaminho(int ini, int fim, int nVertice)
{
	int atual;

	atual = ini;

	lambda[atual][0] = 0; 

	encontraCaminho(atual, nVertice);

	printf("%d\n", lambda[fim][0]);
	exibeMenorCaminho(ini, fim);
	printf("\n");
}

void exibirMatriz(int nVertice)
{
	int i, j;
	printf(" ");
	for(i = 0; i < nVertice; i++)
	{
		printf(" %d ",i);
	}
	
	printf("\n");

	for(i = 0; i < nVertice; i++)
	{
		printf("%d  ",i);
		for(j = 0; j < nVertice; j++)
		{
			printf("%d ",adjacencia[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	// Número de vértices e número de arestas
	int nVertice, nAresta;

	int i, v1, v2, peso, ini, fim;

	preencherLambda(TAM);

	scanf("%d %d",&nVertice, &nAresta);
	preencherAdjacencia(nVertice);


	for(i = 0; i < nAresta; i++)
	{
		scanf("%d %d %d",&v1,&v2,&peso);
		adjacencia[v1][v2] = peso;
		adjacencia[v2][v1] = peso;
	}


	scanf("%d %d",&ini,&fim);

//	exibirMatriz(nVertice);

	encontrarMenorCaminho(ini, fim, nVertice);

/*
	for(i = 0; i < nVertice; i++)
	{
		printf("PESO: %d  ANTECESSOR: %d\n",lambda[i][0],lambda[i][1]);
	}
*/

	//printf("\n");
	return 0;
}