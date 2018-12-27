/// #define debug

#include <bits/stdc++.h>
using namespace std;
const int maxn = 50010;

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
};
struct segTree{
    int left, right;
    int diff;
}Tree[maxn<<2];
Node node[maxn];
int head[maxn]; /// point
int top;
int n, m, p, totw;
int seq[maxn], a[maxn];

void pushDown(int now){
    int diff = Tree[now].diff;
    Tree[now].diff = 0;
    Tree[now<<1].diff += diff;
    Tree[now<<1|1].diff += diff;
}

void build(int left = 1, int right = totw - 1, int now = 1){
    Tree[now].left = left;
    Tree[now].right = right;
    Tree[now].diff = 0;
    if(left >= right){
        return;
    }
    int mid = left + right >> 1;
    build(left, mid, now << 1);
    build(mid + 1, right, now << 1 | 1);
}

void update(int uleft, int uright, int val, int now = 1){
    //printf("%d to %d\n", uleft, uright);
    int left = Tree[now].left, right = Tree[now].right;
    if(uleft <= left && right <= uright){
        Tree[now].diff += val;
        return;
    }
    int mid = left + right >> 1;
    pushDown(now);
    if(uleft <= mid)update(uleft, uright, val, now << 1);
    if(uright > mid)update(uleft, uright, val, now << 1 | 1);
}

int query(int pos, int now = 1){
    if(Tree[now].left == Tree[now].right){
        return Tree[now].diff;
    }
    int mid = Tree[now].left + Tree[now].right >> 1;
    pushDown(now);
    if(pos <= mid)return query(pos, now << 1);
    return query(pos, now << 1 | 1);
}

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

void add_edge(int from, int to){
    node[top].to = to;
    node[top].ne = head[from];
    head[from] = top;
    top ++;
}

void ini(){
    memset(head, -1, sizeof(head));
    memset(node, -1, sizeof(node));
    totw = 1;
    top = 0;
}

int main(){
    //freopen("in.in", "r", stdin);
    while(~scanf("%d%d%d", &n, &m, &p)){
        ini();
        if(m != n - 1){
            printf("wtf\n");
        }
        for(int i = 1; i <= n; ++ i)
            scanf("%d", a + i);
        for(int i = 0; i < m; ++ i){
            int u, v;
            scanf("%d%d", &u, &v);
            add_edge(u, v);
            add_edge(v, u);
        }
        srand(time(NULL)); 
        int root = rand() % n + 1;
        // root = 1;
        dfs(root);
        _dfs(root);
/*
        printf("root = %d\n", root);
        for(int i = 1; i <= 14; ++ i)
            printf("fa(%d) = %d, son(%d) = %d\n", i, node[i].fa, i, node[i].son);
        printf("totw = %d\n", totw);
        for(int i = 1; i < totw; ++ i){
            printf("%d ", seq[i]);
        }
        printf("\n");
*/
        build();
        char op[5];
        while(p --){
            scanf("%s", op);
            if(!strcmp(op, "I")){
                int l, r, k;
                scanf("%d%d%d", &l, &r, &k);
                while(true){
                    int f1 = node[l].top, f2 = node[r].top;
                    //printf("f1 = %d, f2 = %d\n", f1, f2);
                    if(f1 == f2){
                        if(node[l].pos > node[r].pos)swap(l, r);
                        //printf("lpos = %d, rpos = %d\n", node[l].pos, node[r].pos);
                        update(node[l].pos, node[r].pos, k);
                        break;
                    }
                    if(node[f1].dep > node[f2].dep){
                        update(node[f1].pos, node[l].pos, k);
                        l = node[f1].fa;
                    }
                    else {
                        update(node[f2].pos, node[r].pos, k);
                        r = node[f2].fa;
                    }
                }
                //printf("test\n");
            }
            else if(!strcmp(op, "D")){
                int l, r, k;
                scanf("%d%d%d", &l, &r, &k);
                while(true){
                    int f1 = node[l].top, f2 = node[r].top;
                    if(f1 == f2){
                        if(node[l].pos > node[r].pos)swap(l, r);
                        update(node[l].pos, node[r].pos, -k);
                        break;
                    }
                    if(node[f1].dep > node[f2].dep){
                        update(node[f1].pos, node[l].pos, -k);
                        l = node[f1].fa;
                    }
                    else {
                        update(node[f2].pos, node[r].pos, -k);
                        r = node[f2].fa;
                    }
                }
            }
            else {
                int in;
                scanf("%d", &in);
                int diff = query(node[in].pos);
                //printf("in = %d, diff = %d\n", in, diff);
                printf("%d\n", a[in] + diff);
            }
        }


    }
    return 0;
}