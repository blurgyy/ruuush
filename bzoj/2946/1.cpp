#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;

struct Node
{
  int to;
  int ne;
};

Node node[maxn<<1];
int head[maxn<<1];
int top;

void add(int from, int to)
{
  node[top].to = to;
  node[top].ne = head[from];
  head[from] = top;
  top ++;
}

//for(int i = head[u]; i != -1; i = node[i].ne){
//  /// 遍历
//}

void ini()
{
  top = 0;
  memset(head, -1, sizeof(head));
}

#define maxn 200010
#define sigma 26
struct SuffixAutomaton{
    int root;               ///root = 0;
    int size, last;
    int go[maxn][sigma];    ///转移
    int maxlen[maxn];       ///节点i代表的子串的最长长度
    int par[maxn];          ///parent树中节点i的父节点
    int cnt[maxn];          ///节点i的right集合大小
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
    void extend(int ch, int pos){
        //printf("extending: %c\n", 'a' + ch);
        int p, q, np, nq;
        p = last;
        np = new_node(maxlen[p] + 1);
        while(p != -1 && go[p][ch] == -1){///在所有的last的祖先中，为所有没有标号为x的边的节点添加一条边指向节点np=ST(Tx)
            go[p][ch] = np;
            p = par[p];
        }
        if(p == -1){///如果last的所有祖先没有标号为x的边，则状态np=trans(Tx)的parent为root
            //printf("par[%d] = root\n", np);
            par[np] = root;
        }
        else {///找到第一个有标号为x的边的状态p，令q=trans(p,x)
            q = go[p][ch];
            if(maxlen[p] + 1 == maxlen[q]){///如果maxlen[p] + 1 == maxlen[q]则直接令q的parent为np
                par[np] = q;
            }
            else {///否则新建节点nq，令maxlen[nq] = maxlen[p] + 1
                nq = new_node(maxlen[p] + 1);
                memcpy(go[nq], go[q], sizeof(go[q]));///nq的状态转移函数与q的完全相同
                par[nq] = par[q];
                par[q] = nq;        ///将parent树上的关系由q->par[q] 修改为 q->nq->par[q]
                par[np] = nq;       ///np=ST(Tx)的parent也是nq
                while(p != -1 && go[p][ch] == q){
                    go[p][ch] = nq;
                    p = par[p];
                }
            }
        }
        last = np;
        cnt[np] = 1;
        //printf("cnt[%d] = %d\n", np, cnt[np]);
    }

    int mx[maxn], mn[maxn];
    void match(char *s){
        memset(mx, 0, sizeof(mx));
        int l = 0;
        int now = root;
        while(*s){
            int ch = idx(*s);
            if(go[now][ch] != -1){
                now = go[now][ch];
                ++ l;
            }
            else {
                while(now != -1 && go[now][ch] == -1){
                    now = par[now];
                }
                if(now == -1){
                    now = root;
                    l = 0;
                }
                else {
                    l = maxlen[now] + 1;
                    now = go[now][ch];
                }
            }
            mx[now] = max(mx[now], l);
            

            ++ s;
        }
        dfs();
        //for(now = 0; now < size; ++ now){
        //    int p = now;
        //    while(par[p] != -1){
        //        mx[par[p]] = max(mx[par[p]], min(mx[p], maxlen[par[p]]));
        //        p = par[p];
        //    }
        //}
        for(int i = 0; i < size; ++ i){
            mn[i] = min(maxlen[i], min(mn[i], mx[i]));
        }
    }
    int getans(){
        int ret = 0;
        for(int i = 0; i < size; ++ i){
            ret = max(ret, mn[i]);
        }
        return ret;
    }
    void dfs(int now = 0){
        //bool leaf = true;
        for(int i = head[now]; i != -1; i = node[i].ne){
            int nxt = node[i].to;
            if(nxt != -1){
                //leaf = false;
                dfs(nxt);
                mx[now] = max(mx[now], mx[nxt]);
            }
        }
    }

    void init(char *s){
        size = 0;
        last = root = new_node(0);
        memset(mn, 0x3f, sizeof(mn));
        memset(cnt, 0, sizeof(cnt));
        int len = strlen(s);
        for(int i = 0; i < len; ++ i){
            extend(idx(s[i]), i);
        }
        for(int i = 1; i < size; ++ i){
            add(par[i], i);
        }
    }
}sam;
#undef sigma
#undef maxn
int n;
char s[maxn];

int main(){
    //freopen("in.in", "r", stdin);
    while(~scanf("%d%s", &n, s)){
        sam.init(s);
        ini();
        -- n;
        while(n --){
            scanf("%s", s);
            sam.match(s);
        }
        printf("%d\n", sam.getans());
    }
    return 0;
}