#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
const int maxn = 30010;
const int INF = 0x3f3f3f3f;

int T;
int n;
int Disc[maxn], p;
vector<int> rec;
set<int> ans;
struct node
{
	int left, right;
}interval[maxn];

struct segTree
{
	int left, right;
	int lazy;
	set<int> rec;
	void update(int val)
	{
	    rec.clear();
	    lazy = val;
	    rec.insert(val);
	}
}Tree[maxn<<2];

void PushDown(int index)
{
    int val = Tree[index].lazy;
    if(val)
    {
        Tree[index<<1].update(val);
        Tree[index<<1|1].update(val);
        Tree[index].lazy = 0;
    }
}

void PushUp(int index)
{
    Tree[index].rec.clear();
    set<int>::iterator i, j;
    for(i = Tree[index<<1].rec.begin(); i != Tree[index<<1].rec.end(); ++i)
        Tree[index].rec.insert(*i);
    for(i = Tree[index<<1|1].rec.begin(); i != Tree[index<<1|1].rec.end(); ++i)
        Tree[index].rec.insert(*i);
}

void Build(int nowNode, int left, int right)
{
	//printf("%d %d\n", left, right);
	Tree[nowNode].left = left;
	Tree[nowNode].right = right;
	Tree[nowNode].rec.clear();
	if(left == right)
	{
		rec.push_back(nowNode);
		return;
	}
	int mid = (left + right)>>1;
	Build(nowNode<<1, left, mid);
	Build(nowNode<<1|1, mid+1, right);
}

void Update(int nowNode, int uleft, int uright, int post_index)
{
	int left = Tree[nowNode].left, right = Tree[nowNode].right;
	if(uleft <= left && right <= uright)
	{
		Tree[nowNode].update(post_index);
		return;
	}
	PushDown(nowNode);
	int mid = (left + right)>>1;
	if(uleft <= mid)Update(nowNode<<1, uleft, uright, post_index);
	if(uright > mid)Update(nowNode<<1|1, uleft, uright, post_index);
	PushUp(nowNode);
}

int bs(int left, int right, int e)
{
	if(left >= right)return right;
	int mid = (left + right)>>1;
	if(Disc[mid] > e)return bs(left, mid, e);
	return bs(mid+1, right, e);
}

void init()
{
	p = 0;
	memset(Disc, 0, sizeof(Disc));
	rec.clear();
	ans.clear();
}

int main()
{
    freopen("in.in", "r", stdin);
    scanf("%d", &T);
    int l, r;
    while(T--)
    {
    	init();
    	scanf("%d", &n);
    	for(int i = 0; i < n; i++)
    	{
    		scanf("%d%d", &l, &r);
    		interval[i].left = l;
    		interval[i].right = r;
    		Disc[p++] = l;
    		Disc[p++] = r;
    	}
    	sort(Disc, Disc + p);
    	int top = 1;
    	for(int i = 1; i < p; i++)
    		if(Disc[i] != Disc[i-1])Disc[top++] = Disc[i];
    	p = top;
    	for(int i = 1; i < p; i++)
    		if(Disc[i] - Disc[i-1] > 1)Disc[top++] = Disc[i-1] + 1;
    	sort(Disc, Disc + top);
    	Build(1, 1, top-1);
    	/*
    	printf("bs:\n");
    	for(int i = 0; i < n; i++)
   			printf("%d %d\n", bs(0, top, interval[i].left), bs(0, top, interval[i].right));
		*/
		for(int i = 0; i < n; i++)
			Update(1, bs(0, top, interval[i].left), bs(0, top, interval[i].right), i+1);
        printf("%d\n", Tree[1].rec.size());
    }
	return 0;
}
/**

1
5
1 4
2 6
8 10
3 4
7 10

*/
