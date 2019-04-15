#include <bits/stdc++.h>
using namespace std;
const int maxn = 10010;

int T, n, m;
char hor[maxn], ver[maxn];

int main(){
	scanf("%d", &T);
	while(T --){
		scanf("%d%d%s%s", &n, &m, hor, ver);
		char top = hor[0];
		char bot = hor[n-1];
		char lft = ver[0];
		char rgt = ver[m-1];
		int ans = (top == bot) + (lft == rgt);
		if(top == 'L' && lft == 'U' && bot == 'R' && rgt == 'D'){
			ans += 2;
		}
		else if(top == 'R' && lft == 'D' && bot == 'L' && rgt == 'U'){
			ans += 2;
		}
		printf("%d\n", ans);
	}
	return 0;
}
