// POJ-1163
#include <cstdio>
#include <cstring>
#include <algorithm>
const int MAXN = 150;

using namespace std;

int a[MAXN][MAXN];
int dp[MAXN][MAXN];
int n;

int dfs(int i,int j)
{
    return i == n ? a[i][j] :
        dp[i][j] >= 0 ? dp[i][j] : // 记忆！如果计算过，就不再递归计算
        dp[i][j] = max(dfs(i + 1, j), dfs(i + 1, j + 1)) + a[i][j];
    // 炫技代码
}

int main()
{
    scanf("%d", &n);
    memset(dp, -1, sizeof(dp));

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
    dfs(1, 1);
    printf("%d", dp[1][1]);
}
