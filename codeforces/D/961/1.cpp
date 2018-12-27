#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 100010;

int n;
struct Point{
    ll x, y;
}pt[maxn];

bool check(int a, int b, int c, int d){
    bool vis[maxn] = {false};
    for(int i = 0; i < maxn; ++ i){
        if((pt[i].y - pt[a].y) * (pt[b].x - pt[a].x) == (pt[b].y - pt[a].y) * (pt[i].x - pt[a].x))
            vis[i] = true;
        else if((pt[i].y - pt[c].y) * (pt[d].x - pt[c].x) == (pt[d].y - pt[c].y) * (pt[i].x - pt[c].x))
            vis[i] = true;
    }
    for(int i = 0; i < n; ++ i)
        if(!vis[i])return false;
    return true;
}

int main(){
    while(~scanf("%d", &n)){
        bool ans = false;
        for(int i = 0; i < n; ++ i)
            scanf("%I64d%I64d", &pt[i].x, &pt[i].y);
        if(n < 5){
            printf("YES\n");
            continue;
        }
        int p1 = -1, p2 = -1;
        for(int i = 2; i < n; ++ i)
            if((pt[i].y - pt[0].y) * (pt[1].x - pt[0].x) != (pt[1].y - pt[0].y) * (pt[i].x - pt[0].x)){
                p1 = i;
                break;
            }
        if(p1 == -1){
            printf("YES\n");
            continue;
        }
        bool mark[3] = {false};
        for(int i = 2; i < n; ++ i){
            if(i == p1)continue;
            if((pt[i].y - pt[0].y) * (pt[1].x - pt[0].x) != (pt[1].y - pt[0].y) * (pt[i].x - pt[0].x))
                if((pt[i].y - pt[0].y) * (pt[p1].x - pt[0].x) != (pt[p1].y - pt[0].y) * (pt[i].x - pt[0].x))
                    if((pt[i].y - pt[p1].y) * (pt[1].x - pt[p1].x) != (pt[1].y - pt[p1].y) * (pt[i].x - pt[p1].x)){
                        p2 = i;
                        break;
                    }
                    else {
                        mark[2] = true;
                    }
                else {
                    mark[1] = true;
                }
            else {
                mark[0] = true;
            }
        }
        if(p2 == -1){
            if(mark[0] == mark[1] && mark[1] == mark[2] && mark[2] == true){
                printf("NO\n");
            }
            else printf("YES\n");
            continue;
        }
        //printf("p1 = %d, p2 = %d\n", p1, p2);
        if(check(0, 1, p1, p2) || check(0, p1, 1, p2) || check(0, p2, 1, p1))ans = true;
        if(ans)printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}

/**

6
-1 -1
-1 -2
-1 -3
0 0
65536 65536
65536 131072

10
315 202
315 203
315 204
-138 -298
-136 -295
-134 -292
-132 -289
-130 -286
-128 -283
-126 -280

5
0 0
0 1
1 1
1 -1
2 2

5
0 0
1 0
2 1
1 1
2 3


*/