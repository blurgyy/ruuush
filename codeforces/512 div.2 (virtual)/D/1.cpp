#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 3e7;

ll n, m, k;
int pri[maxn];
int totprime;
bool v[maxn];
map<int, int> np, mp, kp;

int init_prime(int n, int pri[]){
    int k = 0;
    int i,q;

    for(i = 2,q = sqrt(n)+1; i < q; i++)
    {
        if(!v[i])
        {
            pri[k++] = i;
            for(int j = i<<1; j <= n; j+=i){
                v[j] = true;
            }
        }
    }
    for(;i <= n; i++){
        if(!v[i]){
            pri[k++] = i;
        }
    }
    return k;
}

void dsmt(){
    ll a = n, b = m, c = k;
    for(int i = 0; i < totprime; ++ i){
        int now = pri[i];
        while(a % now == 0){
            np[now] ++;
            a /= now;
        }
        while(b % now == 0){
            mp[now] ++;
            b /= now;
        }
        while(c % now == 0){
            kp[now] ++;
            c /= now;
        }
    }
}

int main(){
    while(~scanf("%I64d%I64d%I64d", &n, &m, &k)){
        np.clear();
        mp.clear();
        kp.clear();
        totprime = init_prime(max(max(n, m), k), pri);
        //for(int i = 0; i < totprime; ++ i){
        //    printf("%d ", pri[i]);
        //}
        //printf("\n");
        dsmt();
        ll totarea = n * m;
        if(totarea * 2 % k){
            printf("NO\n");
            continue;
        }
        printf("YES\n");
        for(auto i = kp.begin(); i != kp.end(); ++ i){
            int side = 0;
            int curprime = i->first;
            printf("curprime = %d\n", curprime);
            while(i->second && np[curprime] && mp[curprime]){
                if(side){
                    np[curprime] --;
                }
                else {
                    mp[curprime] --;
                }
                i->second --;
            }
            while(i->second && np[curprime]){
                np[curprime] --;
                i->second --;
            }
            while(i->second && mp[curprime]){
                mp[curprime] --;
                i->second --;
            }
        }
        ll ans1 = 1, ans2 = 1;
        for(auto i = np.begin(); i != np.end(); ++ i){
            printf("(%d, %d)", i->first, i->second);
            while(i->second){
                ans1 *= i->first;
                i->second --;
            }
        }
        printf("\n");
        for(auto i = mp.begin(); i != mp.end(); ++ i){
            printf("(%d, %d)", i->first, i->second);
            while(i->second){
                ans2 *= i->first;
                i->second --;
            }
        }
        printf("\n");
        if(kp[2]){
            if(ans1 & 1){
                ans2 /= 2;
            }
            else {
                ans1 /= 2;
            }
        }
        printf("%I64d %I64d %I64d %I64d %I64d %I64d\n", (ll)0, (ll)0, (ll)0, (ll)ans1, (ll)ans2, (ll)0);
    }
    return 0;
}