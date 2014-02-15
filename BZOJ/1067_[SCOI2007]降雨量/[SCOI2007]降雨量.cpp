#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 51000, LMAX = 17, INF = ~0u>>1;

int N, M;
int year[NMAX], rain[NMAX];
int ST[NMAX][LMAX];

void buildST()
{
	int i, j;
	for(i = 1;i <= N;i += 1)
		ST[i][0] = rain[i];
	for(j = 1;(1<<j) <= N;j += 1)
	{
		for(i = 1;i + (1<<j) - 1 <= N;i += 1)
			ST[i][j] = max(ST[i][j - 1], ST[i + (1<<(j - 1))][j - 1]);
	}
}

int query(int l, int r)
{
	int i;
	for(i = 0;(1<<(i + 1)) <= (r - l + 1);i += 1);
	return max(ST[l][i], ST[r - (1<<i) + 1][i]);
}

int main()
{
	int i, l, r, x, y;
	scanf("%d", &N);
	year[N + 1] = INF;
	for(i = 1;i <= N;i += 1)
		scanf("%d %d", &year[i], &rain[i]);
	buildST();
	scanf("%d", &M);
	for(i = 1;i <= M;i += 1)
	{
		scanf("%d %d", &l, &r);
		x = lower_bound(year + 1, year + N + 1, l) - year;
		y = lower_bound(year + 1, year + N + 1, r) - year;
		if(year[x] > r)
			printf("maybe\n");
		else if(year[x] > l)
		{
			if(year[y] > r)
				printf("maybe\n");
			else
			{
				if(x > y - 1 || query(x, y - 1) < rain[y])
					printf("maybe\n");
				else
					printf("false\n");
			}
		}
		else
		{
			if(year[y] > r)
			{
				if(x + 1 > y - 1 || query(x + 1, y - 1) < rain[x])
					printf("maybe\n");
				else
					printf("false\n");
			}
			else
			{
				if(rain[x] < rain[y])
					printf("false\n");
				else if(x + 1 > y - 1 && y - x != year[y] - year[x])
					printf("maybe\n");
				else if(x + 1 <= y - 1 && query(x + 1, y - 1) >= rain[y])
					printf("false\n");
				else if(y - x == year[y] - year[x])
					printf("true\n");
				else
					printf("maybe\n");
			}
		}
	}
	exit(0);
}
