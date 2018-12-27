#include<bits/stdc++.h>
using namespace std;

struct node 
{
	int cnt, index;
}value[100];
int n, m;

bool operator< (node a, node b){
	return a.cnt < b.cnt;
}

int main(){
	while(~scanf("%d%d", &n, &m)){
		memset(value, 0, sizeof(value));
		for(int i = 0; i < 100; ++ i)
			value[i].index = i;
		for(int i = 1; i <= n; ++ i){
			for(int j = 1; j <= m; ++ j){
				++ value[i+j].cnt;
			}
		}
		sort(value + 1, value + n + m + 1);
		int max = value[n+m].cnt;
		int out[100], p = 0;
		for(int i = n+m; i >= 0; -- i){
			if(value[i].cnt == max)out[p++] = value[i].index;
			else break;
		}
		sort(out, out + p);
		for(int i = 0; i < p; ++ i)
			printf("%d\n", out[i]);
	}
	return 0;
}