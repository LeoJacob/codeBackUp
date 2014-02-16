#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int answer = 0;
int cost19[20] = {0, 3, 3, 5, 4, 4, 3, 5, 5, 4, 3, 6, 6, 8, 8, 7, 7, 9, 8, 8};
int cost10s[11] = {0, 0, 6, 6, 5, 5, 5, 7, 6, 6};
int H = 7;

int main()
{
	int i;
	for(i = 1;i < 1000;i += 1)
	{
		answer += cost19[i / 100];
		if(i / 100)
		{
			answer += H;
			if(i % 100)
				answer += 3;
		}
		if(i % 100 <= 19)
			answer += cost19[i % 100];
		else
			answer += cost10s[i % 100 / 10] + cost19[i % 10];
	}
	printf("%d\n", answer + 11);
	system("pause");
	exit(0);
}
