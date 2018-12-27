#include<bits/stdc++.h>
using namespace std;

struct cord
{
	int x, y;
}a, b, s, e;
int w, h;

int main(){
	while(~scanf("%d%d%d%d%d%d", &w, &h, &a.x, &a.y, &b.x, &b.y)){
		if(a.x == b.x){
			s.y = a.y;
			e.y = b.y;
			s.x = 0;
			e.x = w;
		}
		else{
			s.x = a.x;
			e.x = b.x;
			s.y = 0;
			e.y = h;
		}
		printf("%d %d %d %d\n", s.x, s.y, e.x, e.y);
	}
	return 0;
}