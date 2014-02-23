#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int PMAX = 11;
const long long INF = ~0u>>1;

long long N, answer = INF, factorCnt;
int prime[PMAX] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
int power[PMAX] = {};

void dfs(int i, long long x)
{
	int j, tmp;
	for(j = tmp = 1;j < i;j += 1)
		tmp *= power[j] + 1;
	if(tmp > factorCnt)
	{
		factorCnt = tmp;
		answer = x;
	}
	else if(tmp == factorCnt)
		answer = min(answer, x);
	if(i > PMAX)
		return;
	for(j = 1;j <= power[i - 1];j += 1)
	{
		x *= prime[i];
		if(x > N)
			break;
		power[i] = j;
		dfs(i + 1, x);
	}
}

int main()
{
	power[0] = 100;
	scanf("%lld", &N);
	dfs(1, 1);
	printf("%lld\n", answer);
	exit(0);
}
