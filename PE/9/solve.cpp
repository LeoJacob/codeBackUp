#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main()
{
	int i, j, k;
	for(i = 1;i < 1000;i += 1)
	{
		for(j = i + 1;i + j < 1000;j += 1)
		{
			k = 1000 - i - j;
			if(i * i + j * j == k * k)
				printf("%d\n", i * j * k);
		}
	}
	system("pause");
	exit(0);
}
