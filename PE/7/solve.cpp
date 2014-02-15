#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 1000000;

bool isPrime[NMAX];
vector<int> prime;

int genPrime()
{
	int i, j;
	for(i = 2;;i += 1)
	{
		if(!isPrime[i])
			prime.push_back(i);
		if(prime.size() == 10001)
			return i;
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
	printf("%d\n", genPrime());
	system("pause");
	exit(0);
}
