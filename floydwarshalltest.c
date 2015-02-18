#include 	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#define infinite 9999
#define TAM 500

typedef struct TipoLambda{
	int peso; // peso associado ao vértice
	int ant; // antecessor ao vértice
}Lambda;

typedef struct TipoVertice{
	int id; // ID do vértice
	int peso; // peso associado ao vértice
	int ant; // antecessor ao vértice
	struct TipoVertice * prox;
}Vertice;


void preencherMatrizAdjacencia(int nVertice, int mAdjacencia[][TAM])
{
	int i,j;
	for(i = 0; i < nVertice; i++)
	{
		for(j = 0; j < nVertice; j++)
		{
			mAdjacencia[i][j] = infinite;
		}
	}
	for(i = 0; i < nVertice; i++)
	{
		mAdjacencia[i][i] = -1;	
	}
}

void exibirMatriz(int nVertice, int mAdjacencia[][TAM], char vertice[][30])
{
	int i, j;
	printf("		");
	for(i = 0; i < nVertice; i++)
	{
		printf("|%s|", vertice[i]);
	}
	
	printf("\n");

	for(i = 0; i < nVertice; i++)
	{
		for(j = 0; j < nVertice*12; j++)
			printf("_");
		printf("\n");
		printf("%s", vertice[i]);
		for(j = strlen(vertice[i]); j <= 14; j++ )
			printf(" ");
		for(j = 0; j < nVertice; j++)
		{
			printf("|   %d  |",mAdjacencia[i][j]);
		}
		printf("\n");
	}
}

void preencherLambda(int nVertice, Lambda * lambda)
{
	int i;
	for(i = 0; i < nVertice; i++)
	{
		lambda[i].peso = infinite;
		lambda[i].ant = -1;
	}
}

void exibirlambda(int nVertice, Lambda * lambda)
{
	int i;

	for(i = 0; i < nVertice; i++)
	{
		printf("ind: %d peso: %d anc: %d\n",i, lambda[i].peso, lambda[i].ant);	
	}
}

void insereVerticeVisitado(Vertice ** verticeVisitado, Vertice vertice)
{
	Vertice * novo = (Vertice *) malloc(sizeof(Vertice));

	if(novo == NULL)
		exit(0);

	novo->id = vertice.id;
	novo->peso = vertice.peso;
	novo->ant = vertice.ant;
	//printf("Insere ID %d", vertice.id);

	//help = *verticeVisitado;

	while(*verticeVisitado != NULL)
	{
		if((*verticeVisitado)->peso > novo->peso)
			break;
		verticeVisitado = &((*verticeVisitado)->prox);
	}
	novo->prox = *verticeVisitado;
	*verticeVisitado = novo;
	//printf(" Inserido\n");

}

void excluirVerticeVisitado(Vertice ** verticeVisitado)
{
	if(*verticeVisitado == NULL)
		return;

	Vertice * novo;

	novo = (*verticeVisitado)->prox;
	free(*verticeVisitado);

	*verticeVisitado = novo;
}

void excluirVerticeVisitadoTodos(Vertice ** verticeVisitado)
{
	if(*verticeVisitado == NULL)
		return;
	else
	{
		Vertice * novo;
		novo = (*verticeVisitado)->prox;
		free(*verticeVisitado);
		*verticeVisitado = novo;
		excluirVerticeVisitadoTodos(verticeVisitado);	
	}
}

Vertice * procuraVertice(Vertice * verticeVisitado, int id)
{
	if(verticeVisitado == NULL)
		return NULL;
	else if(verticeVisitado->id == id)
		return verticeVisitado;
	else
		return procuraVertice(verticeVisitado->prox, id);
}

void excluirVerticeId(Vertice ** verticeVisitado, int id)
{
	if(*verticeVisitado == NULL)
		return;
		
	else if((*verticeVisitado)->id == id)
	{
		//printf("Exclui ID %d\n", id);
		Vertice * novo;

		novo = (*verticeVisitado)->prox;
		
		free(*verticeVisitado);

		*verticeVisitado = novo;

	}
	else
		excluirVerticeId(&((*verticeVisitado)->prox), id);
	
}

void exibirVertices(Vertice * verticeVisitado)
{
	if(verticeVisitado == NULL)
		return;
	printf("ID: %d Peso: %d 	",verticeVisitado->id, verticeVisitado->peso, verticeVisitado->ant);
	exibirVertices(verticeVisitado->prox);	
}

