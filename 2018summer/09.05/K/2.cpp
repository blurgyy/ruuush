#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int maxn = 50010;
const int p1 = 1e9 + 7;
const int p2 = 1e9 + 9;
const int p3 = 998244353;
const int mod = 1004535809;
const char out3[2][110] = {"No true closed chains", "True closed chains"};
const char out2[2][110] = {"No floor closed chains", "Floor closed chains"};

struct Point{
    ll x, y, z;
    ll h2, h3;
    Point(int _x = 0, int _y = 0, int _z = 0){x = _x; y = _y; z = _z;}
    void out(){printf("(%I64d, %I64d, %I64d): h2 = %I64d, h3 = %I64d\n", x, y, z, h2, h3);}
    void in(){
        scanf("%I64d%I64d%I64d", &x, &y, &z);
        h2 = ha2();
        h3 = ha3();
        //out();
    }
    ll ha3(){return (((x * p2 % mod) + y * p1) % mod + z * p3) % mod;}
    ll ha2(){return ((x * p3 % mod) + y * p1) % mod;}
}pt[maxn][2];
int N;
map<pii, int> cnt2, cnt3;
int fa[maxn<<1];
bool ans2, ans3;

int find(int x){
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void unite(int x, int y){
    int t1 = find(x);
    int t2 = find(y);
    if(t1 == t2)return;
    fa[t1] = t2;
}

bool same(int x, int y){
    return find(x) == find(y);
}

int bs(ll e, ll arr[], int left, int right){
    if(left >= right)return right;
    int mid = (left + right) / 2;
    if(e <= arr[mid])return bs(e, arr, left, mid);
    return bs(e, arr, mid + 1, right);
    ///int ret = -1;
    ///if(left >= right)ret = right;
    ///printf("idx(%lld) = %d\n", e, ret);
    ///return ret;
    ///int mid = (left + right) / 2;
    ///if(e <= arr[mid])ret = bs(e, arr, left, right);
    ///else ret = bs(e, arr, mid + 1, right);
    ///printf("idx(%lld) = %d\n", e, ret);
    ///return ret;
}

void dsc(){
    ll assis[maxn<<1];
    int p = 0;
    for(int i = 0; i < N; ++ i){
        assis[p++] = pt[i][0].h2;
        assis[p++] = pt[i][1].h2;
    }
    sort(assis, assis + p);
    p = unique(assis, assis + p) - assis;
    for(int i = 0; i < N; ++ i){
        pt[i][0].h2 = bs(pt[i][0].h2, assis, 0, p - 1);
        pt[i][1].h2 = bs(pt[i][1].h2, assis, 0, p - 1);
    }
    p = 0;
    for(int i = 0; i < N; ++ i){
        assis[p++] = pt[i][0].h3;
        assis[p++] = pt[i][1].h3;
    }
    sort(assis, assis + p);
    p = unique(assis, assis + p) - assis;
    for(int i = 0; i < N; ++ i){
        pt[i][0].h3 = bs(pt[i][0].h3, assis, 0, p - 1);
        pt[i][1].h3 = bs(pt[i][1].h3, assis, 0, p - 1);
    }
}

void edgerec(pii x, int dim = 3){
    if(dim == 3){
        cnt3[x] ++;
    }
    else cnt2[x] ++;
}

void init(){
    //printf("INITIALIZATION\n");
    cnt2.clear();
    cnt2.clear();
    //memset(pt, 0, sizeof(pt));
    for(int i = 0; i < 100010; ++ i)fa[i] = i;
    ans2 = ans3 = false;
}

//#define fin
//#define fout

int main(){
    //Point a(970, 972, 841);
    //Point b(902, 490, 366);
    //printf("%lld, %lld\n", a.ha3(), b.ha3());
    //ll xx[] = {1, 2, 3, 4, 5, 6, 7, 9, 100, 424325, 43543676, 100000000};
    //for(int i = 0; i < 12; ++ i){
    //    printf("idx(%lld) = %d\n", xx[i], bs(xx[i], xx, 0, 11));
    //}
    //return 0;
    printf("mod = %d\n", mod);
    #ifdef fin
        freopen("in.in", "r", stdin);
    #endif
    #ifdef fout
        freopen("out.out", "w", stdout);
    #endif
    //memset(pt, 0, sizeof(pt));
    //while(~scanf("%d", &N)){
    scanf("%d", &N);{
        init();
        for(int i = 0; i < N; ++ i){
            pt[i][0].in();
            pt[i][1].in();
        }
        dsc();
        ///check();
        //for(int i = 0; i < N; ++ i){
        //    pt[i][0].out();
        //    pt[i][1].out();
        //    printf("\n");
        //}
        for(int i = 0; i < N; ++ i){
            int from = pt[i][0].h3;
            int to = pt[i][1].h3;
            if(from == to){
                continue;
            }
            int minx = min(from, to);
            int maxx = max(from, to);
            pii x = make_pair(minx, maxx);
            if(cnt3[x]){
                continue;
            }
            if(same(from, to)){
                //printf("3d: from = %d(%d), to = %d(%d)\n", from, find(from), to, find(to));
                ans3 = true;
                break;
            }
            unite(from, to);
            //printf("3d: %d and %d united\n", from, to);
            edgerec(x);
        }
        for(int i = 0; i < 100010; ++ i)fa[i] = i;
        for(int i = 0; i < N; ++ i){
            int from = pt[i][0].h2;
            int to = pt[i][1].h2;
            if(from == to){
                continue;
            }
            int minx = min(from, to);
            int maxx = max(from, to);
            pii x = make_pair(minx, maxx);
            if(cnt2[x]){
                continue;
            }
            if(same(from, to)){
                //printf("2d: from = %d, to = %d\n", from, to);
                ans2 = true;
                break;
            }
            unite(from, to);
            //printf("2d: %d and %d united\n", from, to);
            edgerec(x, 2);
        }
        printf("%s\n%s\n", out3[ans3], out2[ans2]);
    }
    return 0;
}