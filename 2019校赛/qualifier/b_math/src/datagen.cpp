#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;

int T = 100;
bool vis[maxn];

int main(){
	memset(vis, 0, sizeof(vis));
	srand(time(NULL));
	printf("%d\n", T);
	while(T --){
		int x = rand() % 1000 + 1;
		while(vis[x] == true){
			x = rand() % 1000 + 1;
		}
		vis[x] = true;
		printf("%d\n", x);
	}
	return 0;
}

