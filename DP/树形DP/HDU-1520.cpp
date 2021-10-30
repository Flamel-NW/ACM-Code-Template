//HDU 1520
#include <bits/stdc++.h>
const int MAXN = 1e4;

using namespace std;

int val[MAXN];
int dp[MAXN][2];
int dad[MAXN];

vector<int> tree[MAXN];

void dfs(int u)
{
	dp[u][0] = 0;
	dp[u][1] = val[u];
	for (int i = 0; i < tree[u].size(); i++)
	{
		int son = tree[u][i];
		dfs(son);
		dp[u][0] += max(dp[son][1], dp[son][0]);
		dp[u][1] += dp[son][0];
	}
}

int main()
{
	int n;

	while (~scanf("%d", &n))
	{
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &val[i]);
			tree[i].clear();
			dad[i] = -1;
		}
		while (true)
		{
			int a, b;
			scanf("%d%d", &a, &b);
			if (!a && !b)
			{
				break;
			}
			tree[b].push_back(a);
			dad[a] = b;
		}
		int t = 1;
		while (dad[t] != -1)
		{
			t = dad[t];
		}
		dfs(t);
		printf("%d\n", max(dp[t][1], dp[t][0]));
	}

	return 0;
}