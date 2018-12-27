#include <bits/stdc++.h>
using namespace std;
const int maxn = 110;

int T, n;
char s[5];
double a[maxn];

int main(){
    scanf("%d", &T);
    while(T --){
        scanf("%d%s", &n, s);
        double ans = 0;
        for(int i = 0; i < n; ++ i){
            scanf("%lf", a + i);
            if(a[i] == 0.0){
                continue;
            }
            if(s[0] == 'b'){
                ans += a[i] * log2(100.0/a[i]) / 100.0;
            }
            else if(s[0] == 'n'){
                ans += a[i] * log(100.0/a[i]) / 100.0;
            }
            else {
                ans += a[i] * log10(100.0/a[i]) / 100.0;
            }
        }
        printf("%.12f\n", ans);
    }
    return 0;
}