#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define ll long long
using namespace std;
const int maxn = 20;

ll ans[maxn] = {0, 1, 4, 27, 256, 3125, 46656, 823543, 16777216, 387420489, 10000000000, 285311670611, 8916100448256, 302875106592253, 11112006825558016, 437893890380859375};
ll n;

int bs(int left, int right, ll e){
	if(left >= right)return right;
	int mid = (left + right)>>1;
	if(e < ans[mid])return bs(left, mid, e);
	else return bs(mid+1, right, e);
}

int main(){
	while(~scanf("%lld", &n)){
		if(437893890380859375 <= n)printf("15\n");
		else printf("%d\n", bs(1, 15, n) - 1);
	}
	return 0;
}