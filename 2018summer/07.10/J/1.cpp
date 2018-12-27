/// I don't want to debug for this one so I just wrote 2.cpp and got ACCEPTED
/// SIMULATION!

#include <bits/stdc++.h>
//#include <map>
//#include <cstdio>
//#include <cstring>
//#include <algorithm>
using namespace std;
const int maxn = 10010;
const int inf = 0x3f3f3f3f;
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};

int T;
char s[maxn];
struct cord{
    int x, y;
    cord(int _x = 0, int _y = 0){x = _x, y = _y;}
};
map<cord, bool> rec;

bool operator< (cord a, cord b){
    if(a.x == b.x)return a.y < b.y;
    return a.x < b.x;
}

int main(){
    //freopen("J.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    //freopen("tmp.out", "w", stdout);
    scanf("%d", &T);
    printf("%d\n", T);
    while(T --){
        scanf("%s", s);
        int len = strlen(s);
        int dir = 0;
        rec.clear();
        cord now(0, 0);
        for(int i = 0; i < len; ++ i){
            if(s[i] == 'F'){
            }
            else if(s[i] == 'R'){
                dir = (dir + 3) % 4;
            }
            else if(s[i] == 'L'){
                dir = (dir + 1) % 4;
            }
            else {
                dir = (dir + 2) % 4;
            }
            rec[now] = true;
            now.x += dx[dir];
            now.y += dy[dir];
        }
        int miny = inf, maxy = -inf;
        int maxx = -inf;
        for(auto i = rec.begin(); i != rec.end(); ++ i){
            maxx = max(maxx, i->first.x);
            miny = min(miny, i->first.y);
            maxy = max(maxy, i->first.y);
            //printf("%d %d\n", i->first.x, i->first.y);
        }
        printf("%d %d\n", maxy - miny + 3, maxx + 2);
        for(int i = 0; i <= maxx + 1; ++ i)
            printf("#");
        printf("\n");
        for(int y = maxy; y >= miny; -- y){
            for(int x = 0; x <= maxx + 1; ++ x){
                cord th(x, y);
                if(rec[th])printf(".");
                else printf("#");
            }
            printf("\n");
        }
        for(int i = 0; i <= maxx + 1; ++ i)
            printf("#");
        printf("\n");
    }
    return 0;
}