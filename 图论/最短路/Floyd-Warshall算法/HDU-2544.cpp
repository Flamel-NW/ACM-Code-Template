// HDU-2544
// Floyd-Warshall算法
#include <bits/stdc++.h>
const int INF = 0x3f3f3f3f; // 路口之间的初始距离，看成无穷大，相当于断开
const int MAXN = 105;

using namespace std;

int graph[MAXN][MAXN]; // 邻接矩阵存图
int n, m;

void floyd()
{
	int s = 1; // 定义起点
	for (int k = 1; k <= n; k++) // floyd()的三重循环
		for (int i = 1; i <= n; i++)
			if (graph[i][k] != INF) // 一个小优化，在HDU-1704题中很必要
				for (int j = 1; j <= n; j++)
					if (graph[i][j] > graph[i][k] + graph[k][j])
						graph[i][j] = graph[i][k] + graph[k][j];
					// graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
					// 上面两句这样写也行，但是min()比较慢，如果图大，可能会超时
	printf("%d\n", graph[s][n]); // 输出结果
}

int main()
{
	while (~scanf("%d%d", &n, &m))
	{
		if (n == 0 && m == 0)
			return 0;
		for (int i = 1; i <= n; i++) // 邻接矩阵初始化
			for (int j = 1; j <= n; j++)
				graph[i][j] = INF; // 任意两点间的初始距离为无穷大
		
		while (m--)
		{
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			graph[a][b] = graph[b][a] = c; // 邻接矩阵存图
		}
		floyd();
	}
	return 0;
}
