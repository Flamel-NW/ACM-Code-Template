// HDU-2553
// 注意打表法的使用
// 注意全局变量的使用
#include <bits/stdc++.h>
const int MAXN = 15;

using namespace std;

int cols[MAXN];
int n, tot;

bool check(int r, int c)
{
    for (int i = 0; i < r; i++)
    {
        if (cols[i] == c || abs(cols[i] - c) == abs(i - r))
        {
            return false;
        }
    }
    return true;
}

void dfs(int r)
{
    if (r == n)
    {
        tot++;
        return;
    }

    for (int c = 0; c < n; c++)
    {
        if (check(r, c))
        {
            cols[r] = c;
            dfs(r + 1);
        }
    }
}

int main()
{
    int ans[MAXN] = { 0 };
    for (n = 0; n <= 10; n++)
    {
        memset(cols, 0, sizeof(cols));
        tot = 0;
        dfs(0);
        ans[n] = tot;
    }

    while ((~scanf("%d", &n)) && n)
    {
        printf("%d\n", ans[n]);
    }

    return 0;
}