#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1000010;

#define maxn 1000010
#define sigma 26
struct ACA{
    int size, root,
        nxt[maxn][sigma],
        fail[maxn],
        cnt[maxn], depth[maxn];
    ll ans[maxn];
    ACA(){init();}
    void init(){
        size = 0;
        root = new_node(0);
    }
    int new_node(int dep = 0){
        memset(nxt[size], -1, sizeof(nxt[size]));
        fail[size] = 0;
        cnt[size] = 0;
        depth[size] = dep;
        ans[size] = 0;
        return size ++;
    }
    int index(char ch){return ch - 'a';}
    void insert(char *s){
        int now = root;
        int dep = 1;
        while(*s){
            int ch = index(*s);
            if(nxt[now][ch] == -1){
                nxt[now][ch] = new_node(dep);
            }
            now = nxt[now][ch];
            cnt[now] ++;
            ++ s;
            ++ dep;
        }
    }
    void build(){
        queue<int> que;
        fail[root] = root;
        for(int i = 0; i < sigma; ++ i){
            if(nxt[root][i] == -1) nxt[root][i] = root;
            else {
                que.push(nxt[root][i]);
                fail[nxt[root][i]] = root;
            }
        }
        while(!que.empty()){
            int now = que.front();
            que.pop();
            for(int i = 0; i < sigma; ++ i){
                if(nxt[now][i] == -1) nxt[now][i] = nxt[fail[now]][i];
                else {
                    que.push(nxt[now][i]);
                    fail[nxt[now][i]] = nxt[fail[now]][i];
                    // printf("fail[nxt[%d][%d]] = nxt[fail[%d]][%d]\n", now, i, now, i);
                    // printf("fail[%d] = %d\n", nxt[now][i], nxt[fail[now]][i]);
                }
            }
        }
    }
    ll solve(){
        ll ret = 0;
        queue<int> que;
        bool vis[maxn];
        memset(vis, false, sizeof(vis));
        for(int i = 0; i < sigma; ++ i){
            if(nxt[root][i] > 0){
                que.push(nxt[root][i]);
                vis[nxt[root][i]] = true;
            }
        }
        while(!que.empty()){
            int now = que.front();
            que.pop();
            ans[now] = 1ll * depth[fail[now]] * cnt[fail[now]] + ans[fail[now]];
            printf("ans[%d] = %lld\n", now, ans[now]);
            for(int i = 0; i < sigma; ++ i){
                if(nxt[now][i] > 0 && vis[nxt[now][i]] == false){
                    que.push(nxt[now][i]);
                    vis[nxt[now][i]] = true;
                }
            }
            ret += 1ll * cnt[now] * ans[now];
        }
        for(int i = 1; i < size; ++ i){
            ret += 1ll * cnt[i] * cnt[i];
        }
        return ret;
    }

    void check(){
        for(int now = 0; now < size; ++ now){
            printf("now = %d,\tfail[%d] = %d,\tcnt[%d] = %d\tdepth[%d] = %d\n", now, now, fail[now], now, cnt[now], now, depth[now]);
        }
    }
}x;
#undef maxn
#undef sigma
int T, n;
char s[maxn];

int main(){
    // scanf("%d", &T);
    // while(T --){
    //     scanf("%d", &n);
    while(~scanf("%d", &n)){
        x.init();
        while(n --){
            scanf("%s", s);
            x.insert(s);
        }
        x.build();
        // x.check();
        printf("%lld\n", x.solve());
    }
    return 0;
}
