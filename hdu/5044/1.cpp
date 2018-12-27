/// TLE while using segment tree!
/// Don't be silly, fwend

//#include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 100010;

struct Node
{
    int to, ne;
    int fa, size, son, dep;     /**  dfs()
                                  *  fa: parent node
                                  *  size: cnt_node
                                  *  son: heavy
                                  *  dep: depth of current node
                                  */
    int top, pos;               /**  _dfs()
                                  *  top: top node
                                  *  pos: node's index in *array* seq[]
                                  */
}node[maxn];
struct segTree{
    int left, right;
    ll nval, eval;              /**  nval: value of (node)
                                  *  eval: value of (node to its father_node)
                                  */
}Tree[maxn<<2];
int head[maxn]; /// point
int top, totw;
int T, n, m, Case = 0;
int seq[maxn];
int u[maxn], v[maxn];
ll edgev[maxn], nodev[maxn];
ll anse[maxn], ansn[maxn];
/// int v[maxn][2];   ///0 for node, 1 for edge
char op[10];

int dfs(int now, int prev = -1, int depth = 0){
    node[now].fa = prev;
    node[now].dep = depth;
    int ret = 1;
    int cur_size = -1;
    for(int i = head[now]; i != -1; i = node[i].ne){
        int nxt = node[i].to;
        if(nxt == prev)continue;

        int son_size = dfs(nxt, now, depth + 1);
        if(cur_size < son_size){
            cur_size = son_size;
            node[now].son = nxt;
        }

        ret += son_size;
    }
    node[now].size = ret;
    return ret;
}

void _dfs(int now, int prev = -1){
    node[now].pos = totw;
    seq[totw ++] = now;
    if(node[now].top == -1){
        node[now].top = now;
    }
    if(node[now].son != -1){
        node[node[now].son].top = node[now].top;
        _dfs(node[now].son, now);
    }
    for(int i = head[now]; i != -1; i = node[i].ne){
        int nxt = node[i].to;
        if(nxt == prev || nxt == node[now].son)
            continue;
        _dfs(nxt, now);
    }
}

void pushDownN(int now){
    int d1 = Tree[now].nval;
    if(d1){
        Tree[now].nval = 0;
        Tree[now<<1].nval += d1;
        Tree[now<<1|1].nval += d1;
    }
}

void pushDownE(int now){
    int d2 = Tree[now].eval;
    if(d2){
        Tree[now].eval = 0;
        Tree[now<<1].eval += d2;
        Tree[now<<1|1].eval += d2;
    }
}

void build(int left = 1, int right = totw - 1, int now = 1){
    Tree[now].left = left;
    Tree[now].right = right;
    Tree[now].nval = Tree[now].eval = 0;
    if(left == right){
        return;
    }
    int mid = left + right >> 1;
    build(left, mid, now << 1);     
    build(mid + 1, right, now << 1 | 1);
}

void updateN(int uleft, int uright, int val, int now = 1){
    nodev[uleft] += val;
    nodev[uright + 1] -= val;
}

void updateE(int uleft, int uright, int val, int now = 1){
    edgev[uleft] += val;
    //printf("edgev[%d] = %lld\n", uleft, edgev[uleft]);
    edgev[uright + 1] -= val;
    //printf("edgev[%d] = %lld\n", uright + 1, edgev[uright + 1]);
}

ll queryN(int pos, int now = 1){
    int left = Tree[now].left, right = Tree[now].right;
    if(left == right){
        return Tree[now].nval;
    }
    int mid = left + right >> 1;
    pushDownN(now);
    if(pos <= mid)return queryN(pos, now << 1);
    return queryN(pos, now << 1 | 1);
}

ll queryE(int pos, int now = 1){
    int left = Tree[now].left, right = Tree[now].right;
    if(left == right){
        return Tree[now].eval;
    }
    int mid = left + right >> 1;
    pushDownE(now);
    if(pos <= mid)return queryE(pos, now << 1);
    return queryE(pos, now << 1 | 1);
}

void add_edge(int from, int to){
    node[top].to = to;
    node[top].ne = head[from];
    head[from] = top;
    top ++;
}

