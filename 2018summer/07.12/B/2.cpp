#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1010;

struct Node{
    int to, nxt;
    int ind;
}node[maxn];
int n;
int head[maxn], top;
bool vis[maxn];
queue<int> que;
int ans;

void add_edge(int from, int to){
    node[top].to = to;
    node[top].nxt = head[from];
    head[from] = top;
    top ++;
}

void dfs(int now){
    vis[now] = true;
    bool first = true;
    for(int i = head[now]; i != -1; i = node[i].nxt){
        int nxt = node[i].to;
        if(vis[nxt])continue;
        if(!first){
            que.push(nxt);
            ans ++;
        }
        else{
            first = false;
            dfs(nxt);
        }
    }
}

void init(){
    top = ans = 0;
    while(!que.empty()) que.pop();
    memset(vis, false, sizeof(vis));
    memset(node, 0, sizeof(node));
    memset(head, -1, sizeof(head));
}

int main(){
    //freopen("in.in", "r", stdin);
    while(~scanf("%d", &n)){
        init();
        for(int i = 0; i < n; ++ i){
            int cnt, to;
            scanf("%d", &cnt);
            while(cnt --){
                scanf("%d", &to);
                add_edge(i, to);
                node[to].ind ++;
            }
        }
        for(int i = 0; i < n; ++ i){
            if(node[i].ind == 0){
                que.push(i);
                ans ++;
            }
        }
        while(!que.empty()){
            int now = que.front();
            que.pop();
            dfs(now);
        }
        printf("%d\n", ans);
    }
    return 0;
}