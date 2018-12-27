#include<bits/stdc++.h>
using namespace std;
const int maxn = 300010;
typedef long long ll;

struct node
{
	ll price;
	int pos;
}share[maxn];
int N;
ll ans;

bool operator < (node a, node b){
	return a.price < b.price;
}

int main(){
	while(~scanf("%d", &N)){
		//memset(share, 0x3f, sizeof(share));
		for(int i = 0; i < N; ++ i){
			scanf("%d", &share[i].price);
			share[i].pos = i;
			printf("share[%d].pos = %d\n", i, share[i].pos);
		}
		sort(share, share + N);
		for(int i = 0; i < N; ++ i)
			printf("price = %lld share[%d].pos = %d\n", share[i].price, i, share[i].pos);
		printf("\n");
		for(int i = 0; i <= N/2; ++ i){
			if(share[i].price < share[N-i-1].price && share[i].pos < share[N-i-1].pos)
				ans += share[N-1-i].price - share[i].price;
		}
		printf("%I64d\n", ans);
	}
	return 0;
}

/**

9
10 5 4 7 9 12 6 2 10

*/