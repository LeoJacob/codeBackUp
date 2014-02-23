#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int NMAX = 101, KMAX = 11, MMAX = 3, SMAX = 5, INF = ~0u>>3;

int N, M, K, answer;
int number[NMAX][MMAX], sum[NMAX];
int f[NMAX][KMAX][SMAX];

int main()
{
	int i, j, k, l, tmp;
	int cost[5][5] = {{0, 1, 1, 2, 1}, {0, 0, 1, 1, 1}, {0, 1, 0, 1, 1}, {0, 0, 0, 0, 1}, {0, 1, 1, 2, 0}};
	scanf("%d %d %d", &N, &M, &K);
	for(i = 1;i <= N;i += 1)
	{
		for(j = 1;j <= M;j += 1)
		{
			scanf("%d", &number[i][j]);
			sum[i] += number[i][j];
		}
	}
	for(i = 0;i <= N;i += 1)
	{
		for(j = 0;j <= K;j += 1)
		{
			for(k = 0;k < SMAX;k += 1)
				f[i][j][k] = -INF;
		}
	}
	f[0][0][0] = 0;
	for(i = 1;i <= N;i += 1)
	{
		for(j = 0;j <= K;j += 1)
		{
			for(k = 0;k < SMAX;k += 1)
			{
				tmp = 0;
				if(k & 1 || k == 4)
					tmp += number[i][1];
				if(k & 2 || k == 4)
					tmp += number[i][2];
				for(l = 0;l < SMAX;l += 1)
				{
					if(j >= cost[k][l])
						f[i][j][k] = max(f[i][j][k], f[i - 1][j - cost[k][l]][l] + tmp);
				}
			}
		}
	}
	for(i = 1;i <= K;i += 1)
	{
		for(j = 0;j < SMAX;j += 1)
		{
			if(i >= cost[0][j])
				answer = max(answer, f[N][i - cost[0][j]][j]);
		}
	}
	printf("%d\n", answer);
	exit(0);
}
