#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;

int n;
int a[maxn];

int main(){
    while(~scanf("%d", &n)){
        for(int i = 0; i < n; ++ i){
            scanf("%d", a + i);
        }
        sort(a, a + n);
        int tot = a[n-1] - a[0] + 1;
        printf("%d\n", tot - n);
    }
    return 0;
}