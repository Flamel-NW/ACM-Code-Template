// UVA-437
// 经典dp，构建DAG求最长路
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

const int N = 100;
const int INF = 0x3f3f3f3f;

typedef long long int lld;
using namespace std;

int kase;
int n;
int x[N], y[N], z[N];

int g[N][N];
int d[N];

int dp(int i)
{
	int& ans = d[i];
	if (ans > 0)
		return ans;
	ans = z[i];
	for (int j = 1; j <= 3 * n; j++)
		if (g[i][j])
			ans = max(ans, dp(j) + z[i]);
	return ans;
}

int main()
{
	while (~scanf("%d", &n) && n)
	{
		memset(d, 0, sizeof(d));
		memset(g, 0, sizeof(g));

		for (int i = 1; i <= n; i++)
		{
			int temp[3];
			scanf("%d%d%d", &temp[0], &temp[1], &temp[2]);

			x[3 * i] = temp[0];
			y[3 * i] = temp[1];
			z[3 * i] = temp[2];

			x[3 * i - 1] = temp[1];
			y[3 * i - 1] = temp[2];
			z[3 * i - 1] = temp[0];

			x[3 * i - 2] = temp[2];
			y[3 * i - 2] = temp[0];
			z[3 * i - 2] = temp[1];
		}

		for (int i = 1; i <= 3 * n; i++)
			for (int j = 1; j <= 3 * n; j++)
				if ((x[i] > x[j] && y[i] > y[j])
					|| (x[i] > y[j] && y[i] > x[j]))
					g[i][j] = true;

		for (int i = 1; i <= 3 * n; i++)
			dp(i);

		printf("Case %d: maximum height = %d\n", ++kase
			, *max_element(d + 1, d + 1 + 3 * n));
	}

	return 0;
}
