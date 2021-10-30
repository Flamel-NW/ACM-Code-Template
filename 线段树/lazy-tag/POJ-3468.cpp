// POJ-3468
#include <cstdio>
const int MAXN = 1.1e5;

typedef long long int lld;

lld sum[MAXN << 2], add[MAXN << 2]; // 4倍空间

void push_up(int rt) // 向上更新，通过当前结点rt把值递归到父结点
{
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}

void push_down(int rt, int m) // 更新rt的子结点
{
    if (add[rt])
    {
        add[rt << 1] += add[rt];
        add[rt << 1 | 1] += add[rt];

        sum[rt << 1] += (m - (m >> 1)) * add[rt];
        sum[rt << 1 | 1] += (m >> 1) * add[rt];

        add[rt] = 0; // 取消本层标记
    }
}

#define lson l, mid, rt << 1
#define rson mid + 1, r, rt << 1 | 1

void build(int l, int r, int rt) // 用满二叉树建树
{
    add[rt] = 0;
    if (l == r) // 叶子结点，赋值
    {
        scanf("%lld", &sum[rt]);
        return;
    }
    
    int mid = (l + r) >> 1;
    build(lson);
    build(rson);
    push_up(rt); // 向上更新区间和
}

void update(int a, int b, lld c, int l, int r, int rt) // 区间更新
{
    if (a <= l && b >= r)
    {
        sum[rt] += (r - l + 1) * c;
        add[rt] += c;
        return;
    }

    push_down(rt, r - l + 1); // 向下更新
    int mid = (l + r) >> 1;
    if (a <= mid) // 分成两半，继续深入
    {
        update(a, b, c, lson);
    }
    if (b > mid)
    {
        update(a, b, c, rson);
    }
    push_up(rt); // 向上更新
}

lld query(int a, int b, int l, int r, int rt) // 区间求和
{
    if (a <= l && b >= r) // 满足lazy，直接返回值
    {
        return sum[rt];
    }

    push_down(rt, r - l + 1); // 向下更新
    int mid = (l + r) >> 1;
    lld ans = 0;
    if (a <= mid)
    {
        ans += query(a, b, lson);
    }
    if (b > mid)
    {
        ans += query(a, b, rson);
    }

    return ans;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);

    build(1, n, 1);
    while (m--)
    {
        char str[2];
        int a, b;
        lld c;
        scanf("%s", str);

        if (str[0] == 'C')
        {
            scanf("%d%d%lld", &a, &b, &c);
            update(a, b, c, 1, n, 1);
        }
        else
        {
            scanf("%d%d", &a, &b);
            printf("%lld\n", query(a, b, 1, n, 1));
        }
    }

    return 0;
}
