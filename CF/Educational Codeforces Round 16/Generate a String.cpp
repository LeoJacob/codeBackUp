#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int NMAX = 10001000;

int N;
long long x, y, f[NMAX];

int main()
{
	int i;
	scanf("%d %lld %lld", &N, &x, &y);
	f[1] = x;
	for(i = 2;i <= N;i += 1)
	{
		f[i] = f[i - 1] + x;
		if(i & 1)
			f[i] = min(f[i], f[(i + 1)>>1] + x + y);
		else
			f[i] = min(f[i], f[i>>1] + y);
	}
	printf("%lld\n", f[N]);
	exit(0);
}
