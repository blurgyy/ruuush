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
//        for(auto i = pf.begin(); i != pf.end(); ++ i){
//            printf("%d %d\n", i->first, i->second);
//        }
        for(auto i = pf.begin(); i != pf.end(); ++ i){
            ans *= i->first;
            maxx = max(maxx, i->second);
        }
        int add = 0;
        if(maxx != lowbit(maxx)){
            add = true;
        }
        else {
            for(auto i = pf.begin(); i != pf.end(); ++ i){
                if(i->second != maxx){
                    add = true;
                    break;
                }
            }
        }
        t = add + log2(maxx) + eps + (maxx != lowbit(maxx));
        // printf("maxx = %d, lb(%d), t = %d\n", maxx, lowbit(maxx), t);
        // t += log2(maxx) + eps;
        // if(lowbit(maxx) == maxx);
        // else ++ t;
        printf("%d %d\n", ans, t);
    }
    return 0;
}
