// POJ-3134
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
typedef long long int lld;
const lld MAXN = 1100;
const lld MAXB = 1e13;

using namespace std;

lld min(lld a, lld b)
{
    return (a > b) ? b : a;
}

lld gcd(lld a, lld b)
{
    if (a < b)
    {
        lld temp = a;
        a = b;
        b = temp;
    }
    return b ? gcd(b, a % b) : a;
}

lld lcm(lld a, lld b)
{
    if (a < b)
    {
        lld temp = a;
        a = b;
        b = temp;
    }
    return a * b / gcd(a, b);
}

struct fraction
{
    fraction() = default;
    fraction(lld m, lld n) : a(m), b(n) { };

    lld a;
    lld b;
};

fraction operator+(fraction x, fraction y)
{
    fraction ret;

    ret.b = lcm(x.b, y.b);
    ret.a = ret.b / x.b * x.a + ret.b / y.b * y.a;

    lld g = gcd(ret.b, ret.a);
    ret.b /= g;
    ret.a /= g;

    return ret;
}

fraction operator-(fraction x, fraction y)
{
    fraction ret;

    ret.b = lcm(x.b, y.b);
    ret.a = ret.b / x.b * x.a - ret.b / y.b * y.a;

    lld g = gcd(ret.b, ret.a);
    ret.b /= g;
    ret.a /= g;

    return ret;
}

lld vals[MAXN];
lld solve[MAXN];
fraction n;
lld pos;

bool ida_star(lld now, lld depth, fraction remain)
{
    if (now == depth) // IDDFS
    {
        if (remain.a != 1 || remain.b <= vals[now])
        {
            return false;
        }
        if (remain.b < solve[now + 1])
        {
            memcpy(solve, vals, sizeof(lld) * (depth + 1));
            solve[now + 1] = remain.b;
            return true;
        }
        return false;
    }
    
    bool find = false;
    lld end = (depth - now + 1.0) / ((double)remain.a / remain.b) + 2;
    pos++;
    vals[pos] = vals[pos - 1] + 1;
    do
    {
        if (remain.a * vals[pos] > remain.b && 
            ida_star(now + 1, depth, remain - fraction(1, vals[pos])))
        {
            find = true;
        }
    } while (++vals[pos] < end);
    pos--;
    return find;
}

int main()
{
    scanf("%lld%lld", &n.a, &n.b);

    lld g = gcd(n.b, n.a);
    n.b /= g;
    n.a /= g;
    
    lld depth;
    for (depth = 0; ; depth++)
    {
        memset(vals, 0, sizeof(vals));
        for (int i = 0; i <= depth + 1; i++)
        {
            solve[i] = MAXB;
        }
        pos = 0;
        vals[0] = 1;
        if (ida_star(0, depth, n))
        {
            break;
        }
    }
    for (lld i = 1; solve[i] < MAXB && solve[i]; i++)
    {
        printf("%d ", solve[i]);
    }
    
    return 0;
}
