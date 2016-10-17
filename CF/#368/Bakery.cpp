#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int NMAX = 110000, VMAX = 110000, EMAX = 210000;
const int INF = ~0u>>1;

struct Edge
{
	int y;
	int w;
	int next;
};

int N, M, K, ans = INF;
bool ban[NMAX];
int V[VMAX], eid;
Edge E[EMAX];

void insert(int x, int y, int w)
{
	E[++eid] = (Edge){y, w, V[x]};
	V[x] = eid;
}

int main()
{
	int i, j, x, y, w;
	scanf("%d %d %d", &N, &M, &K);
	for(i = 1;i <= M;i += 1)
	{
		scanf("%d %d %d", &x, &y, &w);
		insert(x, y, w);
		insert(y, x, w);
	}
	for(i = 1;i <= K;i += 1)
	{
		scanf("%d", &x);
		ban[x] = true;
	}
	for(i = 1;i <= N;i += 1)
	{
		if(ban[i])
			continue;
		for(j = V[i];j;j = E[j].next)
		{
			if(ban[E[j].y])
				ans = min(ans, E[j].w);
		}
	}
	printf("%d\n", ans == INF?-1:ans);
	exit(0);
}
