#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <set>

using namespace std;

int answer;
long long R, D;
set<long long> hash;

long long gcd(long long x, long long y)
{
	if(!y)
		return x;
	return gcd(y, x % y);
}

int solve(long long x)
{
	int ans = 0;
	long long i, j, tmp;
	for(i = 1;(tmp = i * i) <= x;i += 1)
	{
		j = (int)(sqrt(x - tmp) + 0.5);
		if(i >= j)
			break;
		if(j * j + tmp == x && gcd(i, j) == 1)
			ans += hash.insert(2 * R / x * i * j).second;
	}
	return ans;
}

int main()
{
	long long i;
	scanf("%I64d", &R);
	D = R<<1;
	for(i = 1;i * i <= D;i += 1)
	{
		if(D % i)
			continue;
		answer += solve(i);
		if(i * i == D)
			break;
		answer += solve(D / i);
	}
	printf("%d\n", 4 * answer + 4);
	exit(0);
}
