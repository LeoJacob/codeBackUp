#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <map>

using namespace std;

const int MMAX = 6, MOD = 1000000007;

int N;
map<int, long long> f;

long long dfs(int i, int j)
{
	int k, l, s, have[MMAX] = {};
	int tmp = i;
	map<int, long long>::iterator p = f.find(i);
	if(p != f.end())
		return p->second;
	f[i] = 0;
	for(k = 0;k <= 5;k += 1)
	{
		have[k] = tmp % 16;
		tmp >>= 4;
	}
	for(k = 1;k <= 5;k += 1)
	{
		if(have[k])
		{
			have[k] -= 1;
			have[k - 1] += 1;
			for(l = s = 0;l <= 5;l += 1)
				s |= have[l]<<(4 * l);
			s |= (k - 1)<<(4 * 6);
			have[k] += 1;
			have[k - 1] -= 1;
			if(k == j)
			{
				if(have[k] != 1)
				{
					f[i] += (have[k] - 1) * dfs(s, k - 1);
					f[i] %= MOD;
				}
			}
			else
			{
				f[i] += have[k] * dfs(s, k - 1);
				f[i] %= MOD;
			}
		}
	}
	return f[i];
}

int main()
{
	int i, have[MMAX] = {};
	int tmp;
	scanf("%d", &N);
	f[N] = 1;
	for(i = 1;i <= N;i += 1)
	{
		scanf("%d", &tmp);
		have[tmp] += 1;
	}
	for(i = tmp = 0;i <= 5;i += 1)
		tmp |= have[i]<<(4 * i);
	printf("%lld\n", dfs(tmp, -1));
	exit(0);
}
