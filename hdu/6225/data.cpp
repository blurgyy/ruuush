#include<bits/stdc++.h>
using namespace std;
const int maxn = 315000;

int main(){
	freopen("in.in", "w", stdout);
	srand(time(NULL));
	printf("%d\n", maxn);
	int t = maxn;
	while(t--){
		printf("%d %d %d %d\n", rand(), rand(), rand(), rand());
	}
	return 0;
}