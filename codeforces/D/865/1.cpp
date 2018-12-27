#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 300010;

struct Segtree
{
	int left, right;
	ll sum;
}Tree[maxn<<2];
int N, in;

void PushUp(int nowNode){
	Tree[nowNode].sum = Tree[nowNode<<1].sum + Tree[nowNode<<1|1].sum;
}

void Build(int left, int right, int nowNode = 1){
	Tree[nowNode].left = left;
	Tree[nowNode].right = right;
	if(left == right){
		Tree[nowNode].sum = 0;
		return;
	}
	int mid = (left + right)>>1;
	Build(left, mid, nowNode<<1);
	Build(mid+1, right, nowNode<<1|1);
	PushUp(nowNode);
}

void Update(int pos, int val, int nowNode = 1){
	int left = Tree[nowNode].left, right = Tree[nowNode].right;
	if(left == right){
		Tree[nowNode].sum = val;
		while(nowNode<<=1)
			PushUp(nowNode);
		return;
	}
	int mid = (left + right)>>1;
	if(pos <= mid)return Update(pos, val, nowNode<<1);
	else return Update(pos, val, nowNode<<1|1);
}

int main(){
	while(~scanf("%d", &N)){
		for(int i = 1; i <= N; ++ i){
			scanf("%d", &in);
			Update(i, in);
		}
	}
}