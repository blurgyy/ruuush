#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100010;
const int inf = 0x3f3f3f3f;

struct Node{
    int to;
    int nxt;
    int w;
};
int T;
int n, d, c;
int a, b, s;
int failtime[10010];
Node node[maxn];
int head[maxn];
int top;

void add_edge(int from, int to, int w){
    node[top].to = to;
    node[top].w = w;
    node[top].nxt = head[from];
    head[from] = top;
    top ++;
}

void bfs(int in){
    //printf("inbfs\n");
    failtime[in] = 0;
    queue<int> que;
    que.push(in);
    while(!que.empty()){
        int now = que.front();
        que.pop();
        for(int i = head[now]; i != -1; i = node[i].nxt){
            int nxt = node[i].to;
            if(failtime[nxt] <= failtime[now] + node[i].w){
                //printf("%d, %d\n", failtime[nxt], failtime[now], node[i].w);
                continue;
            }
            que.push(nxt);
            failtime[nxt] = min(failtime[nxt], failtime[now] + node[i].w);
            //printf("failtime[%d] = %d\n", nxt, failtime[nxt]);
        }
    }
    //printf("bfs(out)\n");
}

void init(){
    top = 0;
    memset(failtime, 0x3f, sizeof(failtime));
    memset(head, -1, sizeof(head));
    memset(node, 0, sizeof(node));
}

int main(){
    //freopen("in.in", "r", stdin);
    scanf("%d", &T);
    while(T --){
        init();
        scanf("%d%d%d", &n, &d, &c);
        while(d --){
            scanf("%d%d%d", &a, &b, &s);
            add_edge(b, a, s);
        }
        bfs(c);
        int ans = -1, cnt = 0;
        for(int i = 1; i <= n; ++ i){
            if(failtime[i] == inf)continue;
            cnt ++;
            ans = max(ans, failtime[i]);
        }
        printf("%d %d\n", cnt, ans);
    }
    //fclose(stdin);
    return 0;
}