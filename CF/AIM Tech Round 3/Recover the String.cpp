#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const int LMAX = 1000100;

int px[3] = {0, 1}, py[3] = {0, 1};
int a[2][2];
bool flag;

int n(int x)
{
	return x * (x - 1) / 2;
}

int check(int x, int y)
{
	return n(x) == a[0][0] && n(y) == a[1][1]
		&& a[1][0] + a[0][1] == x * y && x + y;
}

void output(int x, int y)
{
	int i, last = (y?a[1][0] / y:0), pos;
	char s[LMAX] = {};
	for(i = pos = 0;i < x - last;i += 1, pos += 1)
		s[pos] = '0';
	for(i = 0;i < y;i += 1, pos += 1)
		s[pos] = '1';
	for(i = 0;i < last;i += 1, pos += 1)
		s[pos] = '0';
	for(i = x - last, (y?a[1][0] %= y:a[1][0] = 0);a[1][0];i += 1, a[1][0] -= 1)
		swap(s[i], s[i - 1]);
	printf("%s\n", s);
}

int main()
{
	int i, j;
	for(i = 0;i < 2;i += 1)
	{
		for(j = 0;j < 2;j += 1)
			scanf("%d", &a[i][j]);
	}
	px[2] = (int)sqrt(2 * a[0][0]) + 1;
	py[2] = (int)sqrt(2 * a[1][1]) + 1;
	for(i = 0;i < 3;i += 1)
	{
		for(j = 0;j < 3;j += 1)
		{
			if(!flag && check(px[i], py[j]))
			{
				output(px[i], py[j]);
				flag = true;
			}
		}
	}
	if(!flag)
		printf("Impossible\n");
	exit(0);
}
