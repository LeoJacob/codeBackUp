#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int NMAX = 22, MMAX = 20, VMAX = 1000, EMAX = 100000, INF = ~0u>>1;

int N, M, K;

struct Edge
{
	int y;
	int flow;
	int anti;
	int next;
};

int s, t, V[VMAX], eid, cnt;
Edge E[EMAX];
deque<int> Q;
int level[VMAX], pillar[NMAX][MMAX];

void insert(int x, int y, int flow)
{
	E[++eid] = (Edge){y, flow, 0, V[x]};
	V[x] = eid;
	E[++eid] = (Edge){x, 0, 0, V[y]};
	V[y] = eid;
	E[V[x]].anti = V[y];
	E[V[y]].anti = V[x];
}

bool makeLevel()
{
	int i, x;
	memset(level, 0, sizeof(level));
	level[s] = 1;
	Q.push_back(s);
	while(!Q.empty())
	{
		x = Q.front();
		Q.pop_front();
		for(i = V[x];i;i = E[i].next)
		{
			if(E[i].flow && !level[E[i].y])
			{
				level[E[i].y] = level[x] + 1;
				Q.push_back(E[i].y);
			}
		}
	}
	return level[t];
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
		if(level[x] + 1 == level[E[i].y] && E[i].flow)
		{
			tmp = dfs(E[i].y, min(flow - use, E[i].flow));
			if(tmp)
				expand(i, tmp);
			use += tmp;
		}
	}
	if(!use)
		level[x] = -1;
	return use;
}

int dinic()
{
	int flow = 0;
	while(makeLevel())
		flow += dfs(s, INF);
	return flow;
}

int main()
{
	int i, j, k, l;
	char tmp;
	bool flag;
	scanf("%d %d %d", &N, &M, &K);
	s = 2 * N * M + 1;
	t = s + 1;
	for(i = 1;i <= N;i += 1)
	{
		for(j = 1;j <= M;j += 1)
		{
			scanf("%1d", &pillar[i][j]);
			if(pillar[i][j])
				insert((i - 1) * M + j, N * M + (i - 1) * M + j, pillar[i][j]);
		}
	}
	for(i = 1;i <= N;i += 1)
	{
		for(j = 1;j <= M;j += 1)
		{
			scanf(" %c", &tmp);
			if(tmp == 'L')
			{
				insert(s, (i - 1) * M + j, 1);
				cnt += 1;
			}
		}
	}
	for(i = 1;i <= N;i += 1)
	{
		for(j = 1;j <= M;j += 1)
		{
			if(!pillar[i][j])
				continue;
			flag = false;
			for(k = -K;k <= K;k += 1)
			{
				for(l = -K;l <= K;l += 1)
				{
					if((!k && !l) || abs(k) + abs(l) > K)
						continue;
					if(i + k <= 0 || i + k > N || j + l <= 0 || j + l > M)
					{
						if(!flag)
						{
							flag = true;
							insert(N * M + (i - 1) * M + j, t, INF);
						}
					}
					else if(pillar[i + k][j + l])
						insert(N * M + (i - 1) * M + j, (i + k - 1) * M + j + l, INF);
				}
			}
		}
	}
	printf("%d\n", cnt - dinic());
	exit(0);
}
