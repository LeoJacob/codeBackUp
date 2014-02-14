#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int NMAX = 1010000, INF = ~0u>>1;

struct Node
{
	Node *father;
	Node *child[2];
	int ans;
	int value;
	int l;
	int r;
	int size;
	int type;
};

int N, M;
int pid;
Node pool[NMAX];
Node *root, *null = &pool[pid];
int chart[NMAX][2];
priority_queue<int, vector<int>, greater<int> > heap, del;

void init()
{
	null->child[0] = null->child[1] = null;
	null->size = 0;
	root = null;
}

void update(Node *node)
{
	node->size = node->child[0]->size + node->child[1]->size + 1;
	node->l = node->r = node->value;
	node->ans = INF;
	if(node->child[0] != null)
	{
		node->l = node->child[0]->l;
		node->ans = min(node->ans, node->value - node->child[0]->r);
		node->ans = min(node->ans, node->child[0]->ans);
	}
	if(node->child[1] != null)
	{
		node->r = node->child[1]->r;
		node->ans = min(node->ans, node->child[1]->l - node->value);
		node->ans = min(node->ans, node->child[1]->ans);
	}
}

void rotate(Node *node, int x)//将该节点转成根 
{
	int y;
	Node *p = node->father, *tmp;
	y = p->type;
	tmp = p->father;
	node->father = tmp;
	node->type = y;
	if(y != 2)
		tmp->child[y] = node;
	else
		root = node;
	y = 1 - x;
	tmp = node->child[y];
	tmp->father = p;
	tmp->type = x;
	p->child[x] = tmp;
	node->child[y] = p;
	p->father = node;
	p->type = y;
	update(p);
	update(node);
}

void maintain(Node *node, bool flag)
{
	if(!flag)
	{
		if(node->child[0]->child[0]->size > node->child[1]->size)
			rotate(node->child[0], 0);
		else
		{
			if(node->child[0]->child[1]->size > node->child[1]->size)
			{
				rotate(node->child[0]->child[1], 1);
				rotate(node->child[0], 0);
			}
			else
				return;
		}
	}
	else
	{
		if(node->child[1]->child[1]->size > node->child[0]->size)
			rotate(node->child[1], 1);
		else
		{
			if(node->child[1]->child[0]->size > node->child[0]->size)
			{
				rotate(node->child[1]->child[0], 0);
				rotate(node->child[1], 1);
			}
			else
				return;
		}
	}
	node = node->father;
	maintain(node->child[0], false);
	maintain(node->child[1], true);
	maintain(node, false);
	maintain(node, true);
}

void insert(Node *node, int value, Node *father, int type)
{
	if(node == null)
	{
		pool[++pid] = (Node){father, {null, null}, INF, value, value, value, 1, type};
		if(father == null)
		{
			root = &pool[pid];
			pool[pid].type = 2;
		}
		else
			father->child[type] = &pool[pid];
	}
	else
	{
		if(value < node->value)
			insert(node->child[0], value, node, 0);
		else
			insert(node->child[1], value, node, 1);
		update(node);
		maintain(node, value >= node->value);
	}
}

int main()
{
	int i, x, y;
	char opt[20];
	init();
	scanf("%d %d", &N, &M);
	for(i = 1;i <= N;i += 1)
	{
		scanf("%d", &x);
		chart[i][0] = chart[i][1] = x;
		insert(root, x, null, 0);
		if(i != 1)
			heap.push(abs(x - chart[i - 1][0]));
	}
	for(i = 1;i <= M;i += 1)
	{
		scanf("%s", opt);
		if(opt[0] == 'I')
		{
			scanf("%d %d", &x, &y);
			if(x != N)
			{
				heap.push(abs(y - chart[x + 1][0]));
				del.push(abs(chart[x][1] - chart[x + 1][0]));
			}
			heap.push(abs(y - chart[x][1]));
			chart[x][1] = y;
			insert(root, y, null, 0);
		}
		else if(opt[4] == 'G')
		{
			while(!del.empty() && heap.top() == del.top())
			{
				heap.pop();
				del.pop();
			}
			printf("%d\n", heap.top());
		}
		else
			printf("%d\n", root->ans);
	}
	exit(0);
}
