// POJ-2388
#include <cstdio>
const int MAXN = 11000;

int data[MAXN];

#define swap(a, b) { int temp = a; a = b; b = temp; } // 交换

int partition(int left, int right) // 划分成左、右两部分，以i指向的数为界
{
    int i = left;
    int temp = data[right]; // 把尾部的数看成基准数
    for (int j = left; j < right; j++)
    {
        if (data[j] < temp)
        {
            swap(data[j], data[i]);
            i++;
        }
    }
    swap(data[i], data[right]);
    return i; // 返回基准数的位置
}

void QuickSort(int left, int right)
{
    if (left < right)
    {
        int i = partition(left, right); // 划分
        QuickSort(left, i - 1); // 分治：i左边的继续递归划分
        QuickSort(i + 1, right); // 分治：i右边的继续递归划分
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &data[i]);
    }
    QuickSort(1, n);
    printf("%d\n", data[(n + 1) >> 1]);

    return 0;
}
