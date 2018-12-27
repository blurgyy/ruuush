#include <bits/stdc++.h>
using namespace std;
const int maxn = 10010;

struct Node{
	int a, t;
}s[maxn];
int n;

bool operator< (Node a, Node b){
	return a.a > b.a;
}

int main(){
	while(~scanf("%d", &n)){
		for(int i = 0; i < n; ++ i){
			scanf("%d%d", &s[i].a, &s[i].t);
		}
		double dist = 0;
		double last = 0;
		for(int i = 0; i < n; ++ i){
			double add = 1LL * s[i].a * s[i].t;
			dist -= (last + last + add) * (double)s[i].t / 2.0;
			last += add;
		}
		sort(s, s + n);
		last = 0;
		for(int i = 0; i < n; ++ i){
			double add = 1LL * s[i].a * s[i].t;
			dist += (last + last + add) * (double)s[i].t / 2.0;
			last += add;
			//printf("add = %f\n", add);
		}
		printf("%.1f\n", dist);
	}
	return 0;
}