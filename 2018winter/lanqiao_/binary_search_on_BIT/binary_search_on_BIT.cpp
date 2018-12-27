#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int bit[maxn];
int lowbit(int x){return x & -x;}
int sum(int x){
	int ans = 0;
	while(x){
		ans += bit[x];
		x -= lowbit(x);
	}
	return ans;
}
int add(int x, int v){
	while(x <= n){
		bit[x] += v;
		x += lowbit(x);
	}
}
void init(){
	memset(bit, 0, sizeof(bit));
}

int main(){
	
}