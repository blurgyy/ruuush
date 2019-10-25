#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 100010;

int n;
int m[maxn];
double A;
double ans[maxn];

int main(){
    while(~scanf("%d%lf", &n, &A)){
        for(int i = 1; i <= n; ++ i){
            scanf("%d", m + i);
        }
        for(int i = 1; i <= n; ++ i){
            int top = 1.0 * i * A;
            ans[i] = 0;
            for(int j = 1; j <= top; ++ j){
                ans[i] += 1.0 * m[j] / (i - j);
            }
        }
        for(int i = 1; i <= n; ++ i){
            printf("%f\n", ans[i] * m[i]);
        }
    }
    return 0;
}
