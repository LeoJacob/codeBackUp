#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main()
{
	int x, y, tmp, answer = 0;
	for(x = 1, y = 2;x < 4000000;)
	{
		if(!(x % 2))
			answer += x;
		tmp = y;
		y += x;
		x = tmp;
	}
	printf("%d\n", answer);
	system("pause");
	exit(0);
}
