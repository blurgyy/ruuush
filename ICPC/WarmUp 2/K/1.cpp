#include<bits/stdc++.h>
using namespace std;
const int maxn = 110;

struct date
{
	int index;
	int y, m, d;
	int operator- (date a){
		int ans = y - a.y;
		if(m < a.m)return ans-1;
		if(m == a.m){
			if(d < a.d)return ans-1;
		}
		return ans;
	}
}death, birth[maxn];
int n;

bool cmp(date b, date a){
    if(b.y == a.y){
        if(b.m == a.m)
            return b.d < a.d;
        return b.m < a.m;
    }
    return b.y < a.y;
}

int main(){
	while(~scanf("%d%d%d", &death.d, &death.m, &death.y)){
        memset(birth, 0, sizeof(birth));
		scanf("%d", &n);
		for(int i = 1; i <= n; ++ i){
			scanf("%d%d%d", &birth[i].d, &birth[i].m, &birth[i].y);
			birth[i].index = i;
		}
		sort(birth + 1, birth + n + 1, cmp);
		/*for(int i = n; i >= 1; -- i)
			birth[i].index = i;*/
        /*for(int i = 1; i <= n; ++i){
            printf("%d %d %d\n", birth[i].d, birth[i].m, birth[i].y);
        }*/
		int ans = -1;
		for(int i = 1; i <= n; ++ i){
			if(death - birth[i] >= 18)
				ans = birth[i].index;
		}
		printf("%d\n", ans);
	}
	return 0;
}

/**

22 10 2016
7
1 4 2013
17 12 2004
3 9 2000
28 2 1999
23 10 1998
21 10 1998
22 7 1995

*/
