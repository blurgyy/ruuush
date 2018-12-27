#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100010;
const int inf = 0x3f3f3f3f;

struct Node{
    int a, b, c;
    bool operator< (Node d){
        return a < d.a;
    }
}rk[maxn];
struct STN{
    int left, right;
    int minv;
}Tree[maxn<<2];
int T, n;

void pushUp(int now){
    Tree[now].minv = min(Tree[now<<1].minv, Tree[now<<1|1].minv);
}

void build(int left = 1, int right = n, int now = 1){
    Tree[now].left = left;
    Tree[now].right = right;
    Tree[now].minv = inf;
    if(left >= right){
        return;
    }
    int mid = left + right >> 1;
    build(left, mid, now << 1);
    build(mid + 1, right, now << 1 | 1);
}

void update(int pos, int val, int now = 1){
    int left = Tree[now].left, right = Tree[now].right;
    if(left == right){
        Tree[now].minv = val;
        return;
    }
    int mid = left + right >> 1;
    if(pos <= mid)update(pos, val, now << 1);
    else update(pos, val, now << 1 | 1);
    pushUp(now);
}

int query(int qleft, int qright, int now = 1){
    int left = Tree[now].left, right = Tree[now].right;
    if(qleft <= left && right <= qright){
        return Tree[now].minv;
    }
    int mid = left + right >> 1;
    int ret = inf;
    if(qleft <= mid)ret = min(ret, query(qleft, qright, now << 1));
    if(qright > mid)ret = min(ret, query(qleft, qright, now << 1 | 1));
    return ret;
}

void init(){
    memset(Tree, 0, sizeof(Tree));
    //memset(a, 0x3f, sizeof(a));
}

int main(){
    //freopen("in.in", "r", stdin);
    scanf("%d", &T);
    while(T --){
        init();
        scanf("%d", &n);
        for(int i = 1; i <= n; ++ i)
            scanf("%d%d%d", &rk[i].a, &rk[i].b, &rk[i].c);
        sort(rk + 1, rk + n + 1);
        /*
        for(int i = 1; i <= n; ++ i){
            printf("%d %d %d\n", rk[i].a, rk[i].b, rk[i].c);
        }
        */
        build();
        int ans = 0;
        for(int i = 1; i <= n; ++ i){
            update(rk[i].b, rk[i].c);
            //printf("a[%d] = %d\n", rk[i].b, rk[i].c);
            if(rk[i].b == 1)continue;
            int minv = query(1, rk[i].b - 1);
            if(minv < rk[i].c){
                //printf("a = (%d), b = (%d), c = (%d, %d)\n", rk[i].a, rk[i].b, rk[i].c, minv);
                ans ++;
            }
        }
        printf("%d\n", n - ans);
    }
    return 0;
}