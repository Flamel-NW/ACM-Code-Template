// POJ-3280
#include <cstdio>
#include <algorithm>
const int MAXN = 2005;
const int MAXL = 30;

using namespace std;

int n, m;
int w[MAXL];
int dp[MAXN][MAXN];
char s[MAXN];

int main()
{
    char ch;
    int x, y;

    while (~scanf("%d%d", &n, &m))
    {
        scanf("%s", s);
        while (getchar() != '\n')
        {
            continue;
        }
        for (int i = 0; i < n; i++)
        {
            scanf("%c%d%d", &ch, &x, &y);
            w[ch - 'a'] = min(x, y);
            while (getchar() != '\n')
            {
                continue;
            }
        }
        for (int i = m - 1; i >= 0; i--)
        {
            for (int j = i + 1; j < m; j++)
            {
                if (s[i] == s[j])
                {
                    dp[i][j] = dp[i + 1][j - 1];
                }
                else
                {
                    dp[i][j] = min(dp[i + 1][j] + w[s[i] - 'a'], dp[i][j - 1] + w[s[j] - 'a']);
                }
            }
        }
        printf("%d\n", dp[0][m - 1]);
    }

    return 0;
}
