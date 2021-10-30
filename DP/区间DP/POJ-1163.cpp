// POJ-1163
// 解法没错，但是数据过大，单纯区间dp无法AC
// 需要优化为GarsiaWachs算法
#include <cstdio>
const int INF = 0x3f3f3f3f;
const int MAXN = 300;

using namespace std;

int sum[MAXN];
int n;

int MinVal()
{
    int dp[MAXN][MAXN];
    int s[MAXN][MAXN];
    for (int i = 1; i <= n; i++)
    {
        dp[i][i] = 0;
        s[i][i] = i;
    }

    for (int len = 1; len < n; len++)
    {
        for (int i = 1; i <= n - len; i++)
        {
            int j = i + len;
            dp[i][j] = INF;
            for (int k = s[i][j - 1]; k <= s[i + 1][j]; k++)
            {
                if (dp[i][k] + dp[k + 1][j] + sum[j] - sum[i - 1] < dp[i][j])
                {
                    dp[i][j] = dp[i][k] + dp[k + 1][j] + sum[j] - sum[i - 1];
                    s[i][j] = k;
                }
            }
        }
    }

    return dp[1][n];
}

int main()
{
    while (~scanf("%d", &n))
    {
        sum[0] = 0;
        for (int i = 1; i <= n; i++)
        {
            int temp;
            scanf("%d", &temp);
            sum[i] = sum[i - 1] + temp;
        }
        printf("%d\n", MinVal());
    }

    return 0;
}
