#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll p1 = 1e9 + 7;
const ll p2 = 1e9 + 9;
const ll p3 = 1004535809;
const ll zhanghang = 998244353;
const int maxn = 110;

char s[maxn];
int p;
ll h, rec[200010];

int main(){
	int T = 20000;
	p = 0;
	while(T--){
		scanf("%s", s);
		h = 0;
		for(int i = 0; i < 100; ++ i){
			h = (h * p1 + s[i] * p2 + p3) % zhanghang;
		}
		rec[p++] = h;
	}
	sort(rec, rec + p);
	int ans = unique(rec, rec + p) - rec;
	printf("%d\n", ans);
}