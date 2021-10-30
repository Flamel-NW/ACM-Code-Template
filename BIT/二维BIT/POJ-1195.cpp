// POJ-1195
#include <cstdio>

const int N = 2000;
const int INF = 0x3f3f3f3f;

typedef long long int lld;
using namespace std;

#define lowbit(x) ((x) & -(x))

int n;
int bitree[N][N];

void add(int x, int y, int d)
{
	for (int i = x; i < n + 1; i += lowbit(i))
		for (int j = y; j < n + 1; j += lowbit(j))
			bitree[i][j] += d;
}

int sum(int x, int y)
{
	int sum = 0;
	for (int i = x; i > 0; i -= lowbit(i))
		for (int j = y; j > 0; j -= lowbit(j))
			sum += bitree[i][j];

	return sum;
}

int main()
{
	scanf("%*d%d", &n);

	int ins;
	while (true)
	{
		scanf("%d", &ins);
		if (ins == 1)
		{
			int x, y, a;
			scanf("%d%d%d", &x, &y, &a);
			add(x + 1, y + 1, a);
		}
		else if (ins == 2)
		{
			int l, b, r, t;
			scanf("%d%d%d%d", &l, &b, &r, &t);
			printf("%d\n", sum(r + 1, t + 1) - sum(r + 1, b) - sum(l, t + 1) + sum(l, b));
		}
		else
			break;
	}

	return 0;
}

