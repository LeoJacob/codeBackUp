#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 251000, NodeMAX = 501000;

struct State
{
	State *parent, *go[26];
	int len, right;
};

int N, pid;
int value[NMAX], answer[NMAX];
char str[NMAX];
State pool[NodeMAX];
State *root = &pool[pid], *last = &pool[pid];
State *order[NodeMAX];

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
			memcpy(nq->go, q->go, sizeof(nq->go));
			nq->len = p->len + 1;
			nq->parent = q->parent;
			q->parent = np->parent = nq;
			for(;p && p->go[c] == q;p = p->parent)
				p->go[c] = nq;
		}
	}
	last = np;
}

void createOrder()
{
	int i;
	for(i = 0;i <= pid;i += 1)
		value[pool[i].len] += 1;
	for(i = 1;i <= N;i += 1)
		value[i] += value[i - 1];
	for(i = 0;i <= pid;i += 1)
		order[--value[pool[i].len]] = &pool[i];
}

int main()
{
	int i;
	scanf("%s", str);
	N = strlen(str);
	for(i = 0;i < N;i += 1)
		expand(str[i] - 'a');
	createOrder();
	for(i = pid;i > 0;i -= 1)
	{
		order[i]->parent->right += order[i]->right;
		answer[order[i]->len] = max(answer[order[i]->len], order[i]->right);
	}
	for(i = N - 1;i > 0;i -= 1)
		answer[i] = max(answer[i], answer[i + 1]);
	for(i = 1;i <= N;i += 1)
		printf("%d\n", answer[i]);
	exit(0);
}
