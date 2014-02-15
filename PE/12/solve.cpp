#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 100000;

int factorCnt[NMAX], minFactorPower[NMAX];
bool isPrime[NMAX];
vector<int> prime;

void genPrime()
{
	int i, j;
	for(i = 2;i < NMAX;i += 1)
	{
		if(!isPrime[i])
		{
			prime.push_back(i);
			factorCnt[i] = 2;
			minFactorPower[i] = 1;
		}
		for(j = 0;j < prime.size() && i * prime[j] < NMAX;j += 1)
		{
			isPrime[i * prime[j]] = true;
			if(!(i % prime[j]))
			{
				factorCnt[i * prime[j]] = factorCnt[i] / (minFactorPower[i] + 1) * (minFactorPower[i] + 2);
				minFactorPower[i * prime[j]] = minFactorPower[i] + 1;
			}
			else
			{
				factorCnt[i * prime[j]] = factorCnt[i] * 2;
				minFactorPower[i * prime[j]] = 1;
			}
		}
	}
}

int main()
{
	int i, tmp;
	genPrime();
	for(i = 1;;i += 1)
	{
		tmp = factorCnt[i] * factorCnt[i + 1];
		if(!(i % 2))
			tmp = tmp / (minFactorPower[i] + 1) * minFactorPower[i];
		else
			tmp = tmp / (minFactorPower[i + 1] + 1) * minFactorPower[i + 1];
		if(tmp > 500)
			break;
	}
	printf("%d\n", i * (i + 1) / 2);
	system("pause");
	exit(0);
}
