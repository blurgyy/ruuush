#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
const int maxn = 20;
const int inf = 0x3f3f3f3f;

int T, n, t;
int add[maxn], sub[maxn];
bool vis[4010];
int pa, ps;

pii bfs(){
    queue<pii> que; ///pair<current_time, current_button_press_counting>
    que.push(make_pair(0, 0));
    vis[0] = true;
    int minx = inf, mincnt = inf;
    while(!que.empty()){
        pii now = que.front();
        que.pop();

        //printf("(%d)now time = %d\n", now.second, now.first);

        if(now.first == t){
            return make_pair(now.second, 0);
        }
        if(now.first > t && now.first < minx){
            minx = now.first;
            mincnt = now.second;
        }
        if(now.first > t && now.first == minx){
            mincnt = min(mincnt, now.second);
        }
        for(int i = 0; i < pa; ++ i){
            int nxt = now.first + add[i];
            if(nxt > 3600){
                nxt = 3600;
            }
            if(!vis[nxt]){
                que.push(make_pair(nxt, now.second + 1));
                vis[nxt] = true;
            }
        }
        for(int i = 0; i < ps; ++ i){
            int nxt = now.first - sub[i];
            if(nxt < 0){
                continue;
                //nxt = 0;
            }
            if(!vis[nxt]){
                que.push(make_pair(nxt, now.second + 1));
                vis[nxt] = true;
            }
        }
    }
    return make_pair(mincnt, minx - t);
}

void init(){
    pa = ps = 0;
    memset(vis, false, sizeof(vis));
}

int main(){
    //freopen("in.in", "r", stdin);
    scanf("%d", &T);
    while(T --){
        init();
        scanf("%d%d", &n, &t);
        while(n --){
            int b;
            scanf("%d", &b);
            if(b > 0){
                add[pa ++] = b;
            }
            if(b < 0){
                sub[ps ++] = -b;
            }
        }
        pii ans = bfs();
        printf("%d %d\n", ans.first, ans.second);
    }
    return 0;
}