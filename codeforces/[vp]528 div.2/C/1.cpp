#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;
const int inf = 0x3f3f3f3f;

struct P{
    int x, y;
    bool operator< (const P &rhs){return x == rhs.x ? y < rhs.y : x < rhs.x; }
}pt[3];

bool cmp(P &lhs, P &rhs){return lhs.y == rhs.y ? lhs.x > rhs.x : lhs.y < rhs.y; }

int dist(P a, P b){return abs(a.x - b.x) + abs(a.y - b.y);}

int main(){
    while(~scanf("%d%d%d%d%d%d", &pt[0].x, &pt[0].y, &pt[1].x, &pt[1].y, &pt[2].x, &pt[2].y)){
        sort(pt, pt + 3);
        P *sml = &pt[0];
        P *mid = &pt[1];
        P *big = &pt[2];
        sort(pt, pt + 3, cmp);
        int ans = 0;
        if(mid == &pt[1]){
            ans = dist(pt[0], pt[2]) - 2;
            printf("%d\n", ans);
            for(int i = pt[0].x; i < pt[1].x; ++ i) printf("%d %d", i, pt[0].y);
            for(int i = pt[0].y; i < pt[不想写了])

        }
        else {
            if(big == &pt[2]){
                ans = dist(pt[2], pt[1]) - 1 + abs(pt[0].x - pt[1].x) - 1;
            }
            else if(sml == &pt[0]){
                ans = dist(pt[0], pt[1]) - 1 + abs(pt[3].y - pt[1].y) - 1;
            }
            else if(big == &pt[0]){
                ans = dist(pt[0], pt[2]) - 1 + abs(pt[1].x - pt[2].x) - 1;
            }
            else if(sml == &pt[2]){
                ans = dist(pt[2], pt[1]) - 1 + abs(pt[1].y - pt[0].y) - 1;
            }
        }
    }
    return 0;
}