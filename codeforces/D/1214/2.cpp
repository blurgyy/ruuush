#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int maxn = 1000010;
int dx[] = {0, 1};
int dy[] = {1, 0};

int n, m;
char s[maxn];
int ds[maxn], de[maxn];
bool vis[maxn];
bool mask[maxn];
int cnt[maxn];

int id(pii now){return m*(now.first-1) + now.second;}
bool inrange(pii co){
    int x = co.first, y = co.second;
    return x > 0 && y > 0 && x <= n && y <= m;
}
char& maze(pii x){return s[id(x)];}

void dfs(pii now, int dir, int dist = 0){
    // printf("(%d,%d)\n", now.first, now.second);
    if(!inrange(now) || vis[id(now)] || maze(now) == '#') return;
    vis[id(now)] = true;
    if(dir == 1){
        ds[id(now)] = dist;
    }
    else if(dir == -1){
        de[id(now)] = dist;
    }
    int x = now.first;
    int y = now.second;
    for(int d = 0; d < 2; ++ d){
        int nx = x + dir*dx[d];
        int ny = y + dir*dy[d];
        // printf("(%d,%d) -> (%d,%d)\n", x, y, nx, ny);
        pii nxt = make_pair(nx, ny);
        dfs(nxt, dir, dist+1);
    }
}

int main(){
    while(~scanf("%d%d", &n, &m)){
        int area = n * m;
        for(int i = 1; i <= area; i += m){
            scanf("%s", s + i);
        }
        pii start = make_pair(1, 1);
        pii end = make_pair(n, m);
        // memset(ds, 0, sizeof(ds));
        // memset(de, 0, sizeof(de));
        // memset(cnt, 0, sizeof(cnt));
        // memset(vis, false, sizeof(vis));
        dfs(start, 1);
        memset(vis, false, sizeof(vis));
        dfs(end, -1);
        // memset(mask, false, sizeof(mask));
        for(int i = 1; i <= area; ++ i){
            mask[i] = (ds[i] > 0 && de[i] > 0);
            if(mask[i] && i != 1){
                cnt[ds[i]] ++;
            }
        }
        int ans = 0;
        for(int i = 1; i <= area; ++ i){
            if(mask[i]){
                ans = 2;
                if(cnt[ds[i]] == 1){
                    ans = 1;
                    break;
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
