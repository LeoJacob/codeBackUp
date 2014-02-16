#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 101000;

int N, answer;
int A[NMAX], B[NMAX];

bool cmp(int x, int y)
{
	return x > y;
}

int main()
{
	int t, i, j, l, r, *x, *y;
	scanf("%d", &N);
	for(i = 1;i <= N;i += 1)
		scanf("%d", &A[i]);
	for(i = 1;i <= N;i += 1)
		scanf("%d", &B[i]);
	sort(A + 1, A + N + 1, cmp);
	sort(B + 1, B + N + 1, cmp);
	x = A;
	y = B;
	for(t = 1;t <= 2;t += 1)
	{
		answer = 0;
		for(i = l = 1, j = r = N;i <= j;i += 1)
		{
			if(x[l] > y[i])
			{
				l += 1;
				answer += 2;
			}
			else
			{
				if(x[r] > y[j])
				{
					answer += 2;
					j -= 1;
					i -= 1;
				}
				else if(x[r] == y[i])
					answer += 1;
				r -= 1;
			}
		}
		printf("%d%c", t == 2?2 * N - answer:answer, t == 2?'\n':' ');
		swap(x, y);
	}
	exit(0);
}
