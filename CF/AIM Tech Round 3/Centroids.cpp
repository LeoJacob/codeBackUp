#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int VMAX = 401000, EMAX = 801000;

struct Edge
{
	int y;
	int next;
};

int N, can[VMAX], cnt[VMAX];
int V[VMAX], eid;
Edge E[EMAX];
int centroid, GM[2], GOpt, sCnt[VMAX];
int state;

void insert(int x, int y)
{
	E[++eid] = (Edge){y, V[x]};
	V[x] = eid;
}

void update(int M[], int &opt, int x)
{
	if(M[0] <= sCnt[x])
	{
		M[1] = M[0];
		M[0] = sCnt[x];
		opt = x;
	}
	else if(M[1] < sCnt[x])
		M[1] = sCnt[x];
}

void DFS(int pos, int fa, int ance)
{
	int i, M[2] = {}, opt = 0;
	sCnt[pos] = 1;
	for(i = V[pos];i;i = E[i].next)
	{
		if(E[i].y != fa)
		{
			DFS(E[i].y, pos, (state == 2 && pos == centroid)?E[i].y:ance);
			update(M, opt, E[i].y);
			sCnt[pos] += sCnt[E[i].y];
		}
	}
	if(state == 2 && pos != centroid)
	{
		if(N - sCnt[pos] - GM[GOpt != ance?0:1] <= N / 2
		|| N - cnt[ance] <= N / 2)
			can[pos] = 1;
	}
	if(!state && max(M[0], N - sCnt[pos]) <= N / 2)
	{
		state = 1;
		centroid = pos;
		can[pos] = 1;
		sCnt[fa] = N - sCnt[pos];
		update(M, opt, fa);
		memcpy(GM, M, sizeof(GM));
		for(i = V[pos];i;i = E[i].next)
			cnt[E[i].y] = sCnt[E[i].y];
		GOpt = opt;
	}
}

int main()
{
	int i, x, y;
	scanf("%d", &N);
	for(i = 1;i < N;i += 1)
	{
		scanf("%d %d", &x, &y);
		insert(x, y);
		insert(y, x);
	}
	DFS(1, 0, 0);
	state = 2;
	DFS(centroid, 0, 0);
	for(i = 1;i <= N;i += 1)
		printf("%d%c", can[i], " \n"[i == N?1:0]);
	exit(0);
}
