#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int answer;

int weekday(int y, int m, int d)
{
	int c;
	if(m == 1 || m == 2)
	{
		m += 12;
		y -= 1;
	}
	c = y / 100;
	y = y % 100;
	return (y + y / 4 + c / 4 - 2 * c + (26 * (m + 1) / 10) + d - 1 + 70000) % 7;
}

int main()
{
	int i, j;
	for(i = 1901;i <= 2000;i += 1)
	{
		for(j = 1;j <= 12;j += 1)
		{
			if(!weekday(i, j, 1))
				answer += 1;
		}
	}
	printf("%d\n", answer);
	system("pause");
	exit(0);
}
