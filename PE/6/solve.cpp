#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int answer;

int main()
{
	int i;
	for(i = 1;i <= 100;i += 1)
		answer += i * i;
	printf("%d\n", 5050 * 5050 - answer);
	system("pause");
	exit(0);
}
