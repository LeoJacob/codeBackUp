#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

long long answer;

int main()
{
	int i;
	long long tmp;
	for(i = 1;i <= 100;i += 1)
	{
		scanf("%14I64d%*s", &tmp);
		answer += tmp;
	}
	while(answer >= 10000000000ll)
		answer /= 10;
	printf("%I64d\n", answer);
	system("pause");
	exit(0);
}
