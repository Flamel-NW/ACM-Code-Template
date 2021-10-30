// HDU-1401
// 双向广搜 + 哈希
#include <bits/stdc++.h>

const int dx[] = { 1, 0, -1, 0 };
const int dy[] = { 0, 1, 0, -1 };

char hash[8][8][8][8][8][8][8][8];
bool board[10][10];

struct p
{
    int x;
    int y;
};

struct state
{
    state() : step(0) { memset(ps, 0, sizeof(ps)); };
    void sort();
    void GetBoard() const;
    int GetHash(int way) const;
    bool judge() const;

    p ps[4];
    int step;
};

bool p_cmp(p a, p b)
{
    return a.x == b.x ? a.y > b.y : a.x > b.x;
}

inline void state::sort()
{
    std::sort(ps, ps + 4, p_cmp);
}

inline void state::GetBoard() const
{
    memset(board, 0, sizeof(board));
    for (int i = 0; i < 4; i++)
    {
        board[ps[i].x][ps[i].y] = true;
    }
}

inline int state::GetHash(int way) const 
{
    int ret = hash[ps[0].x][ps[0].y][ps[1].x][ps[1].y][ps[2].x][ps[2].y][ps[3].x][ps[3].y];
    hash[ps[0].x][ps[0].y][ps[1].x][ps[1].y][ps[2].x][ps[2].y][ps[3].x][ps[3].y] = way;
    return ret + way;
}

bool state::judge() const
{
    int ret = 0;
    for (int i = 0; i < 4; i++)
    {
        if (ps[i].x >= 8 || ps[i].x < 0 || 
            ps[i].y >= 8 || ps[i].y < 0)
        {
            return false;
        }
    }
    return ret != 4;
}

void show(state now)
{
    for (int i = 0; i < 4; i++)
    {
        printf("%d %d", now.ps[i].x, now.ps[i].y);
        putchar('\n');
    }
    printf("%d", now.step);
    putchar('\n');
}

bool solve(state begin, state end)
{
    using namespace std;

    begin.GetHash(1);
    if (end.GetHash(2) == 3)
    {
        return true;
    }

    queue<state> dbfs[2];
    dbfs[0].push(begin);
    dbfs[1].push(end);

    while (!dbfs[0].empty() && !dbfs[1].empty())
    {
        for (int i = 0; i < 2; i++)
        {
            state now = dbfs[i].front();
            dbfs[i].pop();
            now.GetBoard();
            if (now.step == 4)
            {
                break;
            }
            for (int j = 0; j < 4; j++)
            {
                for (int k = 0; k < 4; k++)
                {
                    state next = now;
                    next.ps[j].x += dx[k];
                    next.ps[j].y += dy[k];
                    next.step++;
                    if (next.judge())
                    {
                        if (board[next.ps[j].x][next.ps[j].y])
                        {
                            next.ps[j].x += dx[k];
                            next.ps[j].y += dy[k];
                            if (!next.judge() || board[next.ps[j].x][next.ps[j].y])
                            {
                                continue;
                            }
                        }
                        next.sort();
                        if (next.GetHash(i + 1) == 3)
                        {
                            return true;
                        }
                        dbfs[i].push(next);
                    }
                }
            }
        }
    }
    
    return false;
}

int main()
{
    state begin, end;

    while (~scanf("%d%d", &begin.ps[0].x, &begin.ps[0].y))
    {
        --begin.ps[0].x;
        --begin.ps[0].y;
        memset(hash, 0, sizeof(hash));
        for (int i = 1; i < 4; i++)
        {
            scanf("%d%d", &begin.ps[i].x, &begin.ps[i].y);
            --begin.ps[i].x;
            --begin.ps[i].y;
        }
        for (int i = 0; i < 4; i++)
        {
            scanf("%d%d", &end.ps[i].x, &end.ps[i].y);
            --end.ps[i].x;
            --end.ps[i].y;
        }
        begin.sort();
        end.sort();

        if (solve(begin, end))
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
    }

    return 0;
}
