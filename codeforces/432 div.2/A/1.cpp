#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n, k, t, ans;

int main(){
	while(~scanf("%d%d%d", &n, &k, &t)){
		if(t <= k)
			ans = t;
		else if(t >= n)
			ans = k - t + n;
		else ans = k;
		printf("%d\n", ans);
	}
	return 0;
}