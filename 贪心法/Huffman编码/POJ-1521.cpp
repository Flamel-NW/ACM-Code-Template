// POJ-1521
// 和网上的题解对拍出来的结果完全一致，但OJ上过不了
#include <cstdio>
#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

int main()
{
    string s;
    priority_queue<int, vector<int>, greater<int> > q;
    // 优先级队列，最小的在队首

    while (getline(cin, s) && s != "END") // 输入字符串
    {
        int t = 1;
        sort(s.begin(), s.end());
        for (int i = 1; i < s.length(); i++) // 统计字符出现的频次，并放进优先级队列
        {
            if (s[i] != s[i - 1])
            {
                q.push(t);
                t = 1;
            }
            else
            {
                t++;
            }
        }
        q.push(t);
        int ans = q.size() == 1 ? 1 : 0;
        while (q.size() > 1)
        {
            int a = q.top(); // 提取队列中最小的两个
            q.pop();
            int b = q.top();
            q.pop();
            q.push(a + b);
            ans += a + b; // 直接计算编码的总长度
        }
        q.pop();

        int ascii = s.size() * CHAR_BIT;
        printf("%d %d %.1f\n", ascii, ans, double(ascii) / ans);
    }
}
