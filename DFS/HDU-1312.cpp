// HDU-1312
#include <cstdio>
#include <cstring>
const int MAXN = 30;

using namespace std;

const int dx[] = { 1, 0, -1, 0 };
const int dy[] = { 0, 1, 0, -1 };

char room[MAXN][MAXN];
int w, h;

struct p
{
	int x;
	int y;
};

int dfs(p now)
{
    int ret = 0;
	room[now.y][now.x] = '#';
    ret++;
    
    p next;
    for (int i = 0; i < 4; i++)
    {
        next.x = now.x + dx[i];
        next.y = now.y + dy[i];
        if (next.x < w && next.x >= 0
				&& next.y < h && next.y >= 0
				&& room[next.y][next.x] == '.')
            {
                ret += dfs(next);
            }
    }
	
	return ret;
}

int main()
{
	scanf("%d%d", &w, &h);
	while (w || h)
	{
		getchar();
		memset(room, 0, sizeof(room));
		
		p begin;
		for (int i = 0; i < h; ++i)
		{
			for (int j = 0; j < w; ++j)
			{
				room[i][j] = getchar();
				if (room[i][j] == '@')
				{
					begin.x = j;
					begin.y = i;
				}
			}
			getchar();
		}
		
		printf("%d\n", dfs(begin));
		scanf("%d%d", &w, &h);
	}
	
	return 0;
}
