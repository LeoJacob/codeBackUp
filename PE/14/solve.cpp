#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int NMAX = 100001000;

int N = 1000000;
int answer = 1, value = 1;

int dfs(long long x)
{
	if(x == 1)
		return 1;
	return (x % 2?dfs(3 * x + 1):dfs(x / 2)) + 1;
}

int main()
{
	int i, tmp = 0;
	for(i = 2;i < N;i += 1)
	{
		tmp = dfs(i);
		if(tmp > value)
		{
			value = tmp;
			answer = i;
		}
	}
	printf("%d\n", answer);
	system("pause");
	exit(0);
}
