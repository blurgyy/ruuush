#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int maxn = 50010;
const int p1 = 1e9 + 7;
const int p2 = 1e9 + 9;
const int p3 = 998244353;
const int mod = 1000003;

struct Point{
    ll x, y, z;
    ll h2, h3;
    void out(){
        printf("(%lld, %lld, %lld): h2 = %lld, h3 = %lld\n", x, y, z, h2, h3);
    }
    void in(){
        scanf("%lld%lld%lld", &x, &y, &z);
        h2 = ha2();
        h3 = ha3();
        //out();
    }
    ll ha3(){
        return ((((x * p1) % mod + y) * p2 % mod) + z)* p3 % mod;
    }
    ll ha2(){
        return ((x * p1) % mod + y) * p3 % mod;
    }
}pt[2][maxn];
int k;
int fa[maxn];
ll assis[maxn<<1];
bool ans2, ans3;
map<pii, int> cnt2, cnt3;

int bs(ll e, ll arr[], int left, int right){
    if(left >= right)return right;
    int mid = (left + right) / 2;
    if(e <= arr[mid])return bs(e, arr, left, mid);
    return bs(e, arr, mid + 1, right);
}

void init(){
    for(int i = 0; i < maxn; ++ i)fa[i] = i;
}

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

int main(){
    while(~scanf("%d", &k)){
        ans2 = ans3 = false;
        cnt2.clear();
        cnt3.clear();
        init();
        for(int i = 0; i < k; ++ i){
            pt[0][i].in();
            pt[1][i].in();
        }
        int p = 0;
        for(int i = 0; i < k; ++ i){
            assis[p++] = pt[0][i].h3;
            assis[p++] = pt[1][i].h3;
        }
        sort(assis, assis + p);
        int all = unique(assis, assis + p) - assis;
        for(int i = 0; i < k; ++ i){
            pt[0][i].h3 = bs(pt[0][i].h3, assis, 0, all - 1);
            pt[1][i].h3 = bs(pt[1][i].h3, assis, 0, all - 1);
        }
        for(int i = 0; i < k; ++ i){
            int p1 = pt[0][i].h3;
            int p2 = pt[1][i].h3;
            if(same(p1, p2) && p1 != p2){
                ans3 = true;
                break;
            }
            if(p1 == p2){
                int minx = min(p1, p2);
                int maxx = max(p1, p2);
                pii x = make_pair(minx, maxx);
                cnt3[x] ++;
                if(cnt3[x] >= 3){
                    ans3 = true;
                    break;
                }
            }
            unite(p1, p2);
        }
        init();
        p = 0;
        for(int i = 0; i < k; ++ i){
            assis[p++] = pt[0][i].h2;
            assis[p++] = pt[1][i].h2;
        }
        sort(assis, assis + p);
        all = unique(assis, assis + p) - assis;
        for(int i = 0; i < k; ++ i){
            pt[0][i].h2 = bs(pt[0][i].h2, assis, 0, all - 1);
            pt[1][i].h2 = bs(pt[1][i].h2, assis, 0, all - 1);
        }

        for(int i = 0; i < k; ++ i){
            pt[0][i].out();
            pt[1][i].out();
        }

        for(int i = 0; i < k; ++ i){
            int p1 = pt[0][i].h2;
            int p2 = pt[1][i].h2;
            if(same(p1, p2) && p1 != p2){
                ans2 = true;
                break;
            }
            if(p1 == p2){
                int minx = min(p1, p2);
                int maxx = max(p1, p2);
                pii x = make_pair(minx, maxx);
                cnt2[x] ++;
                if(cnt2[x] >= 3){
                    ans2 = true;
                    break;
                }
            }
            printf("%d and %d united\n", p1, p2);
            unite(p1, p2);
        }
        printf("%d\n%d\n", ans3, ans2);
    }
    return 0;
}