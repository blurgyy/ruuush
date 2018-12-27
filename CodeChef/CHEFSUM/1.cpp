#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int T, n, mini, pos;
int a[maxn];

int main(){
	scanf("%d", &T);
	while(T--){
		mini = 0x3f3f3f3f;
		pos = 0;
		scanf("%d", &n);
		for(int i = 0; i < n; ++ i){
			scanf("%d", a + i);
			if(a[i] < mini){
				mini = a[i];
				pos = i;
			}
		}
		printf("%d\n", pos+1);
	}
	return 0;
}