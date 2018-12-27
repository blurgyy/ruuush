#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100010;

int n, m;
struct Node{
    int id;
    int to;
    int nxt;
}node[maxn];
int head[maxn];
int top;
int deg[maxn];
int fa[maxn];

int find(int x){
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void unite(int x, int y){
    int t1 = find(x), t2 = find(y);
    if(t1 == t2)return;
    fa[t1] = t2;
}

bool same(int x, int y){
    return find(x) == find(y);
}

void add(int from, int to, int id){
    node[top].id = id;
    node[top].to = to;
    node[top].nxt = head[from];
    head[from] = top;
    top ++;
}
/*
for(int i = head[u]; i != -1; i = node[i].nxt){
    int nxt = node[i].to;
  /// 遍历
}*/

void ini(){
  top = 0;
  memset(head, -1, sizeof(head));
  memset(deg, 0, sizeof(deg));
  for(int i = 0; i < maxn; ++ i)fa[i] = i;
}

int main(){
    while(~scanf("%d%d", &n, &m)){
        ini();
        int from, to;
        for(int i = 1; i <= m; ++ i){
            scanf("%d%d", &from, &to);
            add(from, to, i);
            add(to, from, -i);
            deg[from] ++;
            deg[to] ++;
            unite(from, to);
        }
        int p = 0;
        for(int i = 1; i <= n; ++ i){
            if(deg[i] & 1){
                p ++;
            }
        }
        p = max(p / 2, 1);
        printf("%d\n", p);
        for(int i = 1; i <= n; ++ i){
            fa[i] = find(i);
        }
        sort(fa + 1, fa + 1 + n);
        int tot = unique(fa + 1, fa + 1 + n) - fa - 1;
        //printf("tot = %d\n", tot);
        ///i want to play1v
    }
    return 0;
}