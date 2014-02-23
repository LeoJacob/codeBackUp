#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 2100, MMAX = 2100;

int N, M;
int table[NMAX][MMAX];
int h[NMAX][MMAX], l[NMAX][NMAX], r[NMAX][NMAX];
int square, rectangle;
vector<int> S;

int main()
{
	int i, j, head;
	scanf("%d %d", &N, &M);
	for(i = 1;i <= N;i += 1)
	{
		for(j = 1;j <= M;j += 1)
		{
			scanf("%d", &table[i][j]);
			if(i == 1 || table[i][j] != table[i - 1][j])
				h[i][j] = h[i - 1][j] + 1;
			else
				h[i][j] = 1;
		}
	}
	for(i = 1;i <= N;i += 1)
	{
		S.erase(S.begin(), S.end());
		S.push_back(1);
		head = 1;
		for(j = 2;j <= M;j += 1)
		{
			if(table[i][S.back()] == table[i][j])
			{
				S.erase(S.begin(), S.end());
				S.push_back(j);
				head = j;
			}
			else
			{
				while(!S.empty() && h[i][S.back()] > h[i][j])
					S.pop_back();
				if(S.empty())
					l[i][j] = j - head;
				else if(h[i][S.back()] == h[i][j])
					l[i][j] = j - S.back() + l[i][S.back()];
				else
					l[i][j] = j - S.back() - 1;
				S.push_back(j);
			}
		}
	}
	for(i = 1;i <= N;i += 1)
	{
		S.erase(S.begin(), S.end());
		S.push_back(M);
		head = M;
		for(j = M - 1;j;j -= 1)
		{
			if(table[i][S.back()] == table[i][j])
			{
				S.erase(S.begin(), S.end());
				S.push_back(j);
				head = j;
			}
			else
			{
				while(!S.empty() && h[i][S.back()] > h[i][j])
					S.pop_back();
				if(S.empty())
					r[i][j] = head - j;
				else if(h[i][S.back()] == h[i][j])
					r[i][j] = S.back() - j + r[i][S.back()];
				else
					r[i][j] = S.back() - j - 1;
				S.push_back(j);
			}
		}
	}
	for(i = 1;i <= N;i += 1)
	{
		for(j = 1;j <= M;j += 1)
		{
			rectangle = max(rectangle, h[i][j] * (l[i][j] + r[i][j] + 1));
			square = max(square, min(h[i][j], l[i][j] + r[i][j] + 1) * min(h[i][j], l[i][j] + r[i][j] + 1));
		}
	}
	printf("%d\n%d\n", square, rectangle);
	exit(0);
}
