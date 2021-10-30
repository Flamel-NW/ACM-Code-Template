// HDU-2544
// Bellman-Ford算法
#include <bits/stdc++.h>
const int INF = 0x3f3f3f3f;
const int MAXN = 105;
const int MAXM = 10005;

using namespace std;

struct Edge
{
	int u, v;
	int w;
} e[MAXM]; // 边：起点u，终点v，权值w

int n, m, cnt;
int pre[MAXN]; // 记录前驱结点。
// pre[x] = y————在最短路径上，结点x的前一个结点是y

void print_path(int s, int t) // 打印从s到t的最短路径
{
	if (s == t)
	{
		printf("%d", s); // 打印起点
		return;
	}
	print_path(s, pre[t]); // 先打印前一个点
	printf("%d ", t); // 后打印当前点，最后打印的是最终点t
}

void bellman()
{
	int d[MAXN]; // d[i]记录第i个结点到起点s的最短距离
	for (int i = 2; i <= n; i++)
		d[i] = INF; // 初始化为无穷大
	d[1] = 0;
	int k = 0; // 记录有几轮操作
	bool update = true; // 判断是否有更新
	while (update)
	{
		k++;
		update = false;
		if (k > n)
			exit(EXIT_FAILURE); // 有负圈，停止
		for (int i = 0; i < cnt; i++) // 检查每条边
		{
			int x = e[i].u, y = e[i].v;
			if (d[x] > d[y] + e[i].w) // x通过y到达起点s：如果距离更短，更新
			{
				update = true;
				d[x] = d[y] + e[i].w;
				pre[x] = y; // 如果有需要，记录路径
			}
		}
	}
	printf("%d\n", d[n]);
	// print_path(s, n); // 如果有需要，打印路径
}

int main()
{
	while (~scanf("%d%d", &n, &m))
	{
		if (n == 0 && m == 0)
			return 0;

		cnt = 0; // 记录边的数量。本题的边是双向的，共有2m条
		while (m--)
		{
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);

			e[cnt].u = a;
			e[cnt].v = b;
			e[cnt].w = c;
			cnt++;

			e[cnt].u = b;
			e[cnt].v = a;
			e[cnt].w = c;
			cnt++;
		}
		bellman();
	}
	return 0;
}
