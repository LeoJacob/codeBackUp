#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

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
int head, tail, Q[2 * NMAX][2];

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
	head = tail = 0;
	for(i = 0;;i += 1)
	{
		while(head != tail && (i - Q[head][1] + K) % K > K / 2)
			head += 1;
		if(i >= K && Q[head][1] >= K)
			break;
		if(head != tail)
			answer = max(answer, i + farthest[circle[x][i % K]] + Q[head][0]);
		while(head != tail && Q[tail - 1][0] <= farthest[circle[x][i % K]] - i)
			tail -= 1;
		Q[tail][0] = farthest[circle[x][i % K]] - i;
		Q[tail][1] = i;
		tail += 1;
	}
	for(i = 1;i < K;i += 1)
		farthest[circle[x][0]] = max(farthest[circle[x][0]], farthest[circle[x][i]] + min(i, K - i));
}

void dfs(int x)
{
	int i;
	dfn[x] = low[x] = ++stamp;
	circle[dfn[x]].push_back(x);
	for(i = V[x];i;i = E[i].next)
	{
		if(!use[(i + 1) / 2])
		{
			use[(i + 1) / 2] = true;
			if(dfn[E[i].y])
				low[x] = min(low[x], dfn[E[i].y]);
			else
			{
				dfs(E[i].y);
				low[x] = min(low[x], low[E[i].y]);
				if(low[E[i].y] == dfn[x])
				{
					solve(dfn[x]);
					circle[dfn[x]].erase(circle[dfn[x]].begin(), circle[dfn[x]].end());
					circle[dfn[x]].push_back(x);
				}
				else if(low[E[i].y] > dfn[x])
				{
					answer = max(answer, farthest[x] + 1 + farthest[E[i].y]);
					farthest[x] = max(farthest[x], 1 + farthest[E[i].y]);
				}
			}
		}
	}
	if(dfn[x] != low[x])
		circle[low[x]].push_back(x);
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
	exit(0);
}
