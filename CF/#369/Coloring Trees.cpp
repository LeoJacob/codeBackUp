#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 110, MMAX = 110, KMAX = 110;
const long long INF = 214748364700LL;

int N, M, K;
int cost[NMAX][MMAX], color[NMAX], best[NMAX][KMAX];
long long f[NMAX][MMAX][KMAX], g[NMAX][KMAX][2];

int main()
{
	int i, j, k;
	memset(f, -1, sizeof(f));
	memset(g, -1, sizeof(g));
	scanf("%d %d %d", &N, &M, &K);
	for(i = 1;i <= N;i += 1)
		scanf("%d", &color[i]);
	for(i = 1;i <= N;i += 1)
	{
		for(j = 1;j <= M;j += 1)
			scanf("%d", &cost[i][j]);
	}
	f[0][0][0] = g[0][0][0] = 0;
	for(i = 1;i <= N;i += 1)
	{
		for(j = 1;j <= M;j += 1)
		{
			if(color[i] && j != color[i])
				continue;
			for(k = 1;k <= K;k += 1)
			{
				if(f[i - 1][j][k] >= 0)
					f[i][j][k] = f[i - 1][j][k];
				if(g[i - 1][k - 1][0] >= 0)
				{
					if(best[i - 1][k - 1] != j)
					{
						if(f[i][j][k] < 0 || g[i - 1][k - 1][0] < f[i][j][k])
							f[i][j][k] = g[i - 1][k - 1][0];
					}
					else if(g[i - 1][k - 1][1] >= 0)
					{
						if(f[i][j][k] < 0 || g[i - 1][k - 1][1] < f[i][j][k])
							f[i][j][k] = g[i - 1][k - 1][1];
					}
				}
				if(f[i][j][k] < 0)
					continue;
				if(color[i] != j)
					f[i][j][k] += cost[i][j];
				if(g[i][k][0] < 0 || f[i][j][k] < g[i][k][0])
				{
					g[i][k][1] = g[i][k][0];
					g[i][k][0] = f[i][j][k];
					best[i][k] = j;
				}
				else if(g[i][k][1] < 0 || f[i][j][k] < g[i][k][1])
					g[i][k][1] = f[i][j][k];
			}
		}
	}
	printf("%lld\n", g[N][K][0]);
	exit(0);
}
