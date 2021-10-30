// HDU-1043 stage2
#include <cstdio>
#include <cstring>
#include <queue>
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
state came_from[MAXN];

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

state solve(state begin)
{
	queue<state> bfs;
	bfs.push(begin);

	if (!begin.hash)
	{
		return begin;
	}

	while (!bfs.empty())
	{
		state now = bfs.front();
		bfs.pop();

		int z;
		for (z = 0; z < 9; z++)
		{
			if (now.eight[z] == 9)
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
				state next = now;
				swap(next.eight[z], next.eight[newz]);
				next.move = dir[i];

				next.hash = Cantor(next.eight);
				if (!next.hash)
				{
					came_from[next.hash] = now;
					return next;
				}
				if (!came_from[next.hash].hash)
				{
					came_from[next.hash] = now;
					bfs.push(next);
				}
			}
		}
	}

	state error;
	error.hash = -1;
	return error;
}

void reconstruct(state begin, state end)
{
	char path[MAXL];
	int current = end.hash;
	path[0] = end.move;
	int start = begin.hash;

	int i;
	for (i = 1; i < MAXL && current != start; i++)
	{
		path[i] = came_from[current].move;
		current = came_from[current].hash;
	}

	i--;
	while (i)
	{
		putchar(path[--i]);
	}
	putchar('\n');
}

int main()
{
	state begin, end;
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

		begin.hash = Cantor(begin.eight);
		came_from[begin.hash] = state();
		begin.move = 0;
		end = solve(begin);
		if (end.hash >= 0)
		{
			reconstruct(begin, end);
		}
		else
		{
			printf("unsolvable\n");
		}
	}

	return 0;
}
