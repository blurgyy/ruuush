#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 100;
const int maxp = 10000010;
const int mod = 998244353;

int T, n, l, r;
int a[maxn];
ll x[maxp];
ll pref[maxp];

bool cmp(int x, int y){return x > y;}

int main(){
    // freopen("in.in", "r", stdin);
    scanf("%d", &T);
    while(T --){
        scanf("%d%d%d", &n, &l, &r);
        for(int i = 1; i <= n; ++ i){
            scanf("%d", a + i);
        }
        sort(a+1, a+1+n);//, cmp);
        x[0] = pref[0] = 1;
        /*dsafshgdfsdscx*//*
        for(int i = 2; i <= n; ++ i){
            for(int j = r; j >= 1; -- j){
                if(j - a[i] - 1 < 0) x[j] = pref[j];
                else x[j] = (pref[j] - pref[j-a[i]-1] + mod) % mod;
            }
            for(int j = 1; j <= r; ++ j){
                pref[j] = (pref[j-1] + x[j]) % mod;
            }
            for(int j = 0; j <= r; ++ j){
                printf("%lld%c", x[j], " \n"[j==r]);
            }
            for(int j = 0; j <= r; ++ j){
                printf("%lld%c", pref[j], " \n"[j==r]);
            }
        }
    }
    return 0;
}