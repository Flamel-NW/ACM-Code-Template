// HDU-1043 stage7
#include <cstdio>
#include <cstring>
#include <queue>
#include <cctype>
#include <cmath> 
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
	int priority;
	char move;
};

struct compare_state
{
	bool operator() (const state & a, const state & b)
	{
		return a.priority > b.priority;
	}
};

state came_from[MAXN];
int cost_so_far[MAXN]; // ��ʵ������鲻�Ǳ�Ҫ��
// ����ͨ����state��������һ��dis��Ա��ÿ��+1����
// ����ϣ������A*�㷨��һ����� 

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

int heuristic(state s)
{
	int ret = 0;
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			int sx = (s.eight[x * 3 + y] - 1) / 3;
			int sy = (s.eight[x * 3 + y] - 1) % 3;
			ret += abs(double(x - sx)) + abs(double(y - sy));
		}
	}
	
	return ret;
}

state solve(state begin)
{
	priority_queue<state, vector<state>, compare_state> A_star;
	A_star.push(begin);

	if (!begin.hash)
	{
		return begin;
	}

	while (!A_star.empty())
	{
		state now = A_star.top();
		A_star.pop();

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
				int new_cost = cost_so_far[now.hash] + 1;

				next.hash = Cantor(next.eight);
				if (!next.hash)
				{
					came_from[next.hash] = now;
					return next;
				}
				if (!cost_so_far[next.hash] 
					|| new_cost < cost_so_far[next.hash]) // 这个判断条件在这个每两点之间距离为1的图里面应该没什么用处
				{
					cost_so_far[next.hash] = new_cost;
					next.priority = new_cost + heuristic(next);
					came_from[next.hash] = now;
					A_star.push(next);
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
		memset(cost_so_far, 0, sizeof(cost_so_far));
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
		came_from[begin.hash] = state();
		cost_so_far[begin.hash] = 0;
		begin.move = 0;
		begin.priority = 0;
		end = solve(begin);
		reconstruct(begin, end);
	}

	return 0;
}
