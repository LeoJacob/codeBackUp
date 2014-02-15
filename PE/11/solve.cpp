#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int number[30][30], answer;

int main()
{
	int i, j, k, l, tmp;
	int way[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
	for(i = 1;i <= 20;i += 1)
	{
		for(j = 1;j <= 20;j += 1)
			scanf("%d", &number[i][j]);
	}
	for(i = 1;i <= 20;i += 1)
	{
		for(j = 1;j <= 20;j += 1)
		{
			for(k = 0;k < 4;k += 1)
			{
				for(l = 0, tmp = 1;l < 4 && i + l * way[k][0] > 0 && j + l * way[k][1] > 0;l += 1)
					tmp *= number[i + l * way[k][0]][j + l * way[k][1]];
				if(l >= 4)
					answer = max(answer, tmp);
			}
		}
	}
	printf("%d\n", answer);
	system("pause");
	exit(0);
}
