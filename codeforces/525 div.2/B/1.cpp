#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int n, k;
int a[maxn];

int main(){
    a[0] = 0;
    while(~scanf("%d%d", &n, &k)){
        for(int i = 1; i <= n; ++ i){
            scanf("%d", a + i);
        }
        sort(a+1, a+1 + n);
        int tot = unique(a+1, a+1 + n) - (a + 1);
        for(int i = 1; i <= k; ++ i){
            if(i <= tot){
                printf("%d\n", a[i] - a[i-1]);
            }
            else {
                printf("0\n");
            }
        }
    }
    return 0;
}