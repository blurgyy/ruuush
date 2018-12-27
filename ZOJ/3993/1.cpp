#include<bits/stdc++.h>
using namespace std;
const int maxn = 110;

int T, n, R, r;
int ans[maxn], p;

int sq(int a){
    return a * a;
}

struct point{
    int x, y, id;
    int dist;
    void calc(){
        dist = sq(x) + sq(y);
    }
    void print(){///for dubugging
        printf("x = %d, y = %d, id = %d, dist = %d\n", x, y, id, dist);
    }
}pt[maxn];

bool operator< (point a, point b){
    return a.dist < b.dist;
}

int main(){
    scanf("%d", &T);
    //while(~scanf("%d", &T))
    {
        while(T --){
            p = 0;
            scanf("%d%d%d", &n, &R, &r);
            for(int i = 0; i < n; ++ i){
                scanf("%d%d", &pt[i].x, &pt[i].y);
                pt[i].calc();
                pt[i].id = i + 1;
            }
            sort(pt, pt + n);
            if(r + r <= R){
                int bound = sq(R - r - r);
                if(pt[0].dist <= bound){
                    for(int i = 0; i < n && pt[i].dist <= bound; ++ i){
                        ans[p++] = pt[i].id;
                    }
                }
                else {
                    ans[p++] = pt[0].id;
                    for(int i = 1; i < n && pt[i].dist == pt[i-1].dist; ++ i){
                        ans[p++] = pt[i].id;
                    }
                }
            }
            else {
                int bound = sq(r + r - R);
                if(pt[0].dist <= bound){
                    for(int i = 0; i < n && pt[i].dist <= bound; ++ i)
                        ans[p++] = pt[i].id;
                }
                else {
                    ans[p++] = pt[0].id;
                    for(int i = 1; i < n && pt[i].dist == pt[i-1].dist; ++ i)
                        ans[p++] = pt[i].id;
                }
            }
            sort(ans, ans + p);
            printf("%d\n", p);
            for(int i = 0; i < p; ++ i)
                printf("%d%c", ans[i], " \n"[i == p-1]);
        }
    }
    return 0;
}