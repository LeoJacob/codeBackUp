#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 100100;

char S[NMAX];
int state;

char change(char x)
{
	return (x - 'a' - 1 + 26) % 26 + 'a';
}

int main()
{
	int i;
	scanf("%s", S);
	for(i = 0;S[i];i += 1)
	{
		if(state < 2 && change(S[i]) < S[i])
		{
			state = 1;
			S[i] = change(S[i]);
		}
		else if(state == 1 && change(S[i]) > S[i])
			state = 2;
	}
	if(!state)
		S[i - 1] = change(S[i - 1]);
	printf("%s\n", S);
	exit(0);
}
