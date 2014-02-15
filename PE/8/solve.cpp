#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int digit[1100], answer;

int main()
{
	int i, j, tmp;
	for(i = 1;i <= 1000;i += 1)
	{
		scanf("%1d", &digit[i]);
		if(i >= 5)
		{
			for(j = 0, tmp = 1;j < 5;j += 1)
				tmp *= digit[i - j];
			answer = max(answer, tmp);
		}
	}
	printf("%d\n", answer);
	system("pause");
	exit(0);
}
