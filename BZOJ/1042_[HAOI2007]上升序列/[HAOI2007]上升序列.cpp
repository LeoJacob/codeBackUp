#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int NMAX = 11000, INF = ~0u>>1;

int N, M, L;
int number[NMAX], f[NMAX], g[NMAX];

bool cmp(int a, int b)
{
	return a > b;
}

int main()
{
	int i, j, k, x, ans;
	scanf("%d", &N);
	for(i = 1;i <= N;i += 1)
		scanf("%d", &number[i]);
	g[0] = INF;
	number[0] = -INF;
	for(i = N;i > 0;i -= 1)
	{
		f[i] = lower_bound(g, g + L + 1, number[i], cmp) - g;
		if(g[f[i]] < number[i])
			g[f[i]] = number[i];
		L = max(L, f[i]);
	}
	scanf("%d", &M);
	for(i = 1;i <= M;i += 1)
	{
		scanf("%d", &x);
		if(L < x)
			printf("Impossible\n");
		else
		{
			for(j = x, ans = 0;j;j -= 1)
			{
				for(k = ans + 1;k <= N;k += 1)
				{
					if(f[k] >= j && number[k] > number[ans])
						break;
				}
				ans = k;
				printf("%d%c", number[ans], j == 1?'\n':' ');
			}
		}
	}
	exit(0);
}
