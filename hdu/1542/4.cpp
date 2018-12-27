#include<bits/stdc++.h>
using namespace std;
const int maxn = 1010;

struct Segment{
	double l, r, h;
	int side;	//-1 for top, 1 for bottom;
	bool operator< (Segment b){
		return h < b.h;
	}
}seg[maxn];
struct SegTreeNode{
	int left, right;
	int cnt;
	double sum;
}Tree[maxn<<2];
int n, rp, p, Case = 0;
double x1, x2, y1, y2, A;
double rec[maxn];

void add_point(){
	seg[p].l = seg[p+1].l = x1;
	seg[p].r = seg[p+1].r = x2;
	seg[p].side = 1;
	seg[p+1].side = -1;
	seg[p++].h = y1;
	seg[p++].h = y2;
	rec[rp++] = x1;
	rec[rp++] = x2;
}

void PushUp(int nowNode){
	Tree[nowNode].sum = 0;
	Tree[nowNode].sum += Tree[nowNode<<1].sum * (Tree[nowNode<<1].left != Tree[nowNode<<1].right || Tree[nowNode<<1].cnt > 0);
	Tree[nowNode].sum += Tree[nowNode<<1|1].sum * (Tree[nowNode<<1|1].left != Tree[nowNode<<1|1].right || Tree[nowNode<<1|1].cnt > 0);
}

void PushDown(int nowNode){
	Tree[nowNode<<1].cnt = Tree[nowNode<<1|1].cnt = Tree[nowNode].cnt;
}

void build(int left = 1, int right = rp-1, int nowNode = 1){
	Tree[nowNode].left = left;
	Tree[nowNode].right = right;
	printf("building: %f(%d) to %f(%d)\n", rec[left], left, rec[right], right);
	if(left == right){
		Tree[nowNode].sum = rec[right];
		Tree[nowNode].cnt = 0;
		return;
	}
	int mid = (left + right) >> 1;
	build(left, mid, nowNode<<1);
	build(mid + 1, right, nowNode<<1|1);
}

void update(int uleft, int uright, int side, int nowNode = 1){
	int left = Tree[nowNode].left, right = Tree[nowNode].right;
	if(uleft <= left && right <= uright){
		Tree[nowNode].cnt += side;
		return;
	}
	PushDown(nowNode);
	int mid = (left + right) >> 1;
	if(uleft <= mid)update(uleft, uright, side, nowNode<<1);
	if(uright > mid)update(uleft, uright, side, nowNode<<1|1);
	PushUp(nowNode);
}

int bs(double e, double arr[], int left, int right){
	if(left >= right)return right;
	int mid = (left + right) >> 1;
	if(e <= arr[mid])return bs(e, arr, left, mid);
	return bs(e, arr, mid + 1, right);
}

int idx(double x){
	return bs(x, rec, 1, rp - 1);
}

void init(){
	rp = p = 1;
	A = 0;
}

int main(){
	freopen("in.in", "r", stdin);
	while(~scanf("%d", &n) && n){
		init();
		for(int i = 0; i < n; ++ i){
			scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
			add_point();
		}
		sort(seg + 1, seg + p);
		sort(rec + 1, rec + rp);
		rp = unique(rec + 1, rec + rp) - rec - 1;
		for(int i = 1; i < rp; ++ i)
			printf("%f%c", rec[i], " \n"[i == rp-1]);
		build();
		double prevh = seg[1].h;
		for(int i = 1; i < p; ++ i){
			int l = idx(seg[i].l), r = idx(seg[i].r);
			A += (seg[i].h - prevh) * Tree[1].sum;
			update(l, r, seg[i].side);
			prevh = seg[i].h;
		}
		printf("%f\n", A);
	}
	return 0;
}