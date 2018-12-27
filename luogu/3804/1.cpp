#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000010;
const int sigma = 26;

struct Node{
    int to;
    int ne;
};
Node node[maxn];
int head[maxn];
int top;
void add(int from, int to){
    node[top].to = to;
    node[top].ne = head[from];
    head[from] = top;
    top ++;
}
//for(int i = head[u]; i != -1; i = node[i].ne){
//  /// 遍历
//}
void ini(){
    top = 0;
    memset(head, -1, sizeof(head));
}

int cnt[maxn];
struct SuffixAutomaton{
    int root;
    int size, last;
    int go[maxn][sigma], maxlen[maxn], par[maxn];
    bool vis[maxn];
    SuffixAutomaton(){size = 0;}
    int new_node(int len){
        memset(go[size], -1, sizeof(go[size]));
        maxlen[size] = len;
        par[size] = -1;
        return size ++;
    }
    int idx(char ch){
        return ch - 'a';
    }
    void extend(int ch){
        //printf("extending: %c\n", 'a' + ch);
        int p, q, np, nq;
        p = last;
        np = new_node(maxlen[p] + 1);
        //cnt[np] = 1;
        while(p != -1 && go[p][ch] == -1){
            go[p][ch] = np;
            p = par[p];
        }
        if(p == -1){
            //printf("par[%d] = root\n", np);
            par[np] = root;
        }
        else {
            q = go[p][ch];
            if(maxlen[p] + 1 == maxlen[q]){
                par[np] = q;
            }
            else {
                nq = new_node(maxlen[p] + 1);
                //cnt[nq] = 1;
                memcpy(go[nq], go[q], sizeof(go[q]));
                par[nq] = par[q];
                par[q] = nq;
                par[np] = nq;
                while(p != -1 && go[p][ch] == q){
                    go[p][ch] = nq;
                    p = par[p];
                }
            }
        }
        last = np;
        cnt[np] = 1;
    }
    void init(char *s){
        size = 0;
        last = root = new_node(0);
        int len = strlen(s);
        for(int i = 0; i < len; ++ i){
            extend(idx(s[i]));
        }
    }
    void dfs(int now = 0){
        vis[now] = true;
        //printf("par[%d] = %d\n", now, par[now]);
        if(par[now] != -1){
            add(par[now], now);
        }
        for(int i = 0; i < sigma; ++ i){
            //if(go[now][i] != -1 && vis[go[now][i]] == false){
            //    dfs(go[now][i]);
            //}
            if(go[now][i] != -1){
                if(vis[go[now][i]]){
                    //printf("[%d] son[%c] is %d\n", now, 'a' + i, go[now][i]);
                    continue;
                }
                //printf("go[%d][%c] = %d\n", now, 'a' + i, go[now][i]);
                dfs(go[now][i]);
            }
        }
    }
}SAM;
char s[maxn];

int bucket[maxn];
int seq[maxn];
void count(int now = SAM.root){
    for(int i = head[now]; i != -1; i = node[i].ne){
        int nxt = node[i].to;
        count(nxt);
        cnt[now] += cnt[nxt];
    }
}

void init(){
    ini();
    SAM.init(s);
    memset(SAM.vis, false, sizeof(SAM.vis));
    for(int i = 1; i < SAM.size; ++ i)add(SAM.par[i], i);
}

int main(){
    //while(~scanf("%s", s)){
    scanf("%s", s);{
        init();
        count();
        long long ans = 0;
        for(int i = 0; i < SAM.size; ++ i){
            //printf("mlen[%d] = %d, cnt[%d] = %d\n", i, SAM.maxlen[i], i, cnt[i]);
            if(cnt[i] > 1){
                ans = max(ans, 1LL * SAM.maxlen[i] * cnt[i]);
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}