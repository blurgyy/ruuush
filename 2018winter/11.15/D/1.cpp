///D
#include <bits/stdc++.h>
#define LL long long
using namespace std;

const int N = 300050;
const int MOD = 1e9 + 7;

char ma[N];

LL Quick_mod(LL a, LL b)
{
	LL ans;

	ans = 1;
	while(b){
		if(b & 1){
			ans = (ans * a) % MOD;
		}
		a = a * a % MOD;
	}

	return ans % MOD;
}

int main(int argc, char const *argv[])
{
	int n, m;
	int cnt;
	LL ans;

	while(scanf("%d%d", &n, &m) == 2){
		cnt = 0;
		// cout << n << m << endl;a
		scanf("%s", ma);
		// cin >> ma;
		// cout << 666 << endl;
		printf("%s\n", ma);
		// cout << 777 << endl;
		for(int i = 0; i < n; i ++){
            printf("%c", ma[ia]);
			cnt = ((cnt * 10) % m + ma[i] - '0') % m;
			if(!cnt){
				ans ++;
			}
		}
		if(cnt){
			printf("0\n");
		}
		else{
			printf("%lld\n", Quick_mod(1ll * 2, ans - 1));
		}
	}


	return 0;
}
