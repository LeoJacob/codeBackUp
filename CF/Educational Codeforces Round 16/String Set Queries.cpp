#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

const int ALPHA = 26, LOGMAX = 20, NMAX = 301000, LMAX = 301000;

struct Node
{
	int cnt;
	Node *fail;
	Node *next[ALPHA];
};

struct StringSet
{
	int cnt;
	int store[NMAX];
	Node *AC[LOGMAX];
};

int N;
string S[NMAX];
StringSet normal, del;

Node *createNode()
{
	int i;
	Node *n = (Node *)malloc(sizeof(Node));
	n->cnt = 0;
	n->fail = NULL;
	for(i = 0;i < ALPHA;i += 1)
		n->next[i] = NULL;
	return n;
}

int index(char x)
{
	return x - 'a';
}

void insert2AC(Node *root, const string &str)
{
	int i, x;
	Node *pos = root;
	for(i = 0;i < (int)str.length();i += 1)
	{
		if(!pos->next[x = index(str[i])])
			pos->next[x] = createNode();
		pos = pos->next[x];
	}
	pos->cnt += 1;
}

void buildAC(Node *root)
{
	int i;
	Node *pos;
	deque<Node *> Q;
	root->fail = root;
	Q.push_back(root);
	while(!Q.empty())
	{
		pos = Q.front();
		Q.pop_front();
		pos->cnt += pos->fail->cnt;
		for(i = 0;i < ALPHA;i += 1)
		{
			if(!pos->next[i])
				continue;
			for(pos->next[i]->fail = pos->fail;
					pos->next[i]->fail != root && !(pos->next[i]->fail->next[i]);
					pos->next[i]->fail = pos->next[i]->fail->fail);
			if(pos != root && pos->next[i]->fail->next[i])
				pos->next[i]->fail = pos->next[i]->fail->next[i];
			Q.push_back(pos->next[i]);
		}
	}
}

inline int lowbit(int x)
{
	return x & (-x);
}

void initStringSet(StringSet &A)
{
	int i;
	A.cnt = 0;
	memset(A.store, 0, sizeof(A.store));
	for(i = 0;i < LOGMAX;i += 1)
		A.AC[i] = createNode();
}

void insert2StringSet(StringSet &A, int x)
{
	int i, pos, num = lowbit(A.cnt + 1) - 1;
	memcpy(A.store + num + 1, A.store + 1, num * sizeof(int));
	A.store[2 * num + 1] = x;
	memset(A.store + 1, 0, num * sizeof(int));
	for(pos = 0;(1<<pos) <= num;pos += 1)
	{
		A.AC[pos] = createNode();
		buildAC(A.AC[pos]);
	}
	for(i = num + 1;i <= 2 * num + 1;i += 1)
		insert2AC(A.AC[pos], S[A.store[i]]);
	buildAC(A.AC[pos]);
	A.cnt += 1;
}

int searchAC(Node *root, const string &str)
{
	int i, x, res = 0;
	Node *pos = root;
	for(i = 0;i < (int)str.length();i += 1)
	{
		x = index(str[i]);
		while(pos != root && !(pos->next[x]))
			pos = pos->fail;
		if(pos->next[x])
			pos = pos->next[x];
		res += pos->cnt;
	}
	return res;
}

int searchStringSet(StringSet &A, string str)
{
	int i, res = 0;
	for(i = 0;i < LOGMAX;i += 1)
		res += searchAC(A.AC[i], str);
	return res;
}

int main()
{
	int i, t;
	char x[LMAX];
	initStringSet(normal);
	initStringSet(del);
	scanf("%d", &N);
	for(i = 1;i <= N;i += 1)
	{
		scanf("%d %s", &t, x);
		S[i] = x;
		if(t == 1)
			insert2StringSet(normal, i);
		else if(t == 2)
			insert2StringSet(del, i);
		else
		{
			printf("%d\n", searchStringSet(normal, S[i]) - searchStringSet(del, S[i]));
			fflush(stdout);
		}
	}
	exit(0);
}
