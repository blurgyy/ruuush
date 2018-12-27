///poj2796 - Solved

//#include<bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <time.h>
using namespace std;
typedef long long ll;
const int maxn = 100010;

int n;
ll a[maxn], pref[maxn];
pair<int, int> itv[maxn];
bool vis[maxn];
struct node{
    ll val;
    int pos;
}assis[maxn];

bool cmp(node a, node b){
    return a.val > b.val;
}

void inline upd(int pos){
    for(int i = itv[pos].first; i >= 0; -- i){
        i = itv[i].first;
        if(!vis[i-1]){
            itv[pos].first = i;
            break;
        }
    }
    for(int i = itv[pos].second; i <= n; ++ i){
        i = itv[i].second;
        if(!vis[i+1]){
            itv[pos].second = i;
            break;
        }
    }
}

int main(){
    /*freopen("in.in", "w", stdout);
    srand(time(NULL));
    int t = 50;
    while(t--){
        printf("100000\n");
        for(int i = 0; i < 100000; ++ i)
            printf("%d ", rand() % 1000000 + 1);
        printf("\n");
    }
    return 0;*/
    //freopen("in.in", "r", stdin);
    scanf("%d", &n);{
    //while(~scanf("%d", &n)){
        memset(vis, false, sizeof(vis));
        a[0] = pref[0] = 0;
        for(int i = 1; i <= n; ++ i){
            scanf("%lld", a + i);
            assis[i].val = a[i];
            assis[i].pos = i;
            itv[i].first = itv[i].second = i;
            pref[i] = pref[i-1] + a[i];
        }
        sort(assis + 1, assis + n + 1, cmp);
        ll ans = -1;
        int ansl, ansr;
        for(int i = 1; i <= n; ++ i){
            int pos = assis[i].pos;
            vis[pos] = true;
            for(int j = i + 1; j <= n; ++ j){
                if(vis[assis[j].pos] || assis[j].val != assis[j-1].val)break;
                vis[assis[j].pos] = true;
            }
            upd(pos);
            //printf("val = %lld, l = %d, r = %d\n", assis[i].val, itv[pos].first, itv[pos].second);
            ll sum = (pref[itv[pos].second] - pref[itv[pos].first-1]) * assis[i].val;
            //printf("sum = %d\n", sum);
            if(ans < sum){
                ans = sum;
                ansl = itv[pos].first;
                ansr = itv[pos].second;
            }
        }
        printf("%lld\n%d %d\n", ans, ansl, ansr);
    }
    return 0;
}
