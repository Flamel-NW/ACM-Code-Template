// HDU-2544
// SPFA算法 + 链式前向星
#include <bits/stdc++.h>
const int INF = 0x3f3f3f3f;
const int MAXN = 1000005; // HDU-1535：100万个点，100万个边

using namespace std;

struct Edge // 边：edge[i]的i就是起点，终点to，权值w。下一个边next
{
	int to;
	int next;
	int w;
} edge[MAXN];

int n, m;
int cnt;
int head[MAXN];
int dis[MAXN]; // 记录所有结点到起点的距离
bool inq[MAXN]; // inq[i] = true 表示结点i在队列中
int nl[MAXN]; // 判断负圈(negative loop)
int pre[MAXN]; // 记录前驱结点

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

void init()
{
	for (int i = 0; i < MAXN ; ++i)
	{
		edge[i].next = -1;
		head[i] = -1;
	}
	cnt = 0;
}

void addedge(int u, int v, int w) // 前向星存图
{
	edge[cnt].to = v;
	edge[cnt].w = w;
	edge[cnt].next = head[u];
	head[u] = cnt++;
}

void spfa(int s)
{
	memset(nl, 0, sizeof(nl));
	nl[s] = 1;
	for (int i = 1; i <= n; i++) // 初始化
	{
		dis[i] = INF;
		inq[i] = false;
	}
	dis[s] = 0; // 起点到自己的距离是0
	queue<int> Q;
	Q.push(s);
	inq[s] = true; // 起点进队列

	while(!Q.empty())
	{
		int u = Q.front();
		Q.pop(); // 队头出队
		inq[u] = false;
		for (int i = head[u]; ~i; i = edge[i].next) // ~i 也可以写成 i != -1
		{
			int v = edge[i].to, w = edge[i].w;
			if (dis[u] + w < dis[v]) // u的第i个邻居v，它借道u，到s更近
			{
				dis[v] = dis[u] + w; // 更新第i个邻居到s的距离
				pre[v] = u; // 如果有需要记录路径
				if (!inq[v])
				{
					inq[v] = true;
					Q.push(v);
					nl[v]++;
					if (nl[v] > n)
						exit(EXIT_FAILURE); // 出现负圈
				}
			}
		}
	}
	printf("%d\n", dis[n]); // 从s到n的最短距离
	// print_path(s, n); // 如果有需要，打印路径
}

int main()
{
	while (~scanf("%d%d", &n, &m))
	{
		init();
		if (!n && !m)
			return 0;
		
		while(m--)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			addedge(u, v, w);
			addedge(v, u, w);
		}
		spfa(1);
	}

	return 0;
}
