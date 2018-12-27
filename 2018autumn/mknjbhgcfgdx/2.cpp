#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int maxn = 1000010;
const int maxq = 100010;
const int sigma = 4;

/***************/
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

void dfs(int now = 0, int prv = -1){
    printf("implementing: %d, cnt[%d] = %lld\n", now, now, PT.cnt[now]);
    for(int i = head[now]; i != -1; i = node[i].ne){
        int nxt = node[i].to;
        if(nxt == prv)continue;
        dfs(nxt, now);
    }
}

bool vis[maxn];
void tarjan(int now = 0){
    //printf("now = %d\n", now);
    fa[now] = now;
    vis[now] = true;
    for(int i = head[now]; i != -1; i = node[i].ne){
        int nxt = node[i].to;
        if(!vis[nxt]){
            tarjan(nxt);
            unite(nxt, now);
        }
    }
    int id = get_first_query(now);
    while(id < tot && qrec[id].first == now){
        int query = qrec[id].second;
        if(vis[query]){
            ans[id] = find(query);
            int loctn = loc(make_pair(query, now));
            ans[loctn] = ans[id];
            //printf("lca(%d, %d) = %d\n", now, query, ans[id]);
        }
        id ++;
    }
}

void init(){
    ini();
    PT.init(s);
    memset(vis, false, sizeof(vis));
    for(int i = 0; i < maxn; ++ i)fa[i] = i;
}

int main(){
    freopen("in3.in", "r", stdin);
    while(~scanf("%d%s%d", &n, s + 1, &q)){
        tot = q * 2;
        init();
        for(register int i = 0, x, y; i < tot; i += 2){
            scanf("%d%d", &x, &y);
            x = PT.nodeidx[x];
            y = PT.nodeidx[y];
            in[i/2] = make_pair(x, y);
            qrec[i] = make_pair(x, y);
            qrec[i+1] = make_pair(y, x);
        }
        sort(qrec, qrec + q*2);
        count();
        tarjan();
        for(int i = 0; i < q; ++ i){
            //printf("lca(%d, %d)=%d----------", in[i].first, in[i].second, ans[loc(in[i])]);
            printf("%lld\n", PT.cnt[ans[loc(in[i])]]);
        }
        //dfs();
        //for(int i = 1; i <= n; ++ i){
        //    printf("nodeidx[%c] = %d\n", s[i], PT.nodeidx[i]);
        //}

    }
    return 0;
}