#include 	<stdio.h>
#include	<stdlib.h>

#define max 500
#define infinito 999

typedef struct{
	int p; // peso
	int anc; // nó ancestral que leva a origem
	char cl; // está contido em lambda? 's' sim 'n' não
}Lambda;

void limparAd(int adjacencia[][max], int nv)
{
	int i, j;
	for(i = 0; i < nv; i++) // limpar a matriz de adjacencia
	{
		for(j = 0; j < nv; j++)
			adjacencia[i][j] = -1; // indicar
	}
}

void limparLd(Lambda lambda[], int nv)
{
	int i;
	for(i = 0; i < nv; i++) // limpar o 'lambda'
	{
		lambda[i].p = infinito;
		lambda[i].anc = -1; 
		lambda[i].cl = 'n';
	}
}

void menorCaminho(int ori, int des, int nv, int adjacencia[][max], Lambda lambda[])
{
	int at = ori, i;
	lambda[at].p = 0; 

	
	while(at != des)
	{
		lambda[at].cl = 's';

		for(i = 0; i < nv; i++)
		{
			if( adjacencia[at][i] != -1 && lambda[i].cl == 'n')
			{
				if( lambda[at].p + adjacencia[at][i] < lambda[i].p )
				{
					lambda[i].p = lambda[at].p + adjacencia[at][i];
					lambda[i].anc = at; 
				}

			}
		}

		at = proximo(lambda, nv);
		if(at == -1)
			break;
	}


}

int proximo(Lambda lambda[], int nv)
{
	int i, menor = -1;

	for (i = 0; i < nv; i++)
	{
		if(lambda[i].cl == 'n')
		{
			if( menor == -1 && lambda[i].anc != -1)
				menor = i;
			else if( lambda[i].p < lambda[menor].p  )
				menor = i;
	
		}
	}

	return menor;
}

void exibir(int des, Lambda * lambda)
{
	if(des == -1)
		return;
	exibir(lambda[des].anc, lambda);
	printf("%d ", des);
}

main()
{
	int adjacencia[max][max]; // Matriz de Adjacencia
	Lambda lambda[max]; // controle o peso de cada vértice e se o vértice tá em lambda


	int nv, na, i, ve1, ve2, p, ori, des; // at = atual, ori = origem, des = destino, p = peso

	scanf("%d%d", &nv, &na); // número de vértices e arestas

	limparAd(adjacencia, nv);
	limparLd(lambda, nv);
	

	for(i = 0; i < na; i++) // receber arestas
	{
		scanf("%d%d%d", &ve1, &ve2, &p);
		adjacencia[ve1][ve2] = p;
		adjacencia[ve2][ve1] = p;
	}

	scanf("%d%d",&ori,&des);
	menorCaminho(ori, des, nv, adjacencia, lambda);

	if(lambda[des].p == infinito)
		printf("\nnao ha caminho\n");
	else
	{
		printf("%d\n", lambda[des].p);
		exibir(des, lambda);
		printf("\n");
	}
		

	/*
	for (i = 0; i < nv; ++i)
	{
		printf("p:%d anc:%d cl:%c \n", lambda[i].p, lambda[i].anc, lambda[i].cl);
	}
	*/

	return 0;
}