#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int NMAX = 51000, MMAX = 1100, MOD = 10007;

int N, M, answer;
int limit, stick[NMAX], sum[NMAX], f[NMAX][2];
int Q[NMAX], head, tail;

bool check(int x)
{
	int i, use, tmp;
	for(i = 1, use = tmp = 0;i <= N;i += 1)
	{
		if(tmp + stick[i] > x)
		{
			use += 1;
			tmp = stick[i];
		}
		else
			tmp += stick[i];
		if(tmp > x)
			return false;
	}
	return use <= M;
}

int main()
{
	int i, j, l, r, mid, tmp;
	scanf("%d %d", &N, &M);
	for(i = 1;i <= N;i += 1)
	{
		scanf("%d", &stick[i]);
		sum[i] = stick[i];
		sum[i] += sum[i - 1];
	}
	for(l = 0, r = 50000000;l + 1 < r;)//(]
	{
		mid = (l + r)>>1;
		if(check(mid))
			r = mid;
		else
			l = mid;
	}
	limit = r;
	f[0][0] = 1;
	for(i = 1, tmp = 0;i <= N;i += 1)
	{
		tmp += stick[i];
		if(tmp <= limit)
			f[i][0] = 1;
		else
			break;
	}
	answer = f[N][0];
	for(j = 1;j <= M;j += 1)
	{
		head = tail = 0;
		tmp = 0;
		for(i = 1;i <= N;i += 1)
		{
			while(head < tail && sum[i] - sum[Q[head]] > limit)
			{
				tmp = (tmp - f[Q[head]][(j - 1) & 1] + MOD) % MOD;
				head += 1;
			}
			f[i][j & 1] = tmp;
			Q[tail++] = i;
			tmp = (tmp + f[i][(j - 1) & 1]) % MOD;
		}
		answer = (answer + f[N][j % 2]) % MOD;
	}
	printf("%d %d\n", limit, answer);
	exit(0);
}
