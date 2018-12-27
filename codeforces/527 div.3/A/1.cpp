#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int n, k;
int T;

int main(){
    scanf("%d", &T);
    while(T --){
        scanf("%d%d", &n, &k);
        for(int i = 0; i < n; ++ i){
            printf("%c", 'a' + i%k);
        }
        printf("\n");
    }
    return 0;
}