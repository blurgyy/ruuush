#include <bits/stdc++.h>
#define LL long long
using namespace std;

const int N = 100010;

LL n, m;
LL ma[N];

bool Chekc(LL x)
{
	LL num;
	LL sum;

	sum = 0;
	num = 0;
	// cout << "ne" << endl;
	for(int i = 0; i < n; i ++){
		if(sum + ma[i] > x){
			num ++;
			// printf("%d\n", sum);
			sum = ma[i];
		}
		else{
			sum += ma[i];
		}
	}
	num ++;
	if(num <= m){
		return true;
	}
	else{
		return false;
	}
}

int main(int argc, char const *argv[])
{
    int ncase;
	LL l;
	LL r;
	LL ans;

    scanf("%d", &ncase);
	while(ncase --){
	    scanf("%lld%lld", &n, &m);
	    m ++;
        l = -1;
        r = 0;
		for(int i = 0; i < n; i ++){
            // printf("%d\n", i);
			scanf("%lld", &ma[i]);
            l = max(l, ma[i]);
            r += ma[i];
		}
		while(l <= r){
			LL mid;

			mid = l + ((r - l) >> 1);
			if(Chekc(mid)){
				ans = mid;
				r = mid - 1;
			}
			else{
				l = mid + 1;
			}
		}
		printf("%lld\n", ans);
	}

	return 0;
}
