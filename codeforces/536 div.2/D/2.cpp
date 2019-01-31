#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int maxn = 100010;

int n, m;
vector<int> E[maxn];
int fa[maxn];
bool pushed[maxn];

int find(int x){return x == fa[x] ? x : fa[x] = find(fa[x]);}
bool same(int x, int y){return find(x) == find(y);}
void unite(int x, int y){
    int t1 = find(x), t2 = find(y);
    if(t1 == t2) return;
    fa[t1] = t2;
}

void init(){
    for(int i = 0; i < maxn; ++ i) E[i].clear();
    for(int i = 0; i < maxn; ++ i) fa[i] = i;
    memset(pushed, false, sizeof(pushed));
}

int main(){
    // freopen("in.in", "r", stdin);
    while(~scanf("%d%d", &n, &m)){
        init();
        for(int i = 0, u, v; i < m; ++ i){
            scanf("%d%d", &u, &v);
            E[u].push_back(v);
            E[v].push_back(u);
        }
        // priority_queue<pii> que;
        priority_queue<int> que;
        que.push(-1);
        pushed[1] = true;
        while(!que.empty()){
            int now = -que.top();
            printf("%d ", now);
            que.pop();
            for(int i = 0; i < E[now].size(); ++ i){
                if(pushed[E[now][i]]) continue;
                // printf("pushed (%d)\n", E[now][i]);
                que.push(-E[now][i]);
                pushed[E[now][i]] = true;
            }
            unite(1, -que.top());
        }
        printf("\n");
    }
    return 0;
}