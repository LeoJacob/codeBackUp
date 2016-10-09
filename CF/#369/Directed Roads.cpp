#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 210000, MOD = 1000000007;

int N, parent[NMAX], ans = 1;
int father[NMAX], DFN[NMAX], stamp = 1;
bool visit[NMAX];

int find(int x)
{
	int p, tmp;
	for(p = x;father[p] >= 0;p = father[p]);
	for(;x != p;)
	{
		tmp = father[x];
		father[x] = p;
		x = tmp;
	}
	return p;
}

void Union(int x, int y)
{
	int X = find(x), Y = find(y);
	if(X == Y)
		return;
	if(father[X] > father[Y])
		swap(X, Y);
	father[X] += father[Y];
	father[Y] = X;
}

int quickPow(int x, int y)
{
	int res = 1;
	while(y)
	{
		if(y & 1)
			res = (long long)res * x % MOD;
		x = (long long)x * x % MOD;
		y >>= 1;
	}
	return res;
}

int main()
{
	int i, x, cycle;
	memset(father, -1, sizeof(father));
	scanf("%d", &N);
	for(i = 1;i <= N;i += 1)
	{
		scanf("%d", &parent[i]);
		Union(i, parent[i]);
	}
	for(i = 1;i <= N;i += 1)
	{
		x = find(i);
		if(visit[x])
			continue;
		visit[x] = true;
		for(x = i;;x = parent[x])
		{
			if(DFN[x])
			{
				cycle = stamp - DFN[x];
				ans = ans * ((long long)(quickPow(2, cycle) - 2 + MOD) * quickPow(2, -father[find(x)] - cycle) % MOD) % MOD;
				break;
			}
			DFN[x] = stamp++;
		}
	}
	printf("%d\n", ans);
	exit(0);
}
