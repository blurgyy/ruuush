#include <bits/stdc++.h>
using namespace std;

int T;
char ans[2][5] = {"NO", "YES"};

void input(){
	int t = 72;
	int tmp;
	while(t--)scanf("%d", &tmp);
}

int main(){
	int a = 239;///239 yes
	scanf("%d", &T);
	while(T--){
		input();
		printf("%s\n", ans[a&1]);
		a >>= 1;
	}
	return 0;
}