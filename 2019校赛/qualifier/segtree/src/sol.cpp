#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

struct Three
{
	int l;
	int r;
	int ans;
	int maxx;
};

Three tree[N * 4];
int n, m;

void Build(int x, int l, int r)
{
	tree[x].l = l;
	tree[x].r = r;
    tree[x].ans = 1;
    tree[x].maxx = 0;
	if(l == r){

	}
	else{
		int mid;

		mid = l + ((r - l) >> 1);
		Build(x << 1, l, mid);
		Build(x << 1 | 1, mid + 1, r);
	}
}

int Quary(int x, int v)
{
	int ll;
	int rr;

	ll = tree[x].l;
	rr = tree[x].r;
	if(ll == rr){
		if(tree[x].maxx > v){
			return 1;
		}
		else{
			return 0;
		}
	}
	else{
		int mid;

		mid = ll + ((rr - ll) >> 1);
		if(tree[x << 1].maxx <= v){
			return Quary(x << 1 | 1, v);
		}
		else{
			return Quary(x << 1, v) + tree[x].ans - tree[x << 1].ans;
		}
	}
}

void Update(int x, int pos, int v)
{
	int ll;
	int rr;

	ll = tree[x].l;
	rr = tree[x].r;
	if(ll == rr){
		tree[x].maxx = v;
		tree[x].ans = 1;
	}
	else{
		int mid;

		mid = ll + ((rr - ll) >> 1);
		if(pos <= mid){
			Update(x << 1, pos, v);
		}
		else{
			Update(x << 1 | 1, pos, v);
		}
		tree[x].maxx = max(tree[x << 1].maxx, tree[x << 1 | 1].maxx);
		tree[x].ans = tree[x << 1].ans + Quary(x << 1 | 1, tree[x << 1].maxx);
		// printf("lalala = %d %d %d\n", ll, rr, tree[x].ans);
	}
}

int main(int argc, char const *argv[])
{
    int ncase;

    scanf("%d", &ncase);
	while(ncase --){
        scanf("%d%d", &n, &m);
		Build(1, 1, n);
		for(int i = 0; i < m; i ++){
			int pos;
			int x;

			scanf("%d%d", &pos, &x);
			Update(1, pos, x);
			printf("%d\n", tree[1].ans);
		}
	}

	return 0;
}
