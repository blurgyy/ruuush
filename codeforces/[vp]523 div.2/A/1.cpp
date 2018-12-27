#include <bits/stdc++.h>
using namespace std;

int n, s;

int main(){
	while(~scanf("%d%d", &n, &s)){
		printf("%d\n", s/n + !!(s%n));
	}
	return 0;
}