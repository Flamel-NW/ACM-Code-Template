// HDU-2899
// 个人觉得三分法更好
#include <bits/stdc++.h>
const double EPS = 1e-8; // 终止温度

using namespace std;

double y;
double func(double x) // 计算函数值
{
    return 6 * pow(x, 7.0) + 8 * pow(x, 6.0) + 7 * pow(x, 3.0) + 5 * pow(x, 2.0) - y * x;
}

double solve()
{
    double T = 100; // 初始温度
    double delta = 0.98; // 降温系数
    double x = 50.0; // x的初始值
    double now = func(x); // 计算返回函数值
    double ans = now; // 返回值

    while (T > EPS) // EPS是终止温度
    {
        int f[2] = { 1, -1 };
        double newx = x + f[rand() % 2] * T; // 按概率改变x，随T的降温而减少
        if (newx >= 0 && newx <= 100)
        {
            double next = func(newx);
            ans = min(ans, next);
            if (now - next > EPS)
            {
                x = newx;
                now = next; // 更新x
            }
        }
        T *= delta;
    }

    return ans;
}

int main()
{
    int cas;
    scanf("%d", &cas);

    while (cas--)
    {
        scanf("%lf", &y);
        printf("%.4f\n", solve());
    }
}
