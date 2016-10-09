#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 600;

int N;
long long square[NMAX][NMAX], s;

bool check()
{
	int i, j;
	long long tmp;
	for(j = 1, s = 0;j <= N;j += 1)
		s += square[1][j];
	for(i = 1;i <= N;i += 1)
	{
		for(j = 1, tmp = 0;j <= N;j += 1)
		{
			if(square[i][j] <= 0)
				return false;
			tmp += square[i][j];
		}
		if(tmp != s)
			return false;
	}
	for(i = 1;i <= N;i += 1)
	{
		for(j = 1, tmp = 0;j <= N;j += 1)
		{
			if(square[j][i] <= 0)
				return false;
			tmp += square[j][i];
		}
		if(tmp != s)
			return false;
	}
	for(j = 1, tmp = 0;j <= N;j += 1)
		tmp += square[j][j];
	if(tmp != s)
		return false;
	for(j = 1, tmp = 0;j <= N;j += 1)
		tmp += square[j][N + 1 - j];
	if(tmp != s)
		return false;
	return true;
}

int main()
{
	int i, j, x, y;
	scanf("%d", &N);
	for(i = 1;i <= N;i += 1)
	{
		for(j = 1;j <= N;j += 1)
		{
			scanf("%lld", &square[i][j]);
			if(!square[i][j])
			{
				x = i;
				y = j;
			}
		}
	}
	if(N == 1)
		printf("1\n");
	else
	{
		i = x == 1?2:1;
		for(j = 1;j <= N;j += 1)
			s += square[i][j];
		for(j = 1;j <= N;j += 1)
			s -= square[x][j];
		square[x][y] = s;
		if(check())
			printf("%lld\n", square[x][y]);
		else
			printf("-1\n");
	}
	exit(0);
}
