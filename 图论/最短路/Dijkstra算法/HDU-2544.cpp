// HDU-2544
// Dijkstra算法
#include <bits/stdc++.h>
const int INF = 0x3f3f3f3f;
const int MAXN = 105; 

using namespace std;

struct edge // 边
{
	int from; // 起点（并没有用到，e[i]的i就是from）
	int to; // 终点
	int w; // 权值

	edge(int a, int b, int c) : from(a), to(b), w(c) { }
};

vector<edge> e[MAXN]; // 用于存储图

struct s_node
{
	int id; // id：结点
	int n_dis; // n_dis：这个结点到起点的距离

	s_node(int b, int c) : id(b), n_dis(c) { }
	bool operator< (const s_node & a) const
	{
		return n_dis > a.n_dis;
	}
};

int n, m;
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

void dijkstra()
{
	int s = 1; // 起点s是1
	int dis[MAXN]; // 记录所有结点到起点的距离
	bool done[MAXN]; // done[i] = true 表示到结点[i]的最短路径已经找到
	memset(dis, INF, sizeof(dis)); // 初始化
	memset(done, false, sizeof(done)); // 初始化
	dis[s] = 0; // 起点到自己的距离是0

	priority_queue<s_node> Q; // 优先队列，存结点信息
	Q.push(s_node(s, dis[s])); // 起点进队列
	while(!Q.empty())
	{
		s_node u = Q.top(); // pop出起点s距离最小的结点u
		Q.pop();
		if (done[u.id]) // 丢弃已经找到最短路径的结点，即集合A中的结点
			continue;
		done[u.id] = true;
		for (int i = 0; i < e[u.id].size(); i++) // 检查结点u的所有邻居
		{
			edge y = e[u.id][i]; // u.id的第i个邻居是y.to
			if (done[y.to]) // 丢弃已经找到最短路径的邻居结点
				continue;
			if (dis[y.to] > y.w + u.n_dis)
			{
				dis[y.to] = y.w + u.n_dis;
				Q.push(s_node(y.to, dis[y.to])); // 扩展新的邻居，放到优先队列中
				pre[y.to] = u.id; // 如果有需要，记录路径
			}
		}
	}
	printf("%d\n", dis[n]);
	// print_path(s, n); // 如果有需要，打印路径
}

int main()
{
	while (~scanf("%d%d", &n, &m))
	{
		if (!n && !m)
			return 0;
		for (int i = 1; i <= n; i++)
			e[i].clear();

		while(m--)
		{
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			e[a].push_back(edge(a, b, c)); // 结点a的邻居，都放在node[a]里
			e[b].push_back(edge(b, a, c)); // 结点b的邻居，都放在node[b]里
		}
		dijkstra();
	}

	return 0;
}
