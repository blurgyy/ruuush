#include<bits/stdc++.h>
using namespace std;
const int maxn = 110;
const int INF = 0x3f3f3f3f;

int n, a[maxn];

int check(int pos){
    int ans = 0;
    int work[maxn] = {0};
    work[pos] = a[pos];
    for(int i = pos-1; i > 0; -- i){
        //if(a[i] == 3 || (a[i] | a[i+1]) != a[i+1])
        if(work[i+1] == 2 && (a[i] == 1 || a[i] == 3) || work[i+1] == 1 && (a[i] == 2 || a[i] == 3))
            work[i] = (work[i+1] == 1 ? 2 : 1);
    }
    for(int i = pos+1; i <= n; ++ i){
        //if(a[i] == 3 || (a[i] | a[i-1]) != a[i-1])
        if(work[i-1] == 2 && (a[i] == 1 || a[i] == 3) || work[i-1] == 1 && (a[i] == 2 || a[i] == 3))
            work[i] = (work[i-1] == 1 ? 2 : 1);
    }
    /*
    for(int i = 1; i <= n; ++ i)
        printf("%d ",work[i]);
    printf("\n");
    */
    for(int i = 1; i <= n; ++ i)
        ans += !(work[i]);
    return ans;
}

int main(){
    while(~scanf("%d", &n)){
        int ans = INF;
        for(int i = 1; i <= n; ++ i)
            scanf("%d", a + i);
        for(int i = 1; i <= n; ++ i)
            if(a[i] == 1 || a[i] == 2){
                //printf("check(%d) = %d\n", i, check(i));
                ans = min(ans, check(i));
            }
        printf("%d\n", ans);
    }
    return 0;
}

/**

7
1 3 3 2 1 2 3

6
2 2 1 1 2 2

100
0 2 0 3 3 1 3 3 3 3 2 1 1 2 1 2 3 1 0 0 1 2 3 2 0 0 0 2 0 3 3 0 1 3 2 3 1 3 1 2 1 3 2 1 3 3 0 0 1 1 1 3 1 1 0 2 0 0 0 3 1 3 2 2 0 0 1 0 2 1 0 3 2 0 0 0 0 0 2 2 1 1 3 3 0 1 2 1 0 1 2 2 1 2 1 3 3 1 0 1

*/