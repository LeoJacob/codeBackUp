#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int NMAX = 17;

int answer;
int f[NMAX][NMAX];

int main()
{
	int i, j;
	for(i = 1;i <= 15;i += 1)
	{
		for(j = 1;j <= i;j += 1)
		{
			scanf("%d", &f[i][j]);
			f[i][j] += max(f[i - 1][j], f[i - 1][j - 1]);
			answer = max(answer, f[i][j]);
		}
	}
	printf("%d\n", answer);
	system("pause");
	exit(0);
}
