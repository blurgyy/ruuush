#include<bits/stdc++.h>
using namespace std;
const int maxn = 250010;
typedef long long ll;

struct node
{
	ll s, t;
	bool operator < (node a){
		return s < a.s;
	}
}rect[maxn];
int n;

int main(){
	while(~scanf("%d", &n)){
		int s, t;
		for(int i = 0; i < n; ++ i){
			scanf("%d%d", &s, &t);
			rect[i].s = min(s, t);
			rect[i].t = max(s, t);
		}
		sort(rect, rect + n);
		ll ans = 0;
		for(int i = 0; i < n; ++ i){

		}
	}
}