void ini(){
    memset(head, -1, sizeof(head));
    memset(node, -1, sizeof(node));
    memset(nodev, 0, sizeof(nodev));
    memset(edgev, 0, sizeof(edgev));
    memset(ansn, 0, sizeof(ansn));
    memset(anse, 0, sizeof(anse));
    totw = 1;
    top = 0;
}

void out(){
    ll nv = 0, ev = 0;
    for(int i = 1; i <= n; ++ i){
        nv += nodev[i];
        ansn[seq[i]] = nv;
    }
    for(int i = 1; i <= n; ++ i){
        if(i == 1)printf("%lld", ansn[i]);
        else printf(" %lld", ansn[i]);
    }
    printf("\n");
    for(int i = 1; i <= n; ++ i){
        ev += edgev[i];
        anse[seq[i]] = ev;
    }
    for(int i = 1; i < n; ++ i){
        int nod = -1;
        if(node[u[i]].fa == v[i]){
            nod = u[i];
        }
        else {
            nod = v[i];
        }
        if(nod == -1){
            printf("wtf\n");
        }
        if(i == 1)printf("%lld", anse[nod]);
        else printf(" %lld", anse[nod]);
        //printf("(%d to %d, fa = %d): %lld \n", nod, node[nod].fa, nod, queryE(node[nod].pos), " \n"[i == n]);
        //printf("%lld%c", ev, " \n"[i == n-1]);
    }
    printf("\n");
}

int main(){
    //freopen("in2.in", "r", stdin);
    scanf("%d", &T);
    while(T --){
        ini();
        scanf("%d%d", &n, &m);
        for(int i = 1; i < n; ++ i){
            scanf("%d%d", u + i, v + i);
            add_edge(u[i], v[i]);
            add_edge(v[i], u[i]);
        }
        int root = 1;
        dfs(root);
        _dfs(root);
        //build();
/*
        printf("totw = %d\n", totw);
        for(int i = 1; i < totw; ++ i){
            printf("%d%c", seq[i], " \n"[i == totw - 1]);
        }
*/
        int l, r, k;
        while(m --){
            scanf("%s%d%d%d", op, &l, &r, &k);
            if(!strcmp(op, "ADD1")){
                while(1){
                    int f1 = node[l].top, f2 = node[r].top;
                    //printf("f1 = %d, f2 = %d\n", f1, f2);
                    if(f1 == f2){
                        if(node[l].pos > node[r].pos)swap(l, r);
                        //printf("(%d to %d)\n", node[l].pos, node[r].pos);
                        updateN(node[l].pos, node[r].pos, k);
                        break;
                    }
                    if(node[f1].dep > node[f2].dep){
                        updateN(node[f1].pos, node[l].pos, k);
                        l = node[f1].fa;
                    }
                    else {
                        updateN(node[f2].pos, node[r].pos, k);
                        r = node[f2].fa;
                    }
                }

                for(int i = 1; i <= n; ++ i){
                    //printf("nodev[%d] = %lld\n", i, nodev[i]);
                }
            }
            else if(!strcmp(op, "ADD2")){
                while(1){
                    int f1 = node[l].top, f2 = node[r].top;
                    //printf("f1 = %d, f2 = %d\n", f1, f2);
                    if(f1 == f2){
                        //printf("f1 = f2: l = %d, r = %d\n", l, r);
                        if(l == r)break;
                        if(node[l].pos > node[r].pos)swap(l, r);
                        updateE(node[l].pos + 1, node[r].pos, k);
                        break;
                    }
                    if(node[f1].dep > node[f2].dep){
                        updateE(node[f1].pos, node[l].pos, k);
                        l = node[f1].fa;
                        //printf("pos = %d, %lld\n", node[l].pos, queryE(node[l].pos));
                    }
                    else {
                        updateE(node[f2].pos, node[r].pos, k);
                        r = node[f2].fa;
                    }
                }
            }
            else {
                printf("wtf\n");
            }

            //out();
        }
        printf("Case #%d:\n", ++ Case);
        out();
    }
    return 0;
}