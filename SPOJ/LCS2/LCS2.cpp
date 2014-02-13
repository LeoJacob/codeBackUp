#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 201000;

struct State
{
	State *parent, *go[26];
	int len, lcs, ans;
};

int pid = 0, answer = 0;
int value[NMAX];
char str[NMAX];
State pool[NMAX];
State *root = &pool[pid], *last = &pool[pid], *order[NMAX];

void expand(int c)
{
	State *p = last;
	State *np = &pool[++pid];
	np->lcs = 0;
	np->ans = np->len = p->len + 1;
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
			nq->ans = nq->len = p->len + 1;
			nq->lcs = 0;
			memcpy(nq->go, q->go, sizeof(nq->go));
			nq->parent = q->parent;
			q->parent = np->parent = nq;
			for(;p && p->go[c] == q;p = p->parent)
				p->go[c] = nq;
		}
	}
	last = np;
}

int main()
{
	int i, j, len, length;
	State *pos;
	for(i = 1;scanf("%s", str) != EOF;i += 1)
	{
		length = strlen(str);
		if(i == 1)
		{
			for(j = 0;j < length;j += 1)
				expand(str[j] - 'a');
			for(j = 0;j <= pid;j += 1)
				value[pool[j].len] += 1;
			for(j = 1;j <= length;j += 1)
				value[j] += value[j - 1];
			for(j = 0;j <= pid;j += 1)
				order[--value[pool[j].len]] = &pool[j];
		}
		else
		{
			pos = root;
			for(j = len = 0;j < length;j += 1)
			{
				while(pos && !pos->go[str[j] - 'a'])
					pos = pos->parent;
				if(pos)
				{
					len = min(len, pos->len) + 1;
					pos = pos->go[str[j] - 'a'];
				}
				else
				{
					pos = root;
					len = 0;
				}
				pos->lcs = max(pos->lcs, len);
			}
			for(j = pid;j >= 0;j -= 1)
			{
				order[j]->ans = min(order[j]->ans, order[j]->lcs);
				if(order[j]->parent)
					order[j]->parent->lcs = max(order[j]->parent->lcs, order[j]->lcs);
				order[j]->lcs = 0;
			}
		}
	}
	for(j = 0;j <= pid;j += 1)
		answer = max(answer, pool[j].ans);
	printf("%d\n", answer);
	exit(0);
}
