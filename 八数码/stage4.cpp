// HDU-1043 stage4
#include <cstdio>
#include <queue>
#include <cstring>
#include <cctype>
const int MAXN = 4e5;
const int MAXL = 50;
const int factory[] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880 };

using namespace std;

int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };
const char dir[] = { 'r', 'd', 'l', 'u' };

struct state
{
	int eight[9];
	int hash;
	char move;
};
state came_from[3][MAXN];

int Cantor(int eight[])
{
	int result = 0;
	for (int i = 0; i < 9; i++)
	{
		int counted = 0;
		for (int j = i + 1; j < 9; j++)
		{
			if (eight[i] > eight[j])
			{
				++counted;
			}
		}
		result += counted * factory[8 - i];
	}

	return result;
}

int inversion(int eight[])
{
	int ret = 0;
	for (int i = 1; i < 9; i++)
	{
		if (eight[i] == 9)
		{
			continue;
		}
		for (int j = 0; j < i; j++)
		{
			if (eight[j] == 9)
			{
				continue;
			}
			if (eight[i] < eight[j])
			{
				ret++;
			}
		}
	}
	
	return ret;
}

state solve(state begin, state end)
{
	if (begin.hash == end.hash)
	{
		return begin;
	}
	
	queue<state> dbfs[3];
	dbfs[1].push(begin);
	dbfs[2].push(end);
	
	while (!dbfs[1].empty() && !dbfs[2].empty())
	{
		state now[3];
		now[1] = dbfs[1].front();
		now[2] = dbfs[2].front();
		dbfs[1].pop();
		dbfs[2].pop();

		if (now[1].hash == now[2].hash)
		{
			return now[1];
		}

		for (int j = 1; j <= 2; j++)
		{
			int z;
			for (z = 0; z < 9; z++)
			{
				if (now[j].eight[z] == 9)
				{
					break;
				}
			}
			int x = z % 3;
			int y = z / 3;

			for (int i = 0; i < 4; i++)
			{
				int newx = x + dx[i];
				int newy = y + dy[i];
				int newz = newx + 3 * newy;

				if (newx >= 0 && newx < 3 && newy >= 0 && newy < 3)
				{
					state next = now[j];
					swap(next.eight[z], next.eight[newz]);
					next.move = dir[i];

					next.hash = Cantor(next.eight);
					if (!next.hash)
					{
						came_from[j][next.hash] = now[j];
						return next;
					}
					if (!came_from[j][next.hash].hash)
					{
						came_from[j][next.hash] = now[j];
						dbfs[j].push(next);
					}
				}
			}
		}
	}
}

void reconstruct(state begin, state meet, state end)
{
	char path[3][MAXL];
	int node[3];
	node[0] = begin.hash;
	node[1] = meet.hash;
	node[2] = end.hash;
	path[1][0] = meet.move;
	path[2][0] = meet.move;
	int di[] = { 0, -1, 1 };

	for (int j = 1; j <= 2; j++)
	{
		int current = node[1];
		int start = node[1 + di[j]];

		int i;
		for (i = 1; i < MAXL && current != start; i++)
		{
			path[j][i] = came_from[j][current].move;
			current = came_from[j][current].hash;
		}

		if (j == 1)
		{
			i--;
			while (i)
			{
				putchar(path[j][--i]);
			}
		}
		else
		{
			for (int k = 0; k < i - 1; k++)
			{
				putchar(path[j][k]);
			}
		}
	}
}

int main()
{
	state begin, end, meet;
	char temp[MAXL];

	while (fgets(temp, MAXL, stdin))
	{
		memset(came_from, 0, sizeof(came_from));
		char * ptr = temp;
		for (int i = 0; i < 9; )
		{
			if (isdigit(*ptr))
			{
				begin.eight[i++] = *ptr - '0';
			}
			if (*ptr == 'x')
			{
				begin.eight[i++] = 9;
			}
			ptr++;
		}
		
		if (inversion(begin.eight) % 2)
		{
			printf("unsolvable\n");
			continue;
		}

		begin.hash = Cantor(begin.eight);
		came_from[1][begin.hash] = state();
		begin.move = 0;
		
		end.hash = 0;
		came_from[2][end.hash] = state();
		end.move = 0;
		
		meet = solve(begin, end);
		reconstruct(begin, meet, end);
	}

	return 0;
}

