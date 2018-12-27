#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 110;

int n;
int num[maxn];

bool check_prime(int x){
	if(!(x % 2))return false;
	int top = sqrt(x);
	for(int i = 3; i <= top; ++ i)
		if(!(x % i))return false;
	return true;
}

int divide(int x){
	int ans = 0, p = 2;
	while(x > 1){
		if(check_prime(p) && !(x%p)){
			x /= p;
			++ ans;
		}
		++ p;
	}
	return ans;
}

int main(){
	while(~scanf("%d", &n)){
		for(int i = 0; i < n; ++ i)
			scanf("%d", num + i);
		for(int i = 0; i < n; ++ i)
			num[i] = divide(num[i]);
		int ans = 0;
		for(int i = 0; i < n; ++ i)
			ans ^= num[i];
		if(ans)printf("Arpa\n");
		else printf("Mojtaba\n");
	}
	return 0;
}