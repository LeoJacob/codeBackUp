#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int NMAX = 1001000;

int N;
int degree[NMAX], hate[NMAX];
long long f[NMAX][2], answer;
deque<int> Q;
vector<int> S;

int main()
{
	int i, j;
	long long g[2], tmp;
	scanf("%d", &N);
	for(i = 1;i <= N;i += 1)
	{
		scanf("%lld %d", &f[i][1], &hate[i]);
		degree[hate[i]] += 1;
	}
	for(i = 1;i <= N;i += 1)
	{
		if(!degree[i])
			Q.push_back(i);
	}
	while(!Q.empty())
	{
		i = Q.front();
		Q.pop_front();
		f[hate[i]][1] += f[i][0];
		f[hate[i]][0] += max(f[i][0], f[i][1]);
		degree[hate[i]] -= 1;
		if(!degree[hate[i]])
			Q.push_back(hate[i]);
	}
	for(i = 1;i <= N;i += 1)
	{
		if(degree[i])
		{
			S.clear();
			while(degree[i])
			{
				degree[i] -= 1;
				S.push_back(i);
				i = hate[i];
			}
			g[0] = g[1] = f[i][1];
			for(j = 1;j < S.size();j += 1)
			{
				if(j == 1 || j + 1 == S.size())
				{
					g[0] += f[S[j]][0];
					g[1] += f[S[j]][0];
				}
				else
				{
					g[1] = f[S[j]][0] + max(g[0], g[1]);
					g[0] += f[S[j]][1];
					swap(g[0], g[1]);
				}
			}
			tmp = max(g[0], g[1]);
			g[0] = g[1] = f[i][0];
			for(j = 1;j < S.size();j += 1)
			{
				g[1] = f[S[j]][0] + max(g[0], g[1]);
				g[0] += f[S[j]][1];
				swap(g[0], g[1]);
			}
			tmp = max(tmp, max(g[0], g[1]));
			answer += tmp;
		}
	}
	printf("%lld\n", answer);
	exit(0);
}
