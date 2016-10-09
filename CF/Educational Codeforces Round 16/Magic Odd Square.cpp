#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

const int NMAX = 55;

int N;
int square[NMAX][NMAX];
deque<int> odd, even;

int main()
{
	int i, j, k;
	scanf("%d", &N);
	for(i = 1;i <= N * N;i += 1)
	{
		if(i & 1)
			odd.push_back(i);
		else
			even.push_back(i);
	}
	for(i = 1;i <= N;i += 1)
	{
		square[(N + 1)>>1][i] = odd[0];
		odd.pop_front();
	}
	for(i = 1;i <= N;i += 1)
	{
		if(square[i][(N + 1)>>1])
			continue;
		square[i][(N + 1)>>1] = odd[0];
		odd.pop_front();
	}
	for(i = 1;i <= N;i += 1)
	{
		for(j = 1;j <= N;j += 1)
		{
			if(square[i][j])
				continue;
			if(even.size())
			{
				square[i][j] = even[0];
				square[N + 1 - i][j] = even[1];
				square[i][N + 1 - j] = even[2];
				square[N + 1 - i][N + 1 - j] = even[3];
				for(k = 0;k < 4;k += 1)
					even.pop_front();
			}
			else
			{
				square[i][j] = odd[0];
				square[N + 1 - i][j] = odd[1];
				square[i][N + 1 - j] = odd[2];
				square[N + 1 - i][N + 1 - j] = odd[3];
				for(k = 0;k < 4;k += 1)
					odd.pop_front();
			}
		}
	}
	for(i = 1;i <= N;i += 1)
	{
		for(j = 1;j <= N;j += 1)
			printf("%d%c", square[i][j], " \n"[j == N?1:0]);
	}
	exit(0);
}
