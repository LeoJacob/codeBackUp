#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int N, B, D, ans;
int waste;

int main()
{
	int i, x;
	scanf("%d %d %d", &N, &B, &D);
	for(i = 1;i <= N;i += 1)
	{
		scanf("%d", &x);
		if(x > B)
			continue;
		waste += x;
		if(waste > D)
		{
			ans += 1;
			waste = 0;
		}
	}
	printf("%d\n", ans);
	exit(0);
}
