#include<bits/stdc++.h>
using namespace std;
const int maxn = 300010;

int n, a[maxn], p, top;

int main(){
    //freopen("out.out", "w", stdout);
    while(~scanf("%d", &n)){
        printf("1");
        memset(a, 0, sizeof(a));
        top = n;
        for(int i = 1; i <= n; ++ i){
            scanf("%d", &p);
            a[p] = 1;
            for(int j = top; j >= 0; -- j){
                if(a[j] == 0){
                    top = j;
                    break;
                }
            }
            int pile = n - top;
            printf(" %d", i - pile + 1);
        }
        printf("\n");
    }
    return 0;
}

/**

4 1 3 4 2

8 6 8 3 4 7 2 1 5

*/