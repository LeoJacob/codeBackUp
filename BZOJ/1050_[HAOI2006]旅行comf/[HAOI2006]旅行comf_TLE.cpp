#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>

using namespace std;

const int VMAX = 600, EMAX = 11000, MMAX = 30000;

struct Edge
{
	int y;
	int cost;
	int next;
};

struct Frac
{
	int x;
	int y;
};

int N, M;
int V[VMAX], eid, s, t;
Edge E[EMAX];
int f[VMAX][MMAX];
bool in[VMAX][MMAX];
deque<pair<int, int> > Q;
Frac answer = (Frac){MMAX, 1};

void insert(int x, int y, int cost)
{
	E[++eid] = (Edge){y, cost, V[x]};
	V[x] = eid;
}

void SPFA()
{
	int i, x, v;
	for(i = V[s];i;i = E[i].next)
	{
		f[E[i].y][E[i].cost] = E[i].cost;
		Q.push_back(make_pair(E[i].y, E[i].cost));
	}
	while(!Q.empty())
	{
		x = Q.front().first;
		v = Q.front().second;
		Q.pop_front();
		in[x][v] = false;
		if(x == t)
			continue;
		for(i = V[x];i;i = E[i].next)
		{
			if(E[i].y == s)
				continue;
			if(!f[E[i].y][min(E[i].cost, v)] || f[E[i].y][min(E[i].cost, v)] > max(E[i].cost, f[x][v]))
			{
				f[E[i].y][min(E[i].cost, v)] = max(E[i].cost, f[x][v]);
				if(!in[E[i].y][min(E[i].cost, v)])
				{
					in[E[i].y][min(E[i].cost, v)] = true;
					Q.push_back(make_pair(E[i].y, min(E[i].cost, v)));
				}
			}
		}
	}
}

int gcd(int x, int y)
{
	if(!y)
		return x;
	return gcd(y, x % y);
}

void better(int x, int y)
{
	if(answer.x * y > x * answer.y)
		answer = (Frac){x, y};
}

int main()
{
	int i, x, y, cost;
	scanf("%d %d", &N, &M);
	for(i = 1;i <= M;i += 1)
	{
		scanf("%d %d %d", &x, &y, &cost);
		insert(x, y, cost);
		insert(y, x, cost);
	}
	scanf("%d %d", &s, &t);
	SPFA();
	for(i = 1;i < MMAX;i += 1)
	{
		if(f[t][i])
			better(f[t][i] / gcd(f[t][i], i), i / gcd(f[t][i], i));
	}
	if(answer.x == MMAX && answer.y == 1)
		printf("IMPOSSIBLE\n");
	else if(answer.y == 1)
		printf("%d\n", answer.x);
	else
		printf("%d/%d\n", answer.x, answer.y);
	exit(0);
}
