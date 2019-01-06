#include <cstdio>
#include <cstring>
typedef long long ll;
const int maxn = 200010;
const int inf = 0x3f3f3f3f;

int n;
int a[maxn];
int s[maxn];
int par[maxn];
bool indeg[maxn];

template<class t>
t max(t a, t b){return a > b ? a : b;}
template<class t>
t min(t a, t b){return a < b ? a : b;}

struct Node{
    int to;
    int ne;
};
Node node[maxn<<2];
int head[maxn];
int top;

void add(int from, int to){
    node[top].to = to;
    node[top].ne = head[from];
    head[from] = top;
    top ++;
}

// for(int i = head[u]; i != -1; i = node[i].ne){
//   /// 遍历
// }

void ini(){
    top = 0;
    memset(head, -1, sizeof(head));
}

bool check(){
    for(int i = 1; i <= n; ++ i){
        if(indeg[i] == false){
            // printf("is leaf: %d\n", i);
            int now = i;
            int val = max(s[now], s[par[now]]);
            while(now != -1){
                if(s[now] == -1) {
                    now = par[now];
                    continue;
                }
                if(val < s[now]) return false;
                val = s[now];
                now = par[now];
            }
        }
    }
    return true;
}

void dfs(int now = 1, ll pref = 0){
    int min_son = inf;
    for(int i = head[now]; i != -1; i = node[i].ne){
        int nxt = node[i].to;
        min_son = min(min_son, s[nxt]);
    }
    if(s[now] == -1){
        s[now] = min_son;
        if(s[now] == inf) s[now] = pref;
    }
    a[now] = s[now] - pref;
    for(int i = head[now]; i != -1; i = node[i].ne){
        int nxt = node[i].to;
        dfs(nxt, pref + a[now]);
    }
}

ll calc(){
    dfs();
    ll ret = 0;
    for(int i = 1; i <= n; ++ i){
        ret += a[i];
        // printf("a[%d] = %d\n", i, a[i]);
    }
    return ret;
}

void init(){
    ini();
    memset(indeg, false, sizeof(indeg));
    memset(par, 0, sizeof(par));
    memset(a, 0, sizeof(a));
    par[1] = -1;
}

int main(){
    while(~scanf("%d", &n)){
        init();
        for(int i = 2; i <= n; ++ i){
            scanf("%d", par + i);
            indeg[par[i]] = true;
            add(par[i], i);
        }
        for(int i = 1; i <= n; ++ i){
            scanf("%d", s + i);
        }
        if(check()){
            printf("%I64d\n", calc());
        }
        else {
            printf("-1\n");
        }
    }
    return 0;
}