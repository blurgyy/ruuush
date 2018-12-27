#include <bits/stdc++.h>
using namespace std;
const int maxn = 110;

struct cord
{
	int x, y;
	bool side;//0 for a, 1 for b
}pt[maxn];
int T, n;

int sq(int a){
	return a*a;
}

bool three(){
	for(int i = 0; i < n; ++ i){
		for(int j = i+1; j < n; ++ j){
			for(int k = j+1; k < n; ++ k){
				int dij = sq(pt[i].x - pt[j].x) + sq(pt[i].y - pt[j].y);
				int dik = sq(pt[i].x - pt[k].x) + sq(pt[i].y - pt[k].y);
				int djk = sq(pt[j].x - pt[k].x) + sq(pt[j].y - pt[k].y);
				int len = max(dij, max(djk, dik));
				if(dij == len){
					pt[i].side = pt[j].side = 1;
				}
				else if(dik == len){
					pt[i].side = pt[k].side = 1;
				}
				else if(djk == len){
					pt[j].side = pt[k].side = 1;
				}
				return true;
			}
		}
	}
}

int prod(cord a, cord b){
	return a.x * b.y - b.x * a.y;
}

bool four(cord &a, cord &b, cord &c, cord &d){
	cord p1, p2, p3, p4;
	p1.x = b.x - a.x; p1.y = b.y - a.y;
	p2.x = c.x - b.x; p2.y = c.y - b.y;
	p3.x = d.x - c.x; p3.y = d.y - c.y;
	p4.x = a.x - d.x; p4.y = a.y - d.y;
	int ans1 = prod(p1, p2), ans2 = prod(p2, p3), ans3 = prod(p3, p4), ans4 = prod(p4, p1);
	if(ans1 > 0 && ans2 > 0 && ans3 > 0 && ans4 > 0){
		a.side = c.side = 1;
		return true;
	}
	if(ans1 < 0 && ans2 < 0 && ans3 < 0 && ans4 < 0){
		a.side = c.side = 1;
		return true;
	}
	return false;
}

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		memset(pt, 0, sizeof(pt));
		for(int i = 0; i < n; ++ i)
			scanf("%d%d", &pt[i].x, &pt[i].y);
		if(n < 3){
			printf("NO\n");
			continue;
		}
		if(n == 3){
			if(three()){
				printf("YES\n");
				for(int i = 0; i < n; ++ i)
					printf("%c", "AB"[pt[i].side]);
				printf("\n");
				continue;
			}
			printf("NO\n");
			continue;
		}
		if(n == 4){
			int perm[4];
			bool esc = false;
			for(int i = 0; i < 4; ++ i){
				perm[i] = i;
			}
			do{
				if(four(pt[perm[0]], pt[perm[1]], pt[perm[2]], pt[perm[3]])){
					esc = true;
					break;
				}
			}while(next_permutation(perm, perm + 4));
			if(esc){
				printf("YES\n");
				for(int i = 0; i < n; ++ i)
					printf("%c", "AB"[pt[i].side]);
				printf("\n");
				continue;
			}
			else printf("NO\n");
			continue;
		}
		if(n > 4){
			int perm[4];
			bool esc = false;
			for(int i = 0; i < 5; ++ i){
				for(int j = 0, k = 0; j < 5; ++ j){
                    if(j == i){
                        continue;
                    }
                    perm[k ++] = j;
                }
				do{
					if(four(pt[perm[0]], pt[perm[1]], pt[perm[2]], pt[perm[3]])){
						esc = true;
						break;
					}
				}while(next_permutation(perm, perm + 4));
				if(esc)break;
			}
			printf("YES\n");
			for(int i = 0; i < n; ++ i)
				printf("%c", "AB"[pt[i].side]);
			printf("\n");
			continue;
		}
	}
	return 0;
}

/**

3
1 1
2 2
3 3

5
1 1
1 2
0 0
2 0
2 2

*/