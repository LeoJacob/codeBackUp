#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

long long answer = 1;

long long gcd(long long x, long long y)
{
	if(!y)
		return x;
	return gcd(y, x % y);
}

int main()
{
	int i;
	for(i = 1;i <= 20;i += 1)
		answer = i * answer / gcd(answer, i);
	printf("%I64d\n", answer);
	system("pause");
	exit(0);
}
