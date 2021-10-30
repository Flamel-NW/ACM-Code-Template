// HDU-2602
#include <bits/stdc++.h>
const int MAXN = 1100;

using namespace std;

struct BONE{
	int val;
	int vol;
} bones[MAXN];

int T, N, V;
int dp[MAXN];

int ans()
{
	memset(dp, 0, sizeof(dp));
	
	for (int i = 0; i < N; i++)
	{
		for (int j = V; j >= bones[i].vol; j--)
		{
			dp[j] = max(dp[j], dp[j - bones[i].vol] + bones[i].val);
		}
	}
	
	return dp[V];
}

int main()
{
	scanf("%d", &T);
	
	while(T--)
	{
		scanf("%d%d", &N, &V);
		for (int i = 0; i < N; i++)
		{
			scanf("%d", &bones[i].val);
		}
		for (int i = 0; i < N; i++)
		{
			scanf("%d", &bones[i].vol);
		}
		printf("%d\n", ans());
	}
	
	return 0;
}