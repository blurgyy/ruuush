/////////...

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 300010;
const ll inf = 0x3f3f3f3f3f3f3f3f;

int n;
ll w[maxn];
// ll pathval[maxn];
struct Node{
    int to;
    int ne;
    int w;
    ll pathval;
    ll maxx;
}node[maxn<<1];
int head[maxn];
int top;
ll ans;

void add(int from, int to, int w){
    node[top].to = to;
    node[top].w = w;
    node[top].ne = head[from];
    head[from] = top;
    top ++;
}

void dfs(int now = 1, int prv = -1){
    for(int i = head[now]; i != -1; i = node[i].ne){
        int nxt = node[i].to;
        if(nxt == prv) continue;
        // pathval[nxt] = pathval[now] + w[now] - node[i].w;
        node[nxt].pathval = node[now].pathval + w[now] + node[i].w;
        node[now].maxx = max(node[now].maxx, node[nxt].pathval + w[nxt]);
        dfs(nxt, now);
    }
    ans = max(ans, node[now].maxx);
}

void ini(){
    top = ans = 0;
    memset(node, -1, sizeof(node));
    memset(head, -1, sizeof(head));
    // memset(pathval, 0, sizeof(pathval));
}
void init(){
    ini();
}

int main(){
    while(~scanf("%d", &n)){
        init();
        for(int i = 1; i <= n; ++ i){
            scanf("%lld", w + i);
        }
        for(int i = 1, u, v, c; i < n; ++ i){
            scanf("%d%d%d", &u, &v, &c);
            add(u, v, c);
            add(v, u, c);
        }
        node[1].pathval = 0;
        dfs();
        printf("%lld\n", ans);
    }
    return 0;
}