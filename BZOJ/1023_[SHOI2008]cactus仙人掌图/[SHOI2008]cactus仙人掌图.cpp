#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int NMAX = 51000, EMAX = 201000;

struct Edge
{
	int y;
	int next;
};

int N, M, answer;
int V[NMAX], eid, stamp;
int dfn[NMAX], low[NMAX], farthest[NMAX];
Edge E[EMAX];
bool use[EMAX];
vector<int> circle[NMAX];
deque<pair<int, int> > Q;

void insert(int x, int y)
{
	E[++eid] = (Edge){y, V[x]};
	V[x] = eid;
	E[++eid] = (Edge){x, V[y]};
	V[y] = eid;
}

void solve(int x)
{
	int i, K = circle[x].size();
	while(!Q.empty())
		Q.pop_front();
	for(i = 0;;i += 1)
	{
		while(!Q.empty() && (i - Q.front().second + K) % K > K / 2)
			Q.pop_front();
		if(i >= K && Q.front().second >= K)
			break;
		if(!Q.empty())
			answer = max(answer, i + farthest[circle[x][i % K]] + Q.front().first);
		while(!Q.empty() && Q.back().first <= farthest[circle[x][i % K]] - i)
			Q.pop_back();
		Q.push_back(make_pair(farthest[circle[x][i % K]] - i, i));
	}
	for(i = 1;i < K;i += 1)
		farthest[circle[x][0]] = max(farthest[circle[x][0]], farthest[circle[x][i]] + min(i, K - i));
}

void dfs(int x)
{
	int i;
	//printf("At %d\n", x);
	dfn[x] = low[x] = ++stamp;
	circle[dfn[x]].push_back(x);
	for(i = V[x];i;i = E[i].next)
	{
		if(!use[(i + 1) / 2])
		{
			use[(i + 1) / 2] = true;
			//printf("process %d\n", E[i].y);
			if(dfn[E[i].y])
				low[x] = min(low[x], dfn[E[i].y]);
			else
			{
				dfs(E[i].y);
				low[x] = min(low[x], low[E[i].y]);
				if(low[E[i].y] == dfn[x])
				{
					//printf("get a circle end at %d\n", x);
					solve(dfn[x]);
					circle[dfn[x]].erase(circle[dfn[x]].begin(), circle[dfn[x]].end());
					circle[dfn[x]].push_back(x);
					//printf("%d's farthest: %d\n", x, farthest[x]);
				}
				else if(low[E[i].y] > dfn[x])
				{
					//printf("get a branch end at %d\n", x);
					answer = max(answer, farthest[x] + 1 + farthest[E[i].y]);
					farthest[x] = max(farthest[x], 1 + farthest[E[i].y]);
					//printf("%d's farthest: %d\n", x, farthest[x]);
				}
			}
		}
	}
	if(dfn[x] != low[x])
		circle[low[x]].push_back(x);
	//printf("back from %d\n", x);
}

int main()
{
	int i, j, k, x, y;
	scanf("%d %d", &N, &M);
	for(i = 1;i <= M;i += 1)
	{
		scanf("%d %d", &k, &x);
		for(j = 2;j <= k;j += 1)
		{
			scanf("%d", &y);
			insert(x, y);
			x = y;
		}
	}
	dfs(1);
	printf("%d\n", answer);
	//system("pause");
	exit(0);
}
