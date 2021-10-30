// HDU-1213
#include <cstdio>
const int MAXN = 1050;

using namespace std;

int s[MAXN];
int height[MAXN]; // 合并的优化

void init_set() // 初始化
{
    for (int i = 1; i <= MAXN; i++)
    {
        s[i] = i;
        height[i] = 0; // 树的高度 // 合并的优化
    }
}

// int find_set(int x) // 查询
// {
//     return x == s[x] ? x : find_set(s[x]);
// }

int find_set(int x) // 查询的优化————路径压缩
{
    if (x != s[x])
    {
        s[x] = find_set(s[x]);
    }
    return s[x];
}

// int find_set(int x) // 查询的优化————路径压缩 // 非递归版
// {
//     int r = x;
//     while (s[r] != r) // 找到根结点
//     {
//         r = s[r];
//     }

//     int i = x;
//     int j;
//     while (i != r)
//     {
//         j = s[i]; // 用临时变量 j 记录
//         s[i] = r; // 把路径上的元素的集改为根结点
//         i = j;
//     }
//     return r;
// }

// void union_set(int x, int y) // 合并
// {
//     s[find_set(x)] = find_set(y);
// }

void union_set(int x, int y) // 合并的优化
{
    x = find_set(x);
    y = find_set(y);

    if (height[x] == height[y])
    {
        height[x] = height[y] + 1; // 合并。 树的高度+1
        s[y] = x;
    }
    else
    {
        height[x] < height[y] ? s[x] = y : s[y] = x; // 把矮树并到高树上，高树的高度保持不变
    }
}

int main()
{
    int t;
    scanf("%d", &t);

    while (t--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        init_set();
        
        for (int i = 1; i <= m; i++)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            union_set(x, y);
        }

        int ans = 0;
        for (int i = 1; i <= n; i++)
        {
            if (s[i] == i)
            {
                ans++;
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}
