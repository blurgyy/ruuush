#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100010;
const int maxlog = 20;
const int inf = 0x3f3f3f3f;

struct entry{
    int tup[2], pos;
    bool operator< (entry a){return tup[0] == a.tup[0] ? tup[1] < a.tup[1] : tup[0] < a.tup[0];}
    bool operator==(entry a){return tup[0] == a.tup[0] && tup[1] == a.tup[1];}
}sa[maxn];
int stp, len;
int rk[maxlog][maxn], height[maxn];
char s[maxn];
int T, k;

entry tmp[maxn];
int assis[maxn];
void rsort(entry arr[], int len){
    memset(assis, 0, sizeof(assis));
    for(int i = 0; i < len; ++ i);
}

int calc(int pos){
    int i, j;
    for(i = sa[pos].pos, j = sa[pos-1].pos; i < len && j < len; ++ i, ++ j)
        if(s[i] != s[j])break;
    return i - sa[pos].pos;
}

void getsa(char *s){
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
        for(int i = 0; i < len; ++ i)
            if(i > 0 && sa[i] == sa[i-1])
                rk[stp][sa[i].pos] = rk[stp][sa[i-1].pos];
            else 
                rk[stp][sa[i].pos] = i;
    }
    -- stp;
    for(int i = 1; i < len; ++ i)
        height[i] = calc(i);
}

struct STN{
    int left, right;
    int val;
}Tree[maxn<<2];

void pushUp(int nowNode){
    Tree[nowNode].val = min(Tree[nowNode<<1].val, Tree[nowNode<<1|1].val);
}

void build(int left = 1, int right = len - 1, int nowNode = 1){
    //printf("node(%d): %d to %d\n", nowNode, left, right);
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    if(left == right){
        Tree[nowNode].val = height[right];
        return;
    }
    int mid = left + right >> 1;
    build(left, mid, nowNode << 1);
    build(mid + 1, right, nowNode << 1 | 1);
    pushUp(nowNode);
}

int query(int qleft, int qright, int nowNode = 1){
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    //printf("inquery(%d to %d): %d to %d\n", qleft, qright, left, right);
    if(qleft <= left && right <= qright)
        return Tree[nowNode].val;
    int ret = inf;
    int mid = left + right >> 1;
    if(qleft <= mid)ret = min(ret, query(qleft, qright, nowNode << 1));
    if(qright > mid)ret = min(ret, query(qleft, qright, nowNode << 1 | 1));
    return ret;
}

int lcp(int left, int right){//left: 0 ~ len-2    right: 0 ~ len-1
    return query(left + 1, right);
}

int main(){
    //freopen("in.in", "r", stdin);
    scanf("%d", &T);
    while(T --){
        scanf("%d%s", &k, s);
        getsa(s);
        build();
        int ans = 0;
        for(int i = 0, right = i + k - 1; right < len; ++ i, ++ right){
            int lans = 0, rans = 0;
            if(i > 0){
                lans = lcp(i-1, right);
            }
            if(right < len - 1){
                rans = lcp(i, right + 1);
            }
            //printf("(%d) lans = %d, rans = %d\n", lcp(i, right), lans, rans);
            ans += lcp(i, right) - lans - rans;
            if(i > 0 && right < len-1){
                //printf("ans!! %d\n", lcp(i, right));
                ans += lcp(i-1, right+1);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}