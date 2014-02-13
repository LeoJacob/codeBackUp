#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 501000;

struct State
{
	State *parent, *go[26];
	int len;
	State(int len): parent(NULL), len(len)
	{
		memset(go, 0, sizeof(go));
	}
};

int answer;
char str[NMAX];
State *root = new State(0), *last;

void expand(int c)
{
	State *p = last;
	State *np = new State(p->len + 1);
	for(;p && !p->go[c];p = p->parent)
		p->go[c] = np;
	if(!p)
		np->parent = root;
	else
	{
		State *q = p->go[c];
		if(q->len == p->len + 1)
			np->parent = q;
		else
		{
			State *nq = new State(p->len + 1);
			memcpy(nq->go, q->go, sizeof(nq->go));
			nq->parent = q->parent;
			q->parent = nq;
			np->parent = nq;
			for(;p && p->go[c] == q;p = p->parent)
				p->go[c] = nq;
		}
	}
	last = np;
}

int main()
{
	int i, j, len, length;
	State *opt;
	last = root;
	for(i = 1;i <= 2;i += 1)
	{
		scanf("%s", str);
		length = strlen(str);
		if(i == 1)
		{
			for(j = 0;j < length;j += 1)
				expand(str[j] - 'a');
		}
		else
		{
			opt = root;
			for(j = len = 0;j < length;j += 1)
			{
				while(opt && !opt->go[str[j] - 'a'])
					opt = opt->parent;
				if(opt)
				{
					len = min(len, opt->len) + 1;
					opt = opt->go[str[j] - 'a'];
				}
				else
				{
					opt = root;
					len = 0;
				}
				answer = max(answer, len);
			}
		}
	}
	printf("%d\n", answer);
	exit(0);
}
