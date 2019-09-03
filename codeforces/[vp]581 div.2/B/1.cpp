#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1010;

int n, l, r;
int a[maxn];

int main(){
    while(~scanf("%d%d%d", &n, &l, &r)){
        a[1] = 1;
        ll minsum = 1, maxsum = 1;
        for(int i = 2, cnt = 1; i <= n; ++ i){
            a[i] = a[i-1];
            if(cnt < l){
                a[i] *= 2;
                cnt ++;
                minsum += a[i];
            }
            else {
                minsum += 1;
            }
        }
        for(int i = 2, cnt = 1; i <= n; ++ i){
            a[i] = a[i-1];
            if(cnt < r){
                a[i] *= 2;
                cnt ++;
            }
            maxsum += a[i];
        }
        printf("%lld %lld\n", minsum, maxsum);
    }
    return 0;
}
