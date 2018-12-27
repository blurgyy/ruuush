#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 10010;

struct Node{
    int from;
    int to;
    int w;
    int nxt;
}node[maxn];
int n, m;
int ind[maxn], outd[maxn];
int ans[maxn];
int head[maxn], top;

void add_edge(int from, int to, int w){
    node[top].to = to;
    node[top].w = w;
    node[top].nxt = head[from];
    head[from] = top ++;
}

void init(){
    memset(head, -1, sizeof(head));
    memset(ind, 0, sizeof(ind));
    memset(outd, 0, sizeof(outd));
    memset(ans, 0, sizeof(ans));
    top = 0;
}

int main(){
    while(~scanf("%d%d", &n, &m)){
        init();
        while(m --){
            int from, to, w;
            scanf("%d%d%d", &from, &to, &w);
            add_edge(from, to, w);
            outd[from] ++;
            ind[to] ++;
        }
        priority_queue<pair<int, int> > que;
        int max_cond = -1;
        for(int id = 1; id < 1001; ++ id){
            //printf("id = %d\n", id);
            if(outd[id]){
                while(!que.empty())que.pop();
                que.push(make_pair(0, id));
                //memset(ans, 0, sizeof(ans));
                while(!que.empty()){
                    //printf("que.size = %d\n", que.size());
                    int now = que.top().second;
                    //printf("now = %d\n", now);
                    max_cond = max(max_cond, ans[now]);
                    que.pop();
                    for(int i = head[now]; i != -1; i = node[i].nxt){
                        int nxt = node[i].to, w = node[i].w;
                        if(ans[nxt] < ans[now] + w){
                            ans[nxt] = ans[now] + w;
                            //printf("%d to %d: %d\n", id, nxt, ans[nxt]);
                            que.push(make_pair(ans[nxt], nxt));
                        }
                    }
                }
            }
        }
        printf("%d\n", max_cond);
    }
    return 0;
}

/**

5 5
1 2 15
2 3 12
1 4 17
4 2 11
5 4 9

6 6
1 2 2
4 5 2
2 3 3
1 3 2
5 6 2
1 2 4

*/