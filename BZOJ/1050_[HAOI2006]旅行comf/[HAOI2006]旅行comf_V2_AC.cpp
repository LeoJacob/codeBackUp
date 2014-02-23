#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int NMAX = 600, EMAX = 5100, MMAX = 300000;

struct Edge
{
	int x;
	int y;
	int cost;
};

struct Frac
{
	int x;
	int y;
};

int N, M;
int s, t, father[NMAX];
Edge E[EMAX];
Frac answer = (Frac){MMAX, 1};

int find(int x)
{
	int i, parent, tmp;
	for(i = x;father[i] >= 0;i = father[i]);
	parent = i;
	for(i = x;i != parent;)
	{
		tmp = father[i];
		father[i] = parent;
		i = tmp;
	}
	return parent;
}

void Union(int x, int y)
{
	int X = find(x), Y = find(y);
	if(X == Y)
		return;
	if(father[X] < father[Y])
	{
		father[X] += father[Y];
		father[Y] = X;
	}
	else
	{
		father[Y] += father[X];
		father[X] = Y;
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

bool cmp(Edge x, Edge y)
{
	return x.cost < y.cost;
}

int main()
{
	int i, j;
	scanf("%d %d", &N, &M);
	for(i = 1;i <= M;i += 1)
		scanf("%d %d %d", &E[i].x, &E[i].y, &E[i].cost);
	scanf("%d %d", &s, &t);
	sort(E + 1, E + M + 1, cmp);
	for(i = 1;i <= M;i += 1)
	{
		memset(father, ~0u, sizeof(father));
		for(j = i;j <= M;j += 1)
		{
			Union(E[j].x, E[j].y);
			if(find(s) == find(t))
			{
				better(E[j].cost / gcd(E[i].cost, E[j].cost), E[i].cost / gcd(E[i].cost, E[j].cost));
				break;
			}
		}
		if(find(s) != find(t))
			break;
	}
	if(answer.x == MMAX && answer.y == 1)
		printf("IMPOSSIBLE\n");
	else if(answer.y == 1)
		printf("%d\n", answer.x);
	else
		printf("%d/%d\n", answer.x, answer.y);
	exit(0);
}
