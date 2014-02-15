#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 1100;
const double PI = 3.14159265358;

struct Circle
{
	double x;
	double y;
	double r;
};

int N;
double answer;
Circle circle[NMAX];
vector<pair<double, double> > interval;

bool cmp(Circle x, Circle y)
{
	if(x.x == y.x)
	{
		if(x.y == y.y)
			return x.r < y.r;
		return x.y < y.y;
	}
	return x.x < y.x;
}

int main()
{
	int i, j;
	double x, y, r;
	double alpha, beta, dd, pre, tmp;
	scanf("%d", &N);
	for(i = 1;i <= N;i += 1)
	{
		scanf("%lf %lf %lf", &r, &x, &y);
		circle[i] = (Circle){x, y, r};
	}
	for(i = 1;i <= N;i += 1)
	{
		interval.erase(interval.begin(), interval.end());
		for(j = i + 1;j <= N;j += 1)
		{
			if(circle[i].x == circle[j].x && circle[i].y == circle[j].y && circle[i].r <= circle[j].r)
			{
				interval.push_back(make_pair(-PI, PI));
				break;
			}
			dd = (circle[i].x - circle[j].x) * (circle[i].x - circle[j].x) + (circle[i].y - circle[j].y) * (circle[i].y - circle[j].y);
			if(dd >= (circle[i].r + circle[j].r) * (circle[i].r + circle[j].r))
				continue;
			if(dd <= (circle[i].r - circle[j].r) * (circle[i].r - circle[j].r))
			{
				if(circle[j].r >= circle[i].r)
				{
					interval.push_back(make_pair(-PI, PI));
					break;
				}
				continue;
			}
			alpha = atan2(circle[j].y - circle[i].y, circle[j].x - circle[i].x);
			beta = acos((dd + circle[i].r * circle[i].r - circle[j].r * circle[j].r) / (2 * sqrt(dd) * circle[i].r));
			if(alpha - beta < -PI)
			{
				interval.push_back(make_pair(alpha - beta + 2 * PI, PI));
				interval.push_back(make_pair(-PI, alpha + beta));
			}
			if(alpha + beta > PI)
			{
				interval.push_back(make_pair(-PI, alpha + beta - 2 * PI));
				interval.push_back(make_pair(alpha - beta, PI));
			}
			else
				interval.push_back(make_pair(alpha - beta, alpha + beta));
		}
		sort(interval.begin(), interval.end());
		pre = -PI;
		tmp = 0;
		for(vector<pair<double, double> >::iterator p = interval.begin();p != interval.end();p++)
		{
			if(p->first > pre)
			{
				answer += circle[i].r * (p->first - pre);
				tmp += circle[i].r * (p->first - pre);
			}
			pre = max(pre, p->second);
		}
		answer += circle[i].r * (PI - pre);
		tmp += circle[i].r * (PI - pre);
	}
	printf("%.3f\n", answer);
	exit(0);
}
