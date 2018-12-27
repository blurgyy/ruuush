#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1010;

struct Node{
    int to, nxt;
    int ind;
    int siz, son, dep;  ///son: heavy
}node[maxn];
int n, a[maxn];
int head[maxn], top;
int startpt[maxn], p;

void add_edge(int from, int to){
    node[top].to = to;
    node[top].nxt = head[from];
    head[from] = top;
    top ++;
}

void dfs(int now){
    for(int i = head[now]; i != -1; i = node[i].nxt){
        int nxt = node[i].to;
        
    }
}

void init(){
    top = p = 0;
    memset(node, 0, sizeof(node));
    memset(head, -1, sizeof(head));
}

int main(){
    while(~scanf("%d", &n)){
        init();
        for(int i = 0; i < n; ++ i){
            int cnt, to;
            scanf("%d", &cnt);
            while(cnt --){
                scanf("%d", &to);
                add_edge(i, to);
                ind[to] ++;
            }
        }
        for(int i = 0; i < n; ++ i){
            if(node[i].ind == 0){
                startpt[p++] = i;
            }
        }
        for(int i = 0; i < pt; ++ i){
            dfs(i);
        }
        queue<int> que;


        while(!que.empty()){

        }

    }
    return 0;
}