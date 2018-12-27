#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 100010;
const int inf = 0x3f3f3f3f;

struct stn{
    int left, right;
    int minval;
    ll ans;    ///min(minval), sum(ans);
    int lazy;
    void upd(int val){
        minval += val;
        lazy += val;
    }
}Tree[maxn<<2];
int n, q;
int b[maxn];

void pushUp(int now){
    Tree[now].minval = min(Tree[now<<1].minval, Tree[now<<1|1].minval);
    Tree[now].ans = Tree[now<<1].ans + Tree[now<<1|1].ans;
    //printf("%d to %d = %d\n", Tree[now].left, Tree[now].right, Tree[now].ans);
}

void pushDown(int now){
    int val = Tree[now].lazy;
    if(val){
        Tree[now].lazy = 0;
        Tree[now<<1].upd(val);
        Tree[now<<1|1].upd(val);
    }
}

void install(int id){
    queue<int> que;
    que.push(id);
    while(!que.empty()){
        int now = que.front();
        que.pop();
        //printf("now = %d\n", now);
        if(Tree[now].left == Tree[now].right){
            Tree[now].minval = b[Tree[now].right];
            Tree[now].ans ++;
            //printf("%d: %d %d, %d\n", now, Tree[now].left, Tree[now].right, Tree[now].ans);
            while(now >>= 1){
                Tree[now].minval = min(Tree[now<<1].minval, Tree[now<<1|1].minval);
                Tree[now].ans = Tree[now<<1].ans + Tree[now<<1|1].ans;
            }
            continue;
        }
        pushDown(now);
        if(Tree[now<<1].minval == 0){
            que.push(now << 1);
        }
        if(Tree[now<<1|1].minval == 0){
            que.push(now << 1 | 1);
        }
    }
}

void build(int arr[], int left = 1, int right = n, int now = 1){
    Tree[now].left = left;
    Tree[now].right = right;
    Tree[now].minval = inf;
    Tree[now].ans = Tree[now].lazy = 0;
    if(left == right){
        Tree[now].minval = b[right];
        return;
    }
    int mid = left + right >> 1;
    build(arr, left, mid, now << 1);
    build(arr, mid + 1, right, now << 1 | 1);
    pushUp(now);
}

void update(int uleft, int uright, int now = 1){
    int left = Tree[now].left, right = Tree[now].right;
    //printf("%d to %d\n", left, right);
    if(uleft <= left && right <= uright){
        Tree[now].upd(-1);
        if(Tree[now].minval == 0){
            //printf("test\n");
            install(now);
        }
        return;
    }
    int mid = left + right >> 1;
    pushDown(now);
    if(uleft <= mid)update(uleft, uright, now << 1);
    if(uright > mid)update(uleft, uright, now << 1 | 1);
    pushUp(now);
}

int getmin(int mleft, int mright, int now = 1){
    int left = Tree[now].left, right = Tree[now].right;
    if(mleft <= left && right <= mright){
        return Tree[now].minval;
    }
    int ret = inf;
    int mid = left + right >> 1;
    pushDown(now);
    if(mleft <= mid)ret = min(ret, getmin(mleft, mright, now << 1));
    if(mright > mid)ret = min(ret, getmin(mleft, mright, now << 1 | 1));
    return ret;
}

ll query(int qleft, int qright, int now = 1){
    int left = Tree[now].left, right = Tree[now].right;
    //printf("%d to %d\n", left, right);
    if(qleft <= left && right <= qright){
        return Tree[now].ans;
    }
    ll ret = 0;
    int mid = left + right >> 1;
    if(qleft <= mid)ret += query(qleft, qright, now << 1);
    if(qright > mid)ret += query(qleft, qright, now << 1 | 1);
    return ret;
}

//#define fin
//#define fout
int main(){
    #ifdef fin
        freopen("in.in", "r", stdin);
    #endif
    #ifdef fout
        freopen("out.out", "w", stdout);
    #endif

    while(~scanf("%d%d", &n, &q)){
        for(int i = 1; i <= n; ++ i){
            scanf("%d", b + i);
        }
        build(b);
        while(q --){
            int l, r;
            char op[10];
            scanf("%s%d%d", op, &l, &r);
            if(!strcmp(op, "add")){
                update(l, r);
            }
            else {
                printf("%lld\n", query(l, r));
            }
        }
    }
    return 0;
}

/**

5 12
1 5 2 4 3
add 1 4
query 1 4
add 2 5
query 2 5
add 3 5
query 1 5
add 2 4
query 1 4
add 2 5
query 2 5
add 2 2
query 1 5

6 1000
1 2 3 4 5 6
add 2 6
add 3 6
add 4 6
add 5 6
add 6 6


*/