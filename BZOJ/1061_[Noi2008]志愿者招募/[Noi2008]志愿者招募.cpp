#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>

using namespace std;

const int NMAX = 1100, EMAX = 40000, INF = ~0u>>2;

struct Edge
{
	int y;
	int cost;
	int flow;
	int anti;
	int next;
};

int N, M;
int s, t, V[NMAX], eid;
int dis[NMAX];
Edge E[EMAX];
deque<int> Q;
bool in[NMAX];

void insert(int x, int y, int cost, int flow)
{
	E[++eid] = (Edge){y, cost, flow, 0, V[x]};
	V[x] = eid;
	E[++eid] = (Edge){x, -cost, 0, 0, V[y]};
	V[y] = eid;
	E[V[x]].anti = V[y];
	E[V[y]].anti = V[x];
}

bool SPFA()
{
	int x, i;
	for(i = 0;i <= t;i += 1)
		dis[i] = INF;
	in[s] = true;
	Q.push_back(s);
	dis[s] = 0;
	while(!Q.empty())
	{
		x = Q.front();
		Q.pop_front();
		in[x] = false;
		for(i = V[x];i;i = E[i].next)
		{
			if(E[i].flow && dis[E[i].y] > dis[x] + E[i].cost)
			{
				dis[E[i].y] = dis[x] + E[i].cost;
				if(!in[E[i].y])
				{
					in[E[i].y] = true;
					Q.push_back(E[i].y);
				}
			}
		}
	}
	return dis[t] != INF;
}

void expand(int x, int flow)
{
	E[x].flow -= flow;
	E[E[x].anti].flow += flow;
}

int dfs(int x, int flow)
{
	int i, use = 0, tmp;
	if(x == t)
		return flow;
	for(i = V[x];i && use < flow;i = E[i].next)
	{
		if(!in[E[i].y] && E[i].flow && dis[E[i].y] == E[i].cost + dis[x])
		{
			in[E[i].y] = true;
			tmp = dfs(E[i].y, min(flow - use, E[i].flow));
			use += tmp;
			expand(i, tmp);
			in[E[i].y] = false;
		}
	}
	if(!use)
		dis[x] = INF;
	return use;
}

int minCostFlow()
{
	int cost = 0, tmp;
	while(SPFA())
	{
		tmp = dfs(s, INF);
		cost += tmp * dis[t];
	}
	return cost;
}

int need[NMAX];

int main()
{
	int i, x, y, cost;
	scanf("%d %d", &N, &M);
	s = 0;
	t = N + 2;
	for(i = 1;i <= N;i += 1)
		scanf("%d", &need[i]);
	for(i = N + 1;i;i -= 1)
		need[i] -= need[i - 1];
	for(i = 1;i <= N + 1;i += 1)
	{
		if(need[i] > 0)
			insert(i, t, 0, need[i]);
		if(need[i] < 0)
			insert(s, i, 0, -need[i]);
	}
	for(i = 1;i <= M;i += 1)
	{
		scanf("%d %d %d", &x, &y, &cost);
		insert(y + 1, x, cost, INF);
	}
	for(i = 1;i <= N;i += 1)
		insert(i, i + 1, 0, INF);
	printf("%d\n", minCostFlow());
	exit(0);
}
