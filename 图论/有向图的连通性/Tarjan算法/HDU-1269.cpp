// HDU-1269
// Tarjan算法
#include <bits/stdc++.h>
const int MAXN = 10005;

int cnt;
int low[MAXN], num[MAXN];
int dfn;
int sccno[MAXN];
int stack[MAXN], top;

std::vector<int> G[MAXN];

void dfs(int u)
{
	stack[top++] = u;
	low[u] = num[u] = ++dfn;
	for (int i = 0; i < G[u].size(); ++i)
	{
		int v = G[u][i];
		if (!num[v])
		{
			dfs(v);
			low[u] = std::min(low[u], low[v]);
		}
		else if (!sccno[v])
			low[u] = std::min(low[u], num[v]);
	}
	if (low[u] == num[u])
	{
		cnt++;
		while (true)
		{
			int v = stack[--top];
			sccno[v] = cnt;
			if (u == v)
				break;
		}
	}
}

void Tarjan(int n)
{
	cnt = top = dfn = 0;
	memset(sccno, 0, sizeof(sccno));
	memset(num, 0, sizeof(num));
	memset(low, 0, sizeof(low));

	for (int i = 1; i <= n; i++)
		if (!num[i])
			dfs(i);
}

int main()
{
	int n, m;
	int u, v;

	while (~scanf("%d%d", &n, &m) && (n != 0 || m != 0))
	{
		for (int i = 1; i <= n; i++)
			G[i].clear();
		for (int i = 0; i < m; i++)
		{
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
		}
		Tarjan(n);
		printf("%s\n", cnt == 1 ? "Yes" : "No");
	}

	return 0;
}