void encontraCaminho(int fim, int nVertice, int mAdjacencia[][TAM], Lambda * lambda, Vertice ** verticeVisitado)
{
	if(*verticeVisitado == NULL)
		return;

	int verticeAtual;

	verticeAtual = (*verticeVisitado)->id; // Vértice de Menor Peso
	//printf("\nVértice Atual %d\n", verticeAtual);

	lambda[verticeAtual].peso = (*verticeVisitado)->peso;
	lambda[verticeAtual].ant = (*verticeVisitado)->ant;

	excluirVerticeId(verticeVisitado, verticeAtual);

	//printf("\n"); exibirVertices(*verticeVisitado); printf("\n");

	if(verticeAtual == fim) // Vértice Atual é o Procurado
	{
		//printf("verticeAtual: %d == fim: %d \n", verticeAtual, fim);
		return;
	}
		

	Vertice vertice, * vizinho;
	int i;
	/*
	vertice.id = (*verticeVisitado)->id;
	vertice.peso = (*verticeVisitado)->peso;
	vertice.ant = (*verticeVisitado)->ant;
	*/

	for(i = 0; i < nVertice; i++)
	{
		if(mAdjacencia[verticeAtual][i] != -1 && lambda[i].peso == infinite) // Peso infinito em lambda indica que não está em lambda
		{
			vizinho = procuraVertice(*verticeVisitado, i);

			if(vizinho == NULL)
			{
				vertice.id = i;
				vertice.peso = lambda[verticeAtual].peso + mAdjacencia[verticeAtual][i];
				vertice.ant = verticeAtual;
				insereVerticeVisitado(verticeVisitado, vertice);
			}
			else if(vizinho->peso > lambda[verticeAtual].peso + mAdjacencia[verticeAtual][i])
			{
				excluirVerticeId(verticeVisitado, i);

				vertice.id = i;
				vertice.peso = lambda[verticeAtual].peso + mAdjacencia[verticeAtual][i];
				vertice.ant = verticeAtual;

				insereVerticeVisitado(verticeVisitado, vertice);
			}
		}
	}

	//printf("\n"); exibirVertices(*verticeVisitado); printf("\n");
	encontraCaminho(fim, nVertice, mAdjacencia, lambda, verticeVisitado);
}

void exibeMenorCaminho(int fim, Lambda * lambda)
{
	if(fim != -1)
	{
		exibeMenorCaminho(lambda[fim].ant, lambda);
		printf("%d ", fim);
	}

}

void encontrarMenorCaminho(int inicio, int fim, int nVertice, int mAdjacencia[][TAM], Lambda * lambda)
{
	// Vetor dos Vértices Visitados
	Vertice * verticeVisitado;
	verticeVisitado = NULL;

	Vertice vertice;

	//printf("\nencontraCaminho\n");

	vertice.id = inicio;
	vertice.peso = 0;
	vertice.ant = -1;

	insereVerticeVisitado(&verticeVisitado, vertice);

	//printf("\n"); exibirVertices(verticeVisitado); printf("\n");

	encontraCaminho(fim, nVertice, mAdjacencia, lambda, &verticeVisitado);

	//exibirVertices(verticeVisitado); printf("hhh\n");
	excluirVerticeVisitadoTodos(&verticeVisitado);	

	//printf("Peso: %d até %d é %d\n", inicio, fim, lambda[fim].peso);

	if(lambda[fim].peso != infinite)
	{
		printf("%d\n", lambda[fim].peso);	
		exibeMenorCaminho(fim, lambda);
		printf("\n");
	}
	else
	{
		printf("\nnao ha caminho\n");
	}
}
int main()
{
	// Matriz de Adjacência
	int mAdjacencia[TAM][TAM];
	//Vetor de Lambda
	Lambda lambda[TAM];
	char vertice[30][30];
	// Número de vértices e número de arestas
	int nVertice, nAresta;
	int i, peso, inicio, fim, v1, v2, j, k;

	scanf("%d %d",&nVertice, &nAresta);	
	
	preencherMatrizAdjacencia(nVertice, mAdjacencia);
	//preencherLambda(nVertice, lambda);
	

	for(i = 0; i < nVertice; i++)
	{
		scanf("%s", vertice[i]);
	}
	exibirMatriz(nVertice, mAdjacencia, vertice);

	for(i = 0; i < nAresta; i++)
	{
		scanf("%d %d %d",&v1,&v2,&peso);
		mAdjacencia[v1][v2] = peso;
		mAdjacencia[v2][v1] = peso;
	}

	//scanf("%d %d",&inicio,&fim);
	exibirMatriz(nVertice, mAdjacencia, vertice);
//	encontrarMenorCaminho(inicio, fim, nVertice, mAdjacencia, lambda);

	for(i = 0; i < nVertice; i++)
	{
		for(j = 0; j < nVertice; j++)
		{
			if(mAdjacencia[i][j] != infinite && mAdjacencia[i][j] != -1)
			{
				for(k = 0; k < nVertice; k++)
				{
					if(mAdjacencia[j][k] != infinite && mAdjacencia[j][k] != -1)
					{
						if(mAdjacencia[i][j]+mAdjacencia[j][k] < mAdjacencia[i][k])
						{
							mAdjacencia[i][k] = mAdjacencia[i][j]+mAdjacencia[j][k];
							mAdjacencia[k][i] = mAdjacencia[i][j]+mAdjacencia[j][k];
						}
					}
				}
			}	
		}		
	}
	exibirMatriz(nVertice, mAdjacencia, vertice);

	return 0;
}