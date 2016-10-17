#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int N, M;
bool flag;

int main()
{
	int i, j;
	char o;
	scanf("%d %d", &N, &M);
	for(i = 0;i < N;i += 1)
	{
		for(j = 0;j < M;j += 1)
		{
			scanf(" %c", &o);
			if(o == 'C' || o == 'M' || o == 'Y')
				flag = true;
		}
	}
	if(flag)
		printf("#Color\n");
	else
		printf("#Black&White\n");
	exit(0);
}
