#include<stdio.h>
#include<time.h>
#include<stdlib.h>


int main(void)
{ int E, V, i, j, x, y, p, P, matriz[500][500];
	

	srand( (unsigned)time(NULL));
	
	scanf("%d%d%d", &V,&E,&P);
	
	for(i=0;i<V;i++)
		for(j=0;j<V;j++)
			matriz[i][j]= 0;
	
	printf("%d %d\n",V,E);
	
	for(i=0; i < E; i++)
	{
		do{
			x = rand() % V;
			do{
				y = rand() % V;
			}while(y == x);
		}while(matriz[x][y]);
		printf("%d %d ", x, y);
		p = (rand() % P)+1;
		matriz[x][y]=p;
		matriz[y][x]=p;
		printf("%d\n",p);
	}
	x = rand() % V;
	y = rand() % V;
	printf("%d %d\n", x, y);
	return 0;
}


	
