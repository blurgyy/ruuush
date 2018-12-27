#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int maxn = 1000010;
const int inf = 0x3f3f3f3f;
const int mod = 1000000007;

int T, n;
int a[maxn];
ll ans;
struct stn{
    int left, right;
    int maxv, pos;
}Tree[maxn<<2];

void pushUp(int now){
    if(Tree[now<<1].maxv == Tree[now<<1|1].maxv){
        Tree[now].maxv = max(Tree[now<<1].maxv, Tree[now<<1|1].pos);
        Tree[now].pos = min(Tree[now<<1].pos, Tree[now<<1|1].pos);
    }
    else if(Tree[now<<1].maxv > Tree[now<<1|1].maxv){
        Tree[now].maxv = Tree[now<<1].maxv;
        Tree[now].pos = Tree[now<<1].pos;
    }
    //if(Tree[now<<1].maxv < Tree[now<<1|1].maxv){
    else{
        Tree[now].maxv = Tree[now<<1|1].maxv;
        Tree[now].pos = Tree[now<<1|1].pos;
    }
}

void build(int left = 1, int right = n, int now = 1){
    Tree[now].left = left;
    Tree[now].right = right;
    if(left == right){
        Tree[now].maxv = a[right];
        Tree[now].pos = right;
        //printf("a[%d] = %d\n", right, a[right]);
        return;
    }
    int mid = left + right >> 1;
    build(left, mid, now << 1);
    build(mid + 1, right, now << 1 | 1);
    pushUp(now);
}

void f(pii &a, pii &b){
    if(a.first == b.first){
        a.second = min(a.second, b.second);
        return;
    }
    if(a.first < b.first){
        a = b;
        return;
    }
}

pii query(int qleft, int qright, int now = 1){
    pii ret = make_pair(-inf, inf); ///<val, pos>
    int left = Tree[now].left, right = Tree[now].right;
    if(qleft <= left && right <= qright){
        return make_pair(Tree[now].maxv, Tree[now].pos);
    }
    int mid = left + right >> 1;
    if(qleft <= mid){
        pii nxt = query(qleft, qright, now << 1);
        f(ret, nxt);
    }
    if(qright > mid){
        pii nxt = query(qleft, qright, now << 1 | 1);
        f(ret, nxt);
    }
    return ret;
}

ll inv(ll x){
    return x == 1 ? 1 : (mod - mod / x) * inv(mod % x) % mod;
}

void q(int l = 1, int r = n){
    if(l > r)return;
    int pos = query(l, r).second;
    //printf("pos = %d\n", pos);
    ans = ans * inv(r - l + 1) % mod;
    q(l, pos-1);
    q(pos + 1, r);
}

int main(){
    scanf("%d", &T);
    while(T --){
        scanf("%d", &n);
        for(int i = 1; i <= n; ++ i){
            scanf("%d", a + i);
        }
        build();
        //printf("built\n");
        ans = n;
        ans = ans * inv(2) % mod;
        //printf("before q()\n");
        q();
        //printf("after q()\n");
        printf("%lld\n", ans);
    }
    return 0;
}