#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 775147;

bool isPrime[NMAX];
vector<int> prime;

void genPrime()
{
	int i, j;
	for(i = 2;i < NMAX;i += 1)
	{
		if(!isPrime[i])
			prime.push_back(i);
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
	int i, answer;
	long long x = 600851475143ll;
	genPrime();
	for(i = 0;i < prime.size();i += 1)
	{
		while(!(x % prime[i]))
		{
			x /= prime[i];
			answer = prime[i];
		}
	}
	printf("%d\n", answer);
	system("pause");
	exit(0);
}
