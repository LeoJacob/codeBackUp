#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

int N;
vector<int> number;

int main()
{
	int i, x;
	scanf("%d", &N);
	for(i = 0;i < N;i += 1)
	{
		scanf("%d", &x);
		number.push_back(x);
	}
	sort(number.begin(), number.end());
	printf("%d\n", number[(N - 1) / 2]);
}
