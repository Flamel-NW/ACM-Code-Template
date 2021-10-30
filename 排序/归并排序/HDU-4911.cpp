// HDU-4911
// 归并排序（求逆序对）
#include <bits/stdc++.h>
const int MAXN = 1.1e5;

typedef long long lld;

lld a[MAXN], temp[MAXN];
lld ans;

void Merge(lld l, lld mid, lld r)
{
    lld i = l;
    lld j = mid + 1;
    lld t = 0;

    while (i <= mid && j <= r)
    {
        if (a[i] > a[j])
        {
            temp[t++] = a[j++];
            ans += mid + 1 - i; // 记录逆序对数量
        }
        else
        {
            temp[t++] = a[i++];
        }
    }
    // 一个子序列中的数都处理完了，另一个还没有，把剩下的直接复制过来
    while (i <= mid)
    {
        temp[t++] = a[i++];
    }
    while (j <= r)
    {
        temp[t++] = a[j++];
    }

    for(i = 0; i < t; i++)
    {
        a[l + i] = temp[i]; // 把排好序的temp[]，复制回a[]
    }
}

void MergeSort(lld l, lld r)
{
    if (l < r)
    {
        lld mid = (l + r) >> 1; // 平分成两个子序列
        MergeSort(l, mid);
        MergeSort(mid + 1, r);
        Merge(l, mid, r); // 合并
    }
}

int main()
{
    lld n, k;

    while (~scanf("%lld%lld", &n, &k))
    {
        ans = 0;
        for (lld i = 1; i <= n; i++)
        {
            scanf("%lld", &a[i]);
        }
        MergeSort(1, n); // 归并排序
        if (ans <= k)
        {
            printf("0\n");
        }
        else
        {
            printf("%lld\n", ans - k);
        }
    }

    return 0;
}
