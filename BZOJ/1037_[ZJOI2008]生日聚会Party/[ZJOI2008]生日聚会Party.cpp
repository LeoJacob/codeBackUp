#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int NMAX = 160, MMAX = 160, KMAX = 23, LMAX = 23, MOD = 12345678;

int N, M, P, answer;
int f[NMAX][MMAX][KMAX][LMAX];

int main()
{
	int i, j, k, l;
	scanf("%d %d %d", &N, &M, &P);
	f[0][0][0][0] = 1;
	for(i = 0;i <= N;i += 1)
	{
		for(j = 0;j <= M;j += 1)
		{
			for(k = 0;k <= min(i, P);k += 1)
			{
				for(l = 0;l <= min(j, P);l += 1)
				{
					if(k + 1 <= P)
					{
						f[i + 1][j][k + 1][max(0, l - 1)] += f[i][j][k][l];
						f[i + 1][j][k + 1][max(0, l - 1)] %= MOD;
					}
					if(l + 1 <= P)
					{
						f[i][j + 1][max(0, k - 1)][l + 1] += f[i][j][k][l];
						f[i][j + 1][max(0, k - 1)][l + 1] %= MOD;
					}
				}
			}
		}
	}
	for(i = 0;i <= P;i += 1)
	{
		for(j = 0;j <= P;j += 1)
		{
			answer += f[N][M][i][j];
			answer %= MOD;
		}
	}
	printf("%d\n", answer);
	exit(0);
}
