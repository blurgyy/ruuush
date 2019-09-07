#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int maxn = 1000010;
int dx[] = {0, 1};
int dy[] = {1, 0};

int n, m;
char s[maxn];
int fa[maxn];

void init(){for(int i = 0; i < maxn; ++ i) fa[i] = i;}
int find(int x){return fa[x] == x ? x : find(fa[x]);}
void unite(int x, int y){
    int f1 = find(x), f2 = find(y);
    if(f1 == f2) return;
    fa[f1] = f2;
}
bool same(int x, int y){return find(x) == find(y);}

int id(int x, int y){return m * (x-1) + y;}
char& maze(int x, int y){return s[id(x, y)];}
char& maze(pii x){return maze(x.first, x.second);}
bool inrange(int x, int y){return x > 0 && y > 0 && x <= n && y <= m; }
bool inrange(pii x){return inrange(x.first, x.second);}
bool check(int x = -1, int y = -1){
    char tmp;
    if(inrange(x, y)){
        tmp = maze(x, y);
        maze(x, y) = '#';
    }
    init();
    queue<pii> que;
    pii now = make_pair(1, 1);
    que.push(now);
    while(que.size()){
        if(same(id(1,1), id(n,m))){
            break;
        }
        now = que.front();
        que.pop();
        if(maze(now) == '#'){
            continue;
        }
        int x = now.first, y = now.second;
        for(int d = 0; d < 2; ++ d){
            int nx = x + dx[d];
            int ny = y + dy[d];
            pii nxt = make_pair(nx, ny);
            if(inrange(nxt) && maze(nxt) != '#'){
                unite(id(x,y), id(nx,ny));
                que.push(nxt);
            }
        }
    }
    if(inrange(x, y)){
        maze(x, y) = tmp;
    }
    return same(id(1, 1), id(n, m));
}

int main(){
    while(~scanf("%d%d", &n, &m)){
        int area = n * m;
        for(int i = 1; i <= area; i += m){
            scanf("%s", s+i);
        }
        bool conn = check();
        if(conn){
            if(inrange(2, 1) && check(2, 1) == false || inrange(1, 2) && check(1, 2) == false){
                printf("1\n");
                continue;
            }
            int ans = 0;
            if(inrange(n-1, m) && maze(n-1, m) == '.'){
                check();
                if(same(id(n-1,m), id(1,1))){
                    if(check(n-1, m)){
                        ++ ans;
                    }
                    else {
                        printf("1\n");
                        continue;
                    }
                }
            }
            if(inrange(n, m-1) && maze(n, m-1) == '.'){
                if(same(id(n,m-1), id(1,1))){
                    if(check(n, m-1)){
                        ++ ans;
                    }
                    else {
                        printf("1\n");
                        continue;
                    }
                }
            }
            printf("%d\n", ans);
        }
        else {
            printf("0\n");
        }
    }
    return 0;
}

