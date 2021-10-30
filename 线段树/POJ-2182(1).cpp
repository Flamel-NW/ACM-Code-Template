// POJ-2182
// 用结构体实现线段树
#include <cstdio>
const int MAXN = 10000;

struct 
{
    int l, r;
    int len; // 用len存储这个区间的数字个数，即这个结点下牛的数量
} tree[4 * MAXN]; // 这里是4倍， 因为线段树的空间需要
int pre[MAXN], ans[MAXN];

void BuildTree(int left, int right, int u) // 建树
{
    tree[u].l = left;
    tree[u].r = right;
    tree[u].len = right - left + 1; // 更新结点u的值

    if (left == right)
    {
        return;
    }

    BuildTree(left, (left + right) >> 1, u << 1); // 递归左子树
    BuildTree(((left + right) >> 1) + 1, right, (u << 1) + 1); // 递归右子树
}

int query(int u, int num) // 查询 + 维护，所求值为当前区间中左起第num个元素
{
    tree[u].len--; // 对访问到的区间维护len，即把这个结点上牛的数量减一
    if (tree[u].l == tree[u].r)
    {
        return tree[u].l;
    }
    
    // 情况1：左子区间内牛的个数不够，则查询右子区间中左起第num - tree[u << 1].len个元素
    if (tree[u << 1].len < num)
    {
        return query((u << 1) + 1, num - tree[u << 1].len);
    }
    // 情况2：左子区间内牛的数量足够，依旧查询左子区间中左起第num个元素
    if (tree[u << 1].len >= num)
    {
        return query(u << 1, num);
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    pre[1] = 0;
    for (int i = 2; i <= n; i++)
    {
        scanf("%d", &pre[i]);
    }
    BuildTree(1, n, 1);
    for (int i = n; i >= 1; i--) // 从后往前推断出每次最后一个数字 // 这样推断出来后去除这个数不会对前面的pre产生影响
    {
        ans[i] = query(1, pre[i] + 1);
    }
    for (int i = 1; i <= n; i++)
    {
        printf("%d\n", ans[i]);
    }

    return 0;
}
