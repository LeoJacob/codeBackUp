#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

int dir[8][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
int ans;

int main()
{
	int i, x, y, xx, yy;
	char c, d;
	scanf(" %c%c", &c, &d);
	x = c - 'a' + 1;
	y = d - '0';
	for(i = 0;i < 8;i += 1)
	{
		xx = x + dir[i][0];
		yy = y + dir[i][1];
		if(xx >= 1 && xx <= 8 && yy >= 1 && yy <= 8)
			ans += 1;
	}
	printf("%d\n", ans);
	exit(0);
}
