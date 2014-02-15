#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>

using namespace std;

const int NMAX = 1100, INF = ~0u>>1;

int N, M, K, answer = INF;
deque<pair<int, int> > mR, mC[NMAX], MR, MC[NMAX];

int main()
{
	int i, j, value;
	scanf("%d %d %d", &N, &M, &K);
	for(i = 1;i <= N;i += 1)
	{
		while(!mR.empty())
			mR.pop_front();
		while(!MR.empty())
			MR.pop_front();
		for(j = 1;j <= M;j += 1)
		{
			scanf("%d", &value);
			while(!mR.empty() && mR.back().first > value)
				mR.pop_back();
			mR.push_back(make_pair(value, j));
			while(!MR.empty() && MR.back().first < value)
				MR.pop_back();
			MR.push_back(make_pair(value, j));
			while(!mR.empty() && mR.front().second + K <= j)
				mR.pop_front();
			while(!MR.empty() && MR.front().second + K <= j)
				MR.pop_front();
			if(j >= K)
			{
				while(!mC[j - K + 1].empty() && mC[j - K + 1].back().first > mR.front().first)
					mC[j - K + 1].pop_back();
				mC[j - K + 1].push_back(make_pair(mR.front().first, i));
				while(!MC[j - K + 1].empty() && MC[j - K + 1].back().first < MR.front().first)
					MC[j - K + 1].pop_back();
				MC[j - K + 1].push_back(make_pair(MR.front().first, i));
			}
		}
		if(i >= K)
		{
			for(j = 1;j <= M - K + 1;j += 1)
			{
				while(!mC[j].empty() && mC[j].front().second + K <= i)
					mC[j].pop_front();
				while(!MC[j].empty() && MC[j].front().second + K <= i)
					MC[j].pop_front();
				answer = min(answer, MC[j].front().first - mC[j].front().first);
			}
		}
	}
	printf("%d\n", answer);
	exit(0);
}
