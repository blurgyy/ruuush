#include<bits/stdc++.h>
using namespace std;
const int maxn = 20010;
const char out[2][20] = {"impossible", "possible"};
typedef long long ll;

int N;
ll a[maxn];

int main(){
	while(~scanf("%d", &N)){
		for(int i = 0; i < N; ++ i)
			scanf("%lld", a + i);
		sort(a, a + N);
		bool ans = false;
		for(int i = 2; i < N; ++ i){
			if(a[i-2] + a[i-1] > a[i]){
				ans = true;
				break;
			}
		}
		printf("%s\n", out[ans]);
	}
	return 0;
}