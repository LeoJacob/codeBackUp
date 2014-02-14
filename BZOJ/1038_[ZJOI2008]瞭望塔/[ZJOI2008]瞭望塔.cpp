#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int NMAX = 310;

int N;
double x[NMAX], y[NMAX];
vector<pair<double, double> > line;
deque<pair<double, double> > S;

bool cmp(pair<double, double> x, pair<double, double> y)
{
	if(x.first == y.first)
		return x.second > y.second;
	return x.first < y.first;
}

bool better(pair<double, double> x, pair<double, double> y, pair<double, double> z)
{
	return (x.first - z.first) * (y.second - x.second) <= (x.first - y.first) * (z.second - x.second);
}

void halfPlaneIntersection()
{
	int i;
	double k;
	for(i = 1;i < N;i += 1)
	{
		k = (y[i + 1] - y[i]) / (x[i + 1] - x[i]);
		line.push_back(make_pair(k, y[i] - k * x[i]));
	}
	sort(line.begin(), line.end(), cmp);
	S.push_back(line[0]);
	for(i = 1;i < line.size();i += 1)
	{
		while(S.size() > 1 && better(S[S.size() - 2], line[i], S[S.size() - 1]))
			S.pop_back();
		S.push_back(line[i]);
	}
}

int main()
{
	int i, j;
	double answer, tmp;
	scanf("%d", &N);
	for(i = 1;i <= N;i += 1)
		scanf("%lf", &x[i]);
	for(i = 1;i <= N;i += 1)
		scanf("%lf", &y[i]);
	halfPlaneIntersection();
	answer = 99999999999.0;
	for(i = 1, j = 0;i <= N;i += 1)
	{
		while(j + 1 < S.size() && (S[j + 1].second - S[j].second) / (S[j].first - S[j + 1].first) < x[i])
			j += 1;
		answer = min(answer, S[j].first * x[i] + S[j].second - y[i]);
	}
	for(i = 0, j = 1;i + 1 < S.size();i += 1)
	{
		tmp = (S[i + 1].second - S[i].second) / (S[i].first - S[i + 1].first);
		if(tmp < x[1] || tmp > x[N])
			continue;
		while(j + 1 < N && x[j + 1] < tmp)
			j += 1;
		answer = min(answer, S[i].first * tmp + S[i].second - (y[j] + (y[j] - y[j + 1]) / (x[j] - x[j + 1]) * (tmp - x[j])));
	}
	printf("%.3lf\n", answer);
	exit(0);
}
