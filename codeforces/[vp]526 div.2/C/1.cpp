#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const size_t maxn = 100010;
const int mod = 1e9 + 7;

char s[maxn];
struct STN{
	int left, right;
	ll sum;
	ll lazy;
	void upd(ll val){
		sum = (sum + 1ll * (right - left + 1) * val % mod) % mod;
		lazy = (lazy + val) % mod;
	}
}Tree[maxn<<2];

void pushDown(int x){
	ll val = Tree[x].lazy;
	if(val){
		Tree[x<<1].upd(val);
		Tree[x<<1|1].upd(val);
		Tree[x].lazy = 0;
	}
}

void pushUp(int x){
	Tree[x].sum = (Tree[x<<1].sum + Tree[x<<1|1].sum) % mod;
}

void build(int left, int right, int now = 1){
	Tree[now].left = left;
	Tree[now].right = right;
	Tree[now].sum = 1;
	Tree[now].lazy = 0;
	if(left >= right){
		return;
	}
	int mid = left + (right - left) / 2;
	build(left, mid, now << 1);
	build(mid + 1, right, now << 1 | 1);
	pushUp(now);
}

void update(int uleft, int uright, ll addv, int now = 1){
	if(uleft > uright) return;
	int left = Tree[now].left, right = Tree[now].right;
	if(uleft <= left && right <= uright){
		Tree[now].upd(addv);
		return;
	}
	int mid = left + (right - left) / 2;
	pushDown(now);
	if(uleft <= mid) update(uleft, uright, addv, now << 1);
	if(uright > mid) update(uleft, uright, addv, now << 1 | 1);
	pushUp(now);
}

ll query(int qleft, int qright, int now = 1){
	if(qleft > qright) return 0ll;
	int left = Tree[now].left, right = Tree[now].right;
	if(qleft <= left && right <= qright){
		return Tree[now].sum;
	}
	int mid = left + (right - left) / 2;
	ll ret = 0;
	pushDown(now);
	if(qleft <= mid) ret = (ret + query(qleft, qright, now << 1)) % mod;
	if(qright > mid) ret = (ret + query(qleft, qright, now << 1 | 1)) % mod;
	pushUp(now);
	return ret;
}

int main(){
	while(~scanf("%s", s+1)){
		int len = strlen(s+1);
		int cnta = 0;
		for(int i = 1; i <= len; ++ i){
			cnta += s[i] == 'a';
		}
		build(1, cnta);

		int l = -1, r = 0;
		for(int i = 1, cur = 0, lasta = -1, lastb = -1; i <= len; ++ i){
			if(s[i] == 'a'){
				lasta = i;
				cur ++;
				if(l <= r){
					l = cur;
				}
			}
			if(s[i] == 'b'){
				if(lastb > lasta || cur == 0) continue;
				r = cur;
				lastb = i;
				ll addv = query(l, r);
				update(r+1, cnta, addv);
			}
		}
		printf("%lld\n", query(1, cnta));
	}
	return 0;
}