// POJ-3352
// Tarjan算法
#include <cstdio>
#include <vector>
#include <cstring>
const int MAXN = 1005;

using namespace std;

int n, m;
int low[MAXN];
int dfn;
vector<int> graph[MAXN]; // 存图

void dfs(int u, int dad) // 计算每个点的low值
{
    low[u] = ++dfn;
    for (int i = 0; i < graph[u].size(); i++)
    {
        int v = graph[u][i];
        if (v == dad)
            continue;
        if (!low[v])
            dfs(v, u);
        low[u] = min(low[u], low[v]);
    }
}

int tarjan()
{
    int degree[MAXN]; // 计算每个缩点的度数
    memset(degree, 0, sizeof(degree));

    for (int i = 1; i <= n; i++) // 把有相同low值的点看成一个缩点
        for (int j = 0; j < graph[i].size(); j++)
            if (low[i] != low[graph[i][j]])
                degree[low[i]]++;
    
    int res = 0;
    for (int i = 1; i <= n; i++) // 统计度数为1的缩点的个数
        if (degree[i] == 1)
            res++;
    return (res + 1) / 2;
}

int main()
{
    while (~scanf("%d%d", &n, &m))
    {
        memset(low, 0, sizeof(low));
        for (int i = 0; i <= n; i++)
            graph[i].clear();
        
        for (int i = 1; i <= m; i++)
        {
            int a, b;
            scanf("%d%d", &a, &b);
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        dfn = 0;
        dfs(1, -1);
        printf("%d\n", tarjan());
    }

    return 0;
}