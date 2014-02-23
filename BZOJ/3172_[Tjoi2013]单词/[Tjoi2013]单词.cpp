#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int SMAX = 27, LMAX = 1001000, PMAX = 2001000;

struct State
{
	State *parent, *go[SMAX];
	int len;
	int right;
};

int N, pid, barrel[LMAX];
State pool[PMAX];
State *root = &pool[pid], *last = &pool[pid], *order[PMAX];
char str[LMAX];

void expand(int c)
{
	State *p = last, *np = &pool[++pid];
	np->len = p->len + 1;
	np->right = 1;
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
			State *nq = &pool[++pid];
			nq->len = p->len + 1;
			memcpy(nq->go, q->go, sizeof(nq->go));
			nq->parent = q->parent;
			q->parent = np->parent = nq;
			for(;p && p->go[c] == q;p = p->parent)
				p->go[c] = nq;
		}
	}
	last = np;
}

void buildOrder()
{
	int i;
	for(i = 0;i <= pid;i += 1)
		barrel[pool[i].len] += 1;
	for(i = 1;i <= last->len;i += 1)
		barrel[i] += barrel[i - 1];
	for(i = 0;i <= pid;i += 1)
		order[--barrel[pool[i].len]] = &pool[i];
}

void buildRight()
{
	int i;
	for(i = pid;i > 0;i -= 1)
		order[i]->parent->right += order[i]->right;
}

int main()
{
	int i, j, len, pos = 0;
	State *now;
	scanf("%d", &N);
	for(i = 0;i < N;i += 1)
	{
		scanf("%s", str + pos);
		len = strlen(str + pos);
		for(j = 0;j < len;j += 1)
			expand(str[pos + j] - 'a');
		expand(26);
		str[pos + len] = 'a' + 26;
		pos += len + 1;
	}
	buildOrder();
	buildRight();
	for(i = pos = 0;i < N;i += 1)
	{
		now = root;
		for(j = pos;str[j] != 'a' + 26;j += 1)
			now = now->go[str[j] - 'a'];
		printf("%d\n", now->right);
		pos = j + 1;
	}
	exit(0);
}
