#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int maxn = 1000010;
const int maxq = 100010;
const int sigma = 4;

/***************/
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
int totw;                       /// = 1, for(int i = 1; i < totw; ++ i){}
int seq[maxn];
int head[maxn];
int top;
void add(int from, int to){
    //printf("from (%d) to (%d)\n", from, to);
    node[top].to = to;
    node[top].ne = head[from];
    head[from] = top;
    top ++;
}
int dfs(int now, int prv = -1, int depth = 0){
    node[now].fa = prv;
    node[now].dep = depth;
    int ret = 1;
    int cur_size = -1;
    for(int i = head[now]; i != -1; i = node[i].ne){
        int nxt = node[i].to;
        if(nxt == prv)continue;

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
void _dfs(int now, int prv = -1){
    node[now].pos = totw;
    seq[totw ++] = now;
    if(node[now].top == -1){
        node[now].top = now;
    }
    //printf("node[%d].son = %d\n", now, node[now].son);
    if(node[now].son != -1){
        node[node[now].son].top = node[now].top;
        _dfs(node[now].son, now);
    }
    for(int i = head[now]; i != -1; i = node[i].ne){
        int nxt = node[i].to;
        //printf("nxt = %d???\n", nxt);
        if(nxt == prv || nxt == node[now].son)
            continue;
        _dfs(nxt, now);
    }
}
int lca(int x, int y){
    //printf("in lca(%d, %d)\n", x, y);
    while(true){
        //printf("fa[%d] = %d, fa[%d] = %d\n", x, node[x].fa, y, node[y].fa);
        //printf("fa: (%d, %d), (%d, %d)\n", x, node[x].fa, y, node[y].fa);
        //printf("top: (%d, %d), (%d, %d)\n", x, node[x].top, y, node[y].top);
        //printf("dep: (%d, %d), (%d, %d)\n", x, node[x].dep, y, node[y].dep);
        if(node[x].top == node[y].top){
            return node[x].dep <= node[y].dep ? x : y;
        }
        if(node[node[x].top].dep >= node[node[y].top].dep){
            x = node[node[x].top].fa;
        }
        else {
            y = node[node[y].top].fa;
        }
    }
}
void ini(){
    memset(node, -1, sizeof(node));
    memset(head, -1, sizeof(head));
    top = 0;
    totw = 1;
}
/****************/

/***union_find***/
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
/****************/

struct Palindromic_Tree{
    int nodeidx[maxn];
    int child[maxn][sigma], fail[maxn];
    int depth[maxn];
    ll cnt[maxn];
    int size, last, len;
    char s[maxn];
    int idx(char ch){
        return ch - 'a';
    }
    int new_node(int length){
        memset(child[size], 0, sizeof(child[size]));
        fail[size] = 0;
        depth[size] = length;
        cnt[size] = 0;
        return size++;
    }
    void Extend(int ch, int pos){
        int p = last;
        while (s[pos - depth[p] - 1] != s[pos]){
            p = fail[p];
        }
        if (!child[p][ch]){
            int now = new_node(depth[p] + 2), fa = fail[p];
            while (s[pos - depth[fa] - 1] != s[pos])
                fa = fail[fa];
            fail[now] = child[fa][ch];
            if (fail[now] == 0) fail[now] = 1;
            add(fail[now], now);
            //add(now, fail[now]);
            child[p][ch] = now;
        }
        last = child[p][ch];
        cnt[last]++;
        /**/nodeidx[pos] = last;
    }
    void init(char *x){
        len = strlen(x + 1);
        for (int i = 1; i <= len; i++)
            s[i] = x[i];
        size = 0;
        new_node(-1);
        new_node(0);
        fail[0] = fail[1] = 0;
        add(fail[1], 1);
        //add(1, fail[1]);
        depth[0] = -1;
        last = 1;
        for (int i = 1; i <= len; i++)
            Extend(idx(s[i]), i);
    }
}PT;
int n, q, tot;
int ans[maxq<<1];
char s[maxn];
pii qrec[maxq<<1];
pii in[maxq];

int bs(pii arr[], int e, int left = 0, int right = q * 2 - 1){
    if(left >= right)return right;
    int mid = (left + right) / 2;
    if(e <= arr[mid].first)return bs(arr, e, left, mid);
    return bs(arr, e, mid + 1, right);
}

int bs_(pii arr[], pii e, int left = 0, int right = q * 2 - 1){
    if(left >= right)return right;
    int mid = (left + right) / 2;
    if(e <= arr[mid])return bs_(arr, e, left, mid);
    return bs_(arr, e, mid + 1, right);
}

int get_first_query(int x){
    return bs(qrec, x);
}

int loc(pii x){
    return bs_(qrec, x);
}

ll count_(int now = 0, int prv = -1){
    //bool leaf = true;
    for(int i = head[now]; i != -1; i = node[i].ne){
        int nxt = node[i].to;
        if(nxt == prv)continue;
        PT.cnt[now] += count_(nxt, now);
        //printf("PT.cnt[%d] = %d\n", now, PT.cnt[now]);
        //leaf = false;
    }
    return PT.cnt[now];
}

void count(){
    count_();
    PT.cnt[0] = PT.cnt[1] = 0;
    count_();
}

void de8g(int now = 0, int prv = -1){
    printf("implementing: %d, cnt[%d] = %lld\n", now, now, PT.cnt[now]);
    for(int i = head[now]; i != -1; i = node[i].ne){
        int nxt = node[i].to;
        if(nxt == prv)continue;
        de8g(nxt, now);
    }
}

void init(){
    ini();
    PT.init(s);
    count();
    for(int i = 0; i < maxn; ++ i)fa[i] = i;
}

int main(){
    freopen("in.in", "r", stdin);
    while(~scanf("%d%s%d", &n, s + 1, &q)){
        tot = q * 2;
        init();
        //de8g();
        int root = 1;
        dfs(root);
        _dfs(root);
        for(register int i = 0, x, y; i < tot; i += 2){
            scanf("%d%d", &x, &y);
            x = PT.nodeidx[x];
            y = PT.nodeidx[y];
            printf("%lld\n", PT.cnt[lca(x, y)]);
        }
    }
    return 0;
}