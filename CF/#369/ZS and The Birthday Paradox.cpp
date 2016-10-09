#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

/*
 *
 * 2^(nk) - 2^n * (2^n - 1) * ... * (2^n - k + 1)
 * ---------------------------------------------------
 *                      2^(nk)
 *
 * ***************************************************
 * because MOD divide the product of MOD consecutive numbers exactly, so if k >= 10^6 + 3, then A % MOD = 0
 * 
 */

const int MOD = 1000003;

long long N, K, common;
int A, B;

int quickModPow(int x, int y)
{
	int res = 1;
	while(y)
	{
		if(y & 1)
			res = (long long)res * x % MOD;
		x = (long long)x * x % MOD;
		y >>= 1;
	}
	return res;
}

int main()
{
	int i, rev, tpow;
	long long x;
	scanf("%lld %lld", &N, &K);
	if(N <= 63 && (1ll<<N) < K)
		printf("1 1\n");
	else
	{
		for(x = 2;x < K;x <<= 1)
			common += (K - 1) / x;
		tpow = quickModPow(2, N % (MOD - 1));
		if(K >= MOD)
			A = 0;
		else
		{
			for(A = 1, i = 1;i < K;i += 1)
				A = ((long long)A * (tpow - i) % MOD + MOD) % MOD;
		}
		B = quickModPow(2, (N % (MOD - 1)) * ((K - 1) % (MOD - 1)) % (MOD - 1));
		rev = quickModPow(2, MOD - 2);
		rev = quickModPow(rev, common % (MOD - 1));
		B = (long long)B * rev % MOD;
		A = (B + MOD - (long long)A * rev % MOD) % MOD;
		printf("%d %d\n", A, B);
	}
	exit(0);
}
