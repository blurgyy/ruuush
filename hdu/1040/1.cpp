#include <bits/stdc++.h>
using namespace std;

int main(){
    int T, n;
    int a[100010];
    scanf("%d", &T);
    while(T --){
        scanf("%d", &n);
        for(int i = 0; i < n; ++ i){
            scanf("%d", a + i);
        }
        sort(a, a + n);
        for(int i = 0; i < n; ++ i){
            printf("%d%c", a[i], " \n"[i == n-1]);
        }
    }
    return 0;
}