//HDU 1285
#include <cstdio>
#include <queue>
#include <cstring>
const int MAXN = 500;

using namespace std;

bool graph[MAXN][MAXN];
int in[MAXN];

void solve(int n)
{
	priority_queue<int, vector<int>, greater<int>> bfs;
	for (int i = 1; i <= n; i++)
	{
		if (!in[i])
		{
			bfs.push(i);
		}
	}
	
	while (!bfs.empty())
	{
		int now = bfs.top();
		bfs.pop();
		printf("%d", now);

		for (int i = 1; i <= n; i++)
		{
			if (graph[now][i])
			{
				in[i]--;
				if (!in[i])
				{
					bfs.push(i);
				}
			}
		}
		putchar(bfs.empty() ? '\n' : ' ');
	}
}

int main()
{
	int n, m;
	
	while (~scanf("%d%d", &n, &m))
	{
		memset(graph, 0, sizeof(graph));
		memset(in, 0, sizeof(in));
		while (m--)		
		{
			int a, b;
			scanf("%d%d", &a, &b);
			if (!graph[a][b])
			{
				in[b]++;
			}
			graph[a][b] = 1;
		}
		solve(n);
	}

	return 0;
}