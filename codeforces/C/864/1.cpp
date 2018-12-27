#include<bits/stdc++.h>
using namespace std;
const int maxn = 10010;

int a, b, f, k, ans;
int fuelstation[maxn], pos;

int bs(int left, int right, int e){
	if(left >= right)return right;
	int mid = (left + right)>>1;
	if(fuelstation[mid] >= e)return bs(left, mid, e);
	return bs(mid+1, right, e);
}

int main(){
	while(~scanf("%d%d%d%d", &a, &b, &f, &k)){
		memset(fuelstation, 0, sizeof(fuelstation));
		ans = pos = 0;
		if(b < f || b < 2*(a-f) || b < 2*f){
			printf("-1\n");
			continue;
		}
		for(int i = 1; ; i += 2){
			fuelstation[i-1] = (i - 1) * a - f;
			if(i >= k + 1){
				pos = i;
				break;
			}
			fuelstation[i] = (i - 1) * a + f;
		}
		fuelstation[0] = 0;
		int now = 0, prev;
		while(now < pos-1){
			prev = now;
			now = bs(prev, pos, b);
			printf("prev = %d, now = %d\n", fuelstation[prev], fuelstation[now]);
			if(fuelstation[now] == b)
				++ ans;
			else{
				now -= 1;
				++ ans;
			}
			for(int i = now+1; i < pos; ++ i)
				fuelstation[i] -= fuelstation[now];
			fuelstation[now] = 0;
		}
		printf("ans = %d\n");
	}
	return 0;
}