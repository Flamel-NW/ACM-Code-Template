// HDU-1043 stage1 
#include <bits/stdc++.h>
using namespace std;

char input[1000];
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, -1, 0, 1 };
string d = "durl";
set<string> f;
map<string, string> m;
int sz = 0;

struct node
{
   string s;
   string path;
   int pos;

   node() = default;
   node(string str, string pa, int Pos) : s(str), path(pa), pos(Pos) { };
};

bool g(int a, int b)
{
    if (a >= 0 && a <=2 && b >= 0 && b <= 2)
    {
        return 1;
    }
    return 0;
}

void pre()
{
    queue<node> q;
    q.push(node("12345678x", "", 8));
    m["12345678x"] = "";
    f.insert("12345678x");

    while (!q.empty())
    {
        node h = q.front();
        q.pop();
        
        int a = h.pos / 3;
        int b = h.pos % 3;

        for (int i = 0; i < 4; i++)
        {
            int x = a + dx[i];
            int y = b + dy[i];
            if (!g(x, y))
            {
                continue;
            }
            int pos = 3 * x + y;
            swap(h.s[h.pos], h.s[pos]);
            if (f.find(h.s) != f.end())
            {
                swap(h.s[h.pos], h.s[pos]);
                continue;
            }
            q.push(node(h.s, d[i] + h.path, pos));
            f.insert(h.s);
            m[h.s] = d[i] + h.path;
            swap(h.s[h.pos], h.s[pos]);
        }
    }
}

int main()
{
    pre();
    while (~scanf("%s", input))
    {
        string v = "";
        v += input[0];
        for (int i = 1; i <= 8; i++)
        {
            scanf("%s", input);
            v += input[0];
        }
        if (m[v] == "")
        {
            printf("unsolvable\n");
        }
        else
        {
            printf("%s\n", m[v].c_str());
        }
    }

    return 0;
}

