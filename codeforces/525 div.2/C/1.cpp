#include <bits/stdc++.h>
using namespace std;
const int maxn = 2010;

int n;
int a[maxn];

int main(){
    while(~scanf("%d", &n)){
        for(int i = 0; i < n; ++ i){
            scanf("%d", a + i);
        }
        printf("%d\n", n + 1);
        printf("2 %d 1\n", n);
        printf("1 %d 10000\n", n);
        for(int i = 1; i < n; ++ i){
            printf("2 %d %d\n", i, 10000-i);
        }
    }
    return 0;
}