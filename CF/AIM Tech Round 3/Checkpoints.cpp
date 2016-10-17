#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

int N, A, ans;
vector<int> pos, neg;

int dis(vector<int> &A, int mode)
{
	if((int)A.size() - mode <= 0)
		return 0;
	return A[A.size() - mode - 1];
}

int main()
{
	int i, x;
	scanf("%d %d", &N, &A);
	for(i = 1;i <= N;i += 1)
	{
		scanf("%d", &x);
		x -= A;
		if(x >= 0)
			pos.push_back(x);
		else
			neg.push_back(-x);
	}
	sort(pos.begin(), pos.end());
	sort(neg.begin(), neg.end());
	ans = dis(pos, 0) + dis(neg, 1) + min(dis(pos, 0), dis(neg, 1));
	ans = min(ans, dis(pos, 1) + dis(neg, 0) + min(dis(pos, 1), dis(neg, 0)));
	printf("%d\n", ans); 
	exit(0);
}
