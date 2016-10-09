#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int NMAX = 1100, MMAX = 10;

int N, M = 5, flag;
char table[NMAX][MMAX];

int main()
{
	int i;
	scanf("%d", &N);
	for(i = 1;i <= N;i += 1)
	{
		scanf("%s", table[i]);
		if(flag)
			continue;
		if(table[i][0] == 'O' && table[i][1] == 'O')
		{
			flag = true;
			table[i][0] = table[i][1] = '+';
		}
		if(flag)
			continue;
		if(table[i][3] == 'O' && table[i][4] == 'O')
		{
			flag = true;
			table[i][3] = table[i][4] = '+';
		}
	}
	printf("%s\n", flag?"YES":"NO");
	if(flag)
	{
		for(i = 1;i <= N;i += 1)
			printf("%s\n", table[i]);
	}
	exit(0);
}
