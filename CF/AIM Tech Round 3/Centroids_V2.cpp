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

int N;
int V[VMAX], eid;
Edge E[EMAX];
int centroid, cnt[VMAX], ance[VMAX];
int M[VMAX][2], opt[VMAX];

void insert(int x, int y)
{
	E[++eid] = (Edge){y, V[x]};
	V[x] = eid;
}

void update(int M[], int &opt, int x)
{
	if(M[0] <= cnt[x])
	{
		M[1] = M[0];
		M[0] = cnt[x];
		opt = x;
	}
	else if(M[1] < cnt[x])
		M[1] = cnt[x];
}

void DFS(int pos, int fa)
{
	int i;
	cnt[pos] = 1;
	M[pos][0] = M[pos][1] = opt[pos] = 0;
	if(fa != centroid)
		ance[pos] = ance[fa];
	else
		ance[pos] = pos;
	for(i = V[pos];i;i = E[i].next)
	{
		if(E[i].y != fa)
		{
			DFS(E[i].y, pos);
			update(M[pos], opt[pos], E[i].y);
			cnt[pos] += cnt[E[i].y];
		}
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
	DFS(1, 0);
	for(i = 1;i <= N;i += 1)
	{
		if(M[i][0] <= N / 2 && N - cnt[i] <= N / 2)
			centroid = i;
	}
	DFS(centroid, 0);
	for(i = 1;i <= N;i += 1)
	{
		if(i == centroid
		|| N - ((opt[centroid] == ance[i])?M[centroid][1]:M[centroid][0])
	   		- cnt[i] <= N / 2
		|| N - cnt[ance[i]] <= N / 2)
			printf("1");
		else
			printf("0");
		printf("%c", " \n"[i == N?1:0]);
	}
	exit(0);
}
