#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 2000000;

long long answer;
bool isPrime[NMAX];
vector<int> prime;

int genPrime()
{
	int i, j;
	for(i = 2;i < NMAX;i += 1)
	{
		if(!isPrime[i])
		{
			prime.push_back(i);
			answer += i;
		}
		for(j = 0;j < prime.size() && i * prime[j] < NMAX;j += 1)
		{
			isPrime[i * prime[j]] = true;
			if(!(i % prime[j]))
				break;
		}
	}
}

int main()
{
	genPrime();
	printf("%I64d\n", answer);
	system("pause");
	exit(0);
}
