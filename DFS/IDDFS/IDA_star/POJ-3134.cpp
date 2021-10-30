// POJ-3134
#include <cstdio>
#include <cmath>
const int MAXN = 1100;

using namespace std;

int vals[MAXN];
int pos, n;

bool ida_star(int now, int depth)
{
    if (now > depth) // IDDFS
    {
        return false;
    }
    if (vals[pos] << (depth - now) < n) // IDA_star
    {
        return false;
    }
    if (vals[pos] == n)
    {
        return true;
    }

    pos++;
    for (int i = 0; i < pos; i++)
    {
        vals[pos] = vals[pos - 1] + vals[i];
        if (ida_star(now + 1, depth))
        {
            return true;
        }
        vals[pos] = abs(double(vals[pos - 1] - vals[i]));
        if (ida_star(now + 1, depth))
        {
            return true;
        }
    }
    pos--;
    return false;
}

int main()
{
    while (~scanf("%d", &n) && n)
    {
        int depth;
        for (depth = 0; ; depth++)
        {
            pos = 0;
            vals[0] = 1;
            if (ida_star(0, depth))
            {
                break;
            }
        }
        printf("%d\n", depth);
    }

    return 0;
}
