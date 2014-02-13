#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

struct State
{
	State *parent, *go[26];
	int len;
	State(int len): parent(NULL), len(len)
	{
		memset(go, 0, sizeof(go));
	}
};

State *root = new State(0), *last;

void extend(int c)
{
	State *p = last, *np = new State(p->len + 1);
	for(;p && !p->go[c];p = p->parent)
		p->go[c] = np;
	if(!p)
		np->parent = root;
	else
	{
		State *q = p->go[c];
		if(p->len + 1 == q->len)
			np->parent = q;
		else
		{
			State *nq = new State(p->len + 1);
			memcpy(nq->go, q->go, sizeof(q->go));
			nq->parent = p->parent;
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
	last = root;
	exit(0);
}
