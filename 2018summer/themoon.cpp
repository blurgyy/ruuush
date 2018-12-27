//?!??
#include <bits/stdc++.h>
using namespace std;
const int maxn = 310;
const double eps = 1e-8;

int p;
double dp[maxn];

int idx(double q){
    int ret = q * 2 + eps;
    //printf("q = %f, ret = %d\n", q, ret);
    return ret;
}

int main(){
    while(~scanf("%d", &p)){
        for(int i = 0; i < maxn; ++ i){
            dp[i] = 0;
        }
        dp[idx(100)] = 100.0 / p;
        printf("all = %f\n", dp[idx(100)]);
        double q = 99.5;// q
        while(q >= 2){
            double win = min(100.0, q + 2.0);
            double lose = min(100.0, q + 1.5);
            //printf("win = %f, lose = %f\n", win, lose);
            int id = idx(q);
            dp[id] = 0;
            dp[id] += (p/100.0) * ((q/100.0) * 1.0 + (1 - q/100.0) * dp[idx(win)]);
            dp[id] += (1 - p/100.0) * dp[idx(lose)];
            printf("dp[%d] = %f\n", id, dp[id]);
            q -= 0.5;
        }
        printf("ans = %f\n", dp[idx(2.0)]);
    }
    return 0;
}