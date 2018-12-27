#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 100010;
const int maxlog = 20;
const ll inf = 0x3f3f3f3f3f3f3f3f;

int T, k;
struct entry{
    int tup[2], pos;
    entry(){tup[0] = tup[1] = pos = 0;}
    bool operator< (entry a){return tup[0] == a.tup[0] ? tup[1] < a.tup[1] : tup[0] < a.tup[0];}
    bool operator==(entry a){return tup[0] == a.tup[0] && tup[1] == a.tup[1];}
}sa[maxn];
struct STN{
    int left, right;
    int val;
}Tree[maxn<<2];
int rk[maxlog][maxn], lcp[maxn];
int stp, len;
char s[maxn];

int calc(int pos){
    int i, j;
    for(i = sa[pos].pos, j = sa[pos-1].pos; i < len && j < len; ++ i, ++ j)
        if(s[i] != s[j])break;
    return i - sa[pos].pos;
}

void getsa(char s[]){
    memset(lcp, 0, sizeof(lcp));
    len = strlen(s);
    for(int i = 0; i < len; ++ i)
        rk[0][i] = s[i] - 'a';
    stp = 1;
    for(int ext = 1; ext >> 1 < len; ++ stp, ext <<= 1){
        for(int i = 0; i < len; ++ i){
            sa[i].tup[0] = rk[stp-1][i];
            if(i + ext < len)
                sa[i].tup[1] = rk[stp-1][i+ext];
            else 
                sa[i].tup[1] = -1;
            sa[i].pos = i;
        }
        sort(sa, sa + len);
        for(int i = 0; i < len; ++ i){
            if(i > 0 && sa[i] == sa[i-1])
                rk[stp][sa[i].pos] = rk[stp][sa[i-1].pos];
            else 
                rk[stp][sa[i].pos] = i;
        }
    }
    -- stp;
    for(int i = 1; i < len; ++ i)
        lcp[i] = calc(i);
}

void pushUp(int nowNode){
    Tree[nowNode].val = min(Tree[nowNode<<1].val, Tree[nowNode<<1|1].val);
}

void build(int left = 1, int right = len, int nowNode = 1){
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    if(left == right){
        Tree[nowNode].val = lcp[right];
        return;
    }
    int mid = left + right >> 1;
    build(left, mid, nowNode << 1);
    build(mid + 1, right, nowNode << 1 | 1);
    pushUp(nowNode);
}

ll query(int qleft, int qright, int nowNode = 1){
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    //printf("left = %d, right = %d\n", left, right);
    if(qleft <= left && right <= qright)
        return Tree[nowNode].val;
    int mid = left + right >> 1;
    ll ret = inf;
    if(qleft <= mid)ret = min(ret, query(qleft, qright, nowNode << 1));
    if(qright > mid)ret = min(ret, query(qleft, qright, nowNode << 1 | 1));
    return ret;
}

int main(){
    freopen("in.in", "r", stdin);
    scanf("%d", &T);
    while(T --){
        scanf("%d%s", &k, s);
        getsa(s);
        build();
        ll ans = 0;
        for(int i = 0; i < len; ++ i)
            printf("%s\n", s + sa[i].pos);
        for(int i = 0; i < len; ++ i)
            printf("%d ", lcp[i]);
        printf("\n");
        ll ans1 = 0, ans2 = 0;
        for(int i = 1; i + k <= len; ++ i){
            ans1 += query(i, i + k - 2);
            ans2 += query(i, i + k - 1);
        }
        printf("%lld\n", ans1 - ans2);
    }
    return 0;
}