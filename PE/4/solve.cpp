#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

int answer;

int convert(int x, char str[])
{
	int i;
	for(i = 0;x;i += 1)
	{
		str[i] = x % 10;
		x /= 10;
	}
	return i;
}

int main()
{
	int i, j, k, len;
	char str[10];
	for(i = 1;i <= 999;i += 1)
	{
		for(j = 1;j <= 999;j += 1)
		{
			len = convert(i * j, str);
			for(k = 0;k < (len>>1);k += 1)
			{
				if(str[k] != str[len - 1 - k])
					break;
			}
			if(k >= (len>>1))
				answer = max(answer, i * j);
		}
	}
	printf("%d\n", answer);
	system("pause");
	exit(0);
}
