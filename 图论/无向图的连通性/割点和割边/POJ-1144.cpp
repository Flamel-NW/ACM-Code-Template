// POJ-1144
// Tarjan算法
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

const int MAXN = 109;

using namespace std;

int low[MAXN], num[MAXN];
int dfn; // 时间戳：记录进入递归的顺序。用于给num赋值
bool iscut[MAXN];
vector<int> graph[MAXN]; // 存图

void dfs(int u, int dad) // u的父结点是dad
{
    low[u] = num[u] = ++dfn;
    int child = 0;
    for (int i = 0; i < graph[u].size(); i++)
    {
        int v = graph[u][i];
        if (!num[v]) // v没访问过
        {
            child++;
            dfs(v, u);
            low[u] = min(low[v], low[u]); // 用后代的返回值更新low值

            if (low[v] >= num[u] && u != 1)
                iscut[u] = true; // 标记割点
        }
		else if (num[v] < num[u] && v != dad)
                // 处理回退边，注意这里 v != dad，dad是u的父结点，dad也是u的邻居，但是前面已经访问过，不需要再处理它
			low[u] = min(low[u], num[v]);
    }
    if (u == 1 && child >= 2)
        iscut[1] = true; // 根节点，有两个以上不相连的子树
}

int main()
{
    int ans;
    int n;

    scanf("%d", &n);
    while (n)
    {
        memset(low, 0, sizeof(low));
        memset(num, 0, sizeof(num));
        memset(iscut, false, sizeof(iscut));
        dfn = 0;
        ans = 0;
        for (int i = 0; i < MAXN; i++)
            graph[i].clear();

        int m = n;
        while (true)
        {
            int i;
            scanf("%d", &i);
            if (!i)
                break;
            while (true)
            {
                int j;
                scanf("%d", &j);
                graph[i].push_back(j);
                graph[j].push_back(i);
                if (getchar() == '\n')
                    break;
            }
        }
        
        dfs(1, -1); // DFS的起点是1
        for (int i = 1; i <= n; i++)
            ans += iscut[i];
        printf("%d\n", ans);
        scanf("%d", &n);
    }


    return 0;
}