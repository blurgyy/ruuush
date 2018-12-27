#include<bits/stdc++.h>
using namespace std;
const int maxn = 50010;

int T, n, a[maxn];

int lowbit(int num){
	int level = 0;
	int time = 30;
	while(time--){
		if(num&1){
			return level;
		}
		num >>= 1;
		++ level;
	}
}

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		for(int i = 0; i < n; ++ i)
			scanf("%d", a + i);
		
	}
	return 0;
}