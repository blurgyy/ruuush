#include <cstdio>
#include <cmath>
#include <map>
const int maxn = 1000010;
const double eps = 1e-8;
using namespace std;

int n;
map<int, int> pf;

int lowbit(int x){
    return x & (-x);
}

int main(){
    while(~scanf("%d", &n)){
        pf.clear();
        if(n == 1){
            printf("1 0\n");
            continue;
        }
        int tmp = n;
        for(int i = 2; i <= tmp; ++ i){
            while(tmp % i == 0){
                pf[i] ++;
                tmp /= i;
            }
        }
        int ans = 1;
        int maxx = pf.begin()->second;
        int t = 0;
        // for(auto i = pf.begin(); i != pf.end(); ++ i){
        //     printf("%d %d\n", i->first, i->second);
        // }
        for(auto i = pf.begin(); i != pf.end(); ++ i){
            ans *= i->first;
            maxx = max(maxx, i->second);
        }
        if(lowbit(maxx) == maxx){
            t = log2(maxx) + eps;
            for(auto i = pf.begin(); i != pf.end(); ++ i){
                if(maxx != i->second){
                    ++ t;
                }
            }
        }
        else {
            t = 1;
            t += log2(maxx) + eps + 1;
        }
        // printf("maxx = %d, lb(%d), t = %d\n", maxx, lowbit(maxx), t);
        // t += log2(maxx) + eps;
        // if(lowbit(maxx) == maxx);
        // else ++ t;
        printf("%d %d\n", ans, t);
    }
    return 0;
}