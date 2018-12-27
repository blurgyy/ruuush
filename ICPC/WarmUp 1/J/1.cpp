#include<bits/stdc++.h>
using namespace std;

int now, after;

int main(){
	while(~scanf("%d%d", &now, &after)){
		int a = after - now;
		int b = min(now, after) + 360 - max(now, after);
		if(abs(a) < abs(b))
			printf("%d\n", a);
		else if(now < after)printf("%d\n", abs(b) == 180 ? 180 : -b);
		else printf("%d\n", abs(b) == 180 ? 180 : b);
	}
	return 0;
}