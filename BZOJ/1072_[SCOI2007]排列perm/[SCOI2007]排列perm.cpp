#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 11, SMAX = 1100, MMAX = 1100;

int T, N, M;
char str[NMAX];
int f[SMAX][MMAX], order[SMAX];

int lowbit(int x)
{
	return x & (-x);
}

int digit(int x)
{
	int ans = 0;
	while(x)
	{
		ans += 1;
		x -= lowbit(x);
	}
	return ans;
}

bool cmp(int x, int y)
{
	int d1 = digit(x), d2 = digit(y);
	if(d1 == d2)
		return x < y;
	return d1 < d2;
}

int main()
{
	int t, bound, i, j, k;
	scanf("%d", &T);
	for(t = 1;t <= T;t += 1)
	{
		memset(f, 0, sizeof(f));
		f[0][0] = 1;
		scanf("%s %d", str + 1, &M);
		N = strlen(str + 1);
		for(i = 1;i <= N;i += 1)
			str[i] -= '0';
		sort(str + 1, str + N + 1);
		bound = (1<<N) - 1;
		for(i = 0;i <= bound;i += 1)
			order[i] = i;
		sort(order, order + bound + 1, cmp);
		for(i = 0;i < bound;i += 1)
		{
			for(j = 1;j <= N;j += 1)
			{
				if(!(order[i] & (1<<(j - 1))) && (j == 1 || str[j] != str[j - 1] || (order[i] & (1<<(j - 2)))))
				{
					for(k = 0;k < M;k += 1)
						f[order[i] | (1<<(j - 1))][(k * 10 + str[j]) % M] += f[order[i]][k];
				}
			}
		}
		printf("%d\n", f[bound][0]);
	}
	exit(0);
}
