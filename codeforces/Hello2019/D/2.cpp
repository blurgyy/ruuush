// Editorial: https://codeforces.com/blog/entry/64310
// Unsolved

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 10010;
const int mod = 1e9 + 7;

ll n;
int k;
ll fac[maxn];
int totfac;
map<ll, int> pfac;
map<ll, int> cnt;
ll ans[maxn];
vector<int> rec[maxn];

ll inv(int n){
    if(n == 1) return 1;
    return 1ll * (mod - mod / n) * inv(mod % n) % mod;
}

void get_fac(ll n, ll arr[] = fac){
    int p = 0;
    totfac = 0;
    ll top = sqrt(n) + 1;
    for(ll i = 1; i <= top; ++ i){
        if(n % i == 0){
            fac[p++] = i;
            fac[p++] = n / i;
        }
    }
    // printf("p = %d\n", p);
    sort(fac, fac + p);
    totfac = unique(fac, fac + p) - fac;
}

void p_div(ll n, map<ll, int> &pfac){
    pfac.clear();
    ll top = sqrt(n) + 1;
    for(ll i = 2; i <= top; ++ i){
        while(n % i == 0){
            n /= i;
            pfac[i] ++;
        }
    }
    if(n != 1){
        pfac[n] ++;
    }
}

void out(map<ll, int> x){
    for(auto i = x.begin(); i != x.end(); ++ i){
        printf("%lld %d\n", i->first, i->second);
    }
}

int main(){
    while(~scanf("%lld%d", &n, &k)){
        cnt.clear();
        for(int i = 0; i < maxn; ++ i) rec[i].clear();
        get_fac(n);
        // printf("%d m\n", totfac);
        p_div(n, pfac);
        cnt[1] = 1;
        cnt[n] = totfac;
        for(int i = 0; i < totfac; ++ i){
            if(cnt[fac[i]] != 0) continue;
            cnt[fac[i]] = cnt[n/fac[i]] = 1;
            map<ll, int> tmp;
            p_div(fac[i], tmp);
            // for(auto j = tmp.begin(); j != tmp.end(); ++ j){
            //     ll prm = j->first;
            //     int pw = j->second;
            //     cnt[fac[i]] *= pw + 1;
            //     cnt[n/fac[i]] *= (pfac[prm] - pw) + 1;
            // }
            for(auto j = pfac.begin(); j != pfac.end(); ++ j){
                ll prm = j->first;
                int pw = j->second - tmp[prm];
                cnt[n/fac[i]] *= pw + 1;
                cnt[fac[i]] *= (pfac[prm] - pw) + 1;
            }
        }
        // out(cnt);
        // printf("totfac = %d\n", totfac);
        ll inv_tot = inv(totfac);
        for(int i = 0; i < totfac; ++ i){
            ans[i] = inv_tot;
        }
        for(int i = 1; i < k; ++ i){
            if(i == 1){
                // printf("i = %d\n", i);
                for(int j = 0; j < totfac; ++ j){
                    ans[j] = ans[j] * inv(cnt[fac[j]]) % mod;
                    for(int kk = j+1; kk < totfac; ++ kk){
                        if(fac[kk] % fac[j] == 0){
                            rec[j].push_back(kk);
                            ans[j] = (ans[j] + ans[kk] * inv(cnt[fac[kk]]) % mod) % mod;
                            // printf("cnt[%lld] = %d\n", fac[kk], cnt[fac[kk]]);
                            // printf("%d ", kk);
                        }
                    }
                    // printf("\n");
                    // printf("!!ans[%lld] = %lld, (%lld)\n", fac[j], ans[j], fac[j] * ans[j] % mod);
                }
            }
            else {
                // printf("i = %d\n", i);
                for(int j = 0; j < totfac; ++ j){
                    ans[j] = ans[j] * inv(cnt[fac[j]]) % mod;
                    int lim = rec[j].size();
                    for(int kk = 0; kk < lim; ++ kk){
                        ans[j] = (ans[j] + ans[rec[j][kk]] * inv(cnt[fac[rec[j][kk]]]) % mod) % mod;
                        // printf("%d ", rec[j][kk]);
                    }
                    // printf("\n");
                    // printf("________ans[%lld] = %lld\n", fac[j], ans[j]);
                }
            }
        }
        ll final_ans = 0;
        for(int i = 0; i < totfac; ++ i){
            final_ans = (final_ans + fac[i] * ans[i] % mod) % mod;
        }
        printf("%lld\n", final_ans);
    }
    return 0;
}