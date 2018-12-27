//废物重写吧明天或者后天

#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 40010;

struct node{
	int l, r;
}itv[maxn];
struct SegTree{
	int left, right;
	bool on;
}Tree[maxn];
int T, n, ans;
int disc[maxn], p;
bool not_added;

void PushUp(int nowNode){
	Tree[nowNode].on = Tree[nowNode<<1].on && Tree[nowNode<<1|1].on;
}

void Build(int left, int right, int nowNode = 1){
	Tree[nowNode].left = left;
	Tree[nowNode].right = right;
	if(left == right){
		Tree[nowNode].on = false;
		return;
	}
	int mid((left + right) >> 1);
	Build(left, mid, nowNode<<1);
	Build(mid+1, right, nowNode<<1|1);
	PushUp(nowNode);
}

void Update(int uleft, int uright, int nowNode = 1){
	int left = Tree[nowNode].left, right = Tree[nowNode].right;
	if(uleft <= left && right <= uright){
		if(not_added){
			printf("wtf\n");
			Tree[nowNode].on = true;
			++ ans;
			not_added = false;
		}
		return;
	}
	int mid((left + right) >> 1);
	if(uleft <= mid)Update(uleft, uright, nowNode<<1);
	if(uright > mid)Update(uleft, uright, nowNode<<1|1);
	PushUp(nowNode);
}

int bs(int e, int left, int right){
	if(left >= right)return right;
	int mid = (left + right) >> 1;
	if(disc[mid] > e)return bs(e, left, mid);
	return bs(e, mid+1, right);
}

int main(){
	scanf("%d", &T);
	while(T--){
		p = ans = 0;
		scanf("%d", &n);
		for(int i = 0; i < n; ++ i){
			scanf("%d%d", &itv[i].l, &itv[i].r);
			disc[p++] = itv[i].l;
			disc[p++] = itv[i].r;
		}
		sort(disc, disc + p);
		p = unique(disc, disc + p) - disc;
		int tmp = p;
		for(int i = 1; i < tmp; ++ i)
			if(disc[i] - disc[i-1] > 1)disc[p++] = disc[i-1] + 1;
		p = unique(disc, disc + p) - disc;
		Build(1, p);
		for(int i = p-1; i >= 0; -- i){
			int left = bs(itv[i].l, 0, p)+1, right = bs(itv[i].r, 0, p) + 1;
			not_added = true;
			Update(left, right);
		}
		printf("%d\n", ans);
	}
	return 0;
}