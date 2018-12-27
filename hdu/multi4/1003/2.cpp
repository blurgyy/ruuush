#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#define LL long long
#define pb push_back
using namespace std;

const int N = 1e6 + 7;
const int MOD = 998244353;

vector<int> V;
vector<int> ha[N];
int not_prime[N];
LL sq[N];
LL l ,r, k;

int pr()
{
    memset(not_prime, 0, sizeof(not_prime));
    for (LL i = 2; i < 1000000; ++ i){
        if (!not_prime[i]){
            V.pb(i);
            if (i * i <= 1000000){
                for (LL j = i + i; j <= 1000000; j += i){
                    not_prime[j] = 1;
                }
            }
        }
    }
}

LL g(LL x)
{
    LL ans = 1;
    LL cnt;
    LL p = x - l;
    int limit = ha[p].size();
    LL t = x;

    /*printf("%lld\n", x);

    getchar();*/
    for(int i = 0; i < limit; ++ i){
        //if(t == 1) break;
        cnt = 0;
        while(t % ha[p][i] == 0){
            cnt ++;
            t /= ha[p][i];
            //printf("%d %lld\n", ha[p][i], t);
        }
        //printf("ha = %d\n", ha[p][i]);
        //printf("cnt = %lld\n", cnt);
        ans = (ans * (cnt * k + 1)) % MOD;
    }
    if(t != 1){
        ans = (ans * (k + 1)) % MOD;
    }

    //printf("%lld %lld\n", x, ans);

    return ans;
}



int main()
{
    int ncase;
    int limit;
    ///1
    pr();
    limit = V.size();
    /*k = 1;
    for(int i = 1; i <= 100; i ++){
        printf("%d %lld\n", i, g(i));
    }*/
    //cout << V[V.size() - 1] << endl;
    scanf("%d", &ncase);
    while(ncase --){
        LL ans = 0;
        LL su;

        scanf("%lld%lld%lld", &l, &r, &k);
        su = r - l + 1;
        //cout << su << endl;
        for(int i = 0; V[i] * V[i] <= r && i < limit; ++ i){
            for(LL j = (V[i] - l % V[i]) % V[i]; j < su; j += V[i]){
                //printf("%lld %d\n", j, V[i]);
                //getchar();
                ha[j].pb(V[i]);
            }
        }
        for(LL i = l; i <= r; ++ i){
            ans = (ans + g(i)) % MOD;
        }
        printf("%lld\n", ans);
        for(int i = 0; i < su; ++ i){
            ha[i].resize(0);
        }
    }

    return 0;
}

/**

431981875 432981875 16482
77214900 78214900 27040
213840060 214840060 6901
301583726 302583726 12560
2335992 3335992 32582

604461970 605461970 30020
723064923 724064923 13492
27896082 28896082 1827
359563617 360563617 24565
217334976 218334976 6544

700204778 701204778 29706
723007292 724007292 6651
271793601 272793601 22376
280468044 281468044 9049
21914256 22914256 19476

*/
