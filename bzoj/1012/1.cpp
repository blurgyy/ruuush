#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 200010;

int q;
ll mod, x;
char op[3];
struct T{
	T(): left(-1), right(-1), maxx(-1){}
	int left, right;
	ll maxx;
}Tree[maxn<<2];

void pushUp(int now){
	Tree[now].maxx = max(Tree[now<<1].maxx, Tree[now<<1|1].maxx);
}

void build(int left, int right, int now = 1){
	Tree[now].left = left;
	Tree[now].right = right;
	Tree[now].maxx = -1;
	if(left == right){
		return;
	}
	int mid = left + right >> 1;
	build(left, mid, now << 1);
	build(mid+1, right, now << 1 | 1);
	pushUp(now);
}

void update(int pos, ll x, int now = 1){
	int left = Tree[now].left;
	int right = Tree[now].right;
	if(left == right){
		Tree[now].maxx = x;
		// printf("a[%d] := %d\n", Tree[now].right, x);
		return;
	}
	int mid = left + right >> 1;
	if(pos <= mid) update(pos, x, now << 1);
	else update(pos, x, now << 1 | 1);
	pushUp(now);
}

ll query(int qleft, int qright, int now = 1){
	// printf("now = %d, qleft = %d, qright = %d\n", now, qleft, qright);
	int left = Tree[now].left;
	int right = Tree[now].right;
	if(qleft <= left && right <= qright){
		return Tree[now].maxx;
	}
	ll ret = -1;
	int mid = left + right >> 1;
	if(qleft <= mid) ret = max(ret, query(qleft, qright, now << 1));
	if(qright > mid) ret = max(ret, query(qleft, qright, now << 1 | 1));
	return ret;
}

void ini(){
	memset(Tree, -1, sizeof(Tree));
}

int main(){
	while(~scanf("%d%lld", &q, &mod)){
		ini();
		int len = 0;
		ll lastans = 0;
		build(1, 200001);
		while(q --){
			scanf("%s%lld", op, &x);
			if(!strcmp(op, "Q")){
				lastans = query(len-x+1, len);
				printf("%lld\n", lastans);
			}
			else if(!strcmp(op, "A")){
				update(++ len, (x + lastans) % mod);
			}
			else {
				printf("wtf\n");
			}
		}
	}
	return 0;
}
