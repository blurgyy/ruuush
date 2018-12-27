#include<bits/stdc++.h>
using namespace std;
const int maxn = 10001;

struct SegTree{
	int left, right;
	int sum;
}Tree[maxn<<2];

int a[maxn], n;

void PushUp(int nowNode){
	Tree[nowNode].sum = Tree[nowNode<<1].sum + Tree[nowNode<<1|1].sum;
}

void Build(int left = 1, int right = n, int nowNode =  1){
	Tree[nowNode].left = left;
	Tree[nowNode].right = right;
	if(left == right){
		Tree[nowNode].sum = a[right];
		return;
	}
	int mid((left + right) >> 1);
	Build(left, mid, nowNode<<1);
	Build(mid + 1, right, nowNode<<1|1);
	PushUp(nowNode);
}

void Update(int pos, int val, int nowNode = 1){
	int left = Tree[nowNode].left, right = Tree[nowNode].right;
	if(left == right){
		Tree[nowNode].sum = val;
		return;
	}
	int mid((left + right) >> 1);
	if(pos <= mid)Update(pos, val, nowNode<<1);
	else Update(pos, val, nowNode<<1|1);
	PushUp(nowNode);
}

int Query(int qleft, int qright, int nowNode = 1){
	int left = Tree[nowNode].left, right = Tree[nowNode].right;
	int ret = 0;
	if(qleft <= left && right <= qright){
		return Tree[nowNode].sum;
	}
	int mid((left + right) >> 1);
	if(qleft <= mid)ret += Query(qleft, qright, nowNode<<1);
	if(qright > mid)ret += Query(qleft, qright, nowNode<<1|1);
	return ret;
}

int main(){
	while(~scanf("%d", &n)){
		int q;
		for(int i = 1; i <= n; ++ i)
			scanf("%d", a + i);
		Build();
		scanf("%d", &q);
		while(q--){
			char op[5];
			int aa, bb;
			scanf("%s%d%d", op, &aa, &bb);
			if(!strcmp(op, "u"))
				Update(aa, bb);
			if(!strcmp(op, "q"))
				printf("%d\n", Query(aa, bb));
		}
	}
	return 0;
}