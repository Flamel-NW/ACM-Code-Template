// HDU-2069
#include <bits/stdc++.h>
const int COIN = 101; 
const int MONEY = 251; // 这两个数一个都不能改！！！
const int TYPE[] = { 1, 5, 10, 25, 50 };

int dp[MONEY][COIN];

void solve()
{
    dp[0][0] = 1;
    for (int k = 0; k < 5; k++)
    {
        for (int j = 1; j < COIN; j++)
        {
            for (int i = TYPE[k]; i < MONEY; i++)    
            {
                dp[i][j] += dp[i - TYPE[k]][j - 1];
            }
        }
    }
}

int main()
{
    int s;
    int ans[MONEY];
    memset(ans, 0, sizeof(ans));
    solve();
    for (int i = 0; i < MONEY; i++)
    {
        for (int j = 0; j < COIN; j++)
        {
            ans[i] += dp[i][j];
        }
    }

    while (~scanf("%d", &s))
    {
        printf("%d\n", ans[s]);
    }

    return 0;
}
