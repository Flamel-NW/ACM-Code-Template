// POJ-2182
#include <cstdio>
#include <cstring>
const int MAXN = 10000;
int tree[MAXN];
int pre[MAXN], ans[MAXN];
int n;

#define lowbit(x) ((x) & -(x))

void add(int x, int d)
{
    while (x <= n)
    {
        tree[x] += d;
        x += lowbit(x);
    }
}

int sum(int x)
{
    int sum = 0;

    while (x > 0)
    {
        sum += tree[x];
        x -= lowbit(x);
    }

    return sum;
}

int findpos(int x) // 寻找 sum(x) = pre[i] + 1 所对应的x，就是第x头牛
{
    int l = 1;
    int r = n;

    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (sum(mid) < x)
        {
            l = mid + 1;
        }
        else
        {
            r = mid;
        }
    }

    return l;
}

int main()
{
    scanf("%d", &n);
    pre[1] = 0;
    for (int i = 2; i <= n; i++)
    {
        scanf("%d", &pre[i]);
    }
    for (int i = 1; i <= n; i++) // 初始化tree[]数组
    // 注意这个题目比较特殊，不需要用add[]初始化，因为lowbit(i)就是tree[i]
    {
        tree[i] = lowbit(i);
    }

    for (int i = n; i > 0; i--)
    {
        int x = findpos(pre[i] + 1);
        add(x, -1); // 更新tree[]数组
        ans[i] = x;
    }
    for (int i = 1; i <= n; i++)
    {
        printf("%d\n", ans[i]);
    }
    
    return 0;
}
