#include <cstdio>
#include <cstring>
const int MAXN = 50;

int graph[MAXN + 5][MAXN + 5];
int degree[MAXN + 5];

void euler(int u)
{
	for (int v = 1; v <= MAXN; v++)
		if (graph[u][v])
		{
			graph[u][v]--;
			graph[v][u]--;
			euler(v);
			printf("%d %d\n", v, u);
		}
}

int main()
{
	int t;
	scanf("%d", &t);

	for (int i = 1; i <= t; i++)
	{
		memset(graph, 0, sizeof(graph));
		memset(degree, 0, sizeof(degree));

		if (i == 1)
			printf("Case #1\n");
		else
			printf("\nCase #%d\n", i);

		int n;
		scanf("%d", &n);
		
		for (int j = 1; j <= n ; j++)
		{
			int u, v;
			scanf("%d%d", &u, &v);

			degree[u]++;
			degree[v]++;
			graph[u][v]++;
			graph[v][u]++;
		}

		for (int j = 1; j <= MAXN; j++)
			if (degree[j] % 2)
			{
				printf("some beads may be lost\n");
				break;
			}
			else if (j == MAXN)
				for (int k = 1; k <= MAXN; k++)
					euler(k);
	}

	return 0;
}