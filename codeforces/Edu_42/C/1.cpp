#include<bits/stdc++.h>
using namespace std;
const int maxn = 10010;

char n[30];
int rec[maxn], p;

int power(int lev){
    return 1 << lev;
}

int sq(int a){
    return a * a;
}

int getlen(int x){
    int ret = 1;
    while(x/=10)++ ret;
    return ret;
}

int main(){
    while(~scanf("%s", n)){
        p = 0;
        int len = strlen(n), top = power(len);
        for(int i = 1; i < top; ++ i){
            int now = 0;
            //for(int j = 0, lev = 1; j < len; ++ j){
            for(int j = len-1, lev = 1; j >= 0; -- j){
                if((1 << j) & i){
                    now += lev * (n[j] - '0');
                    lev *= 10;
                }
            }
            rec[p++] = now;
        }
        /*
        for(int i = 0; i < p; ++ i)
            printf("%d ", rec[i]);
        printf("\n");
        */
        //printf("%d %d\n", getlen(234), getlen(1));
        int ans = -1;
        for(int i = 0; i < p; ++ i){
            if(sq(sqrt(rec[i])) == rec[i])
                ans = max(ans, rec[i]);
        }
        //printf("ans = %d\n", ans);
        if(ans == 0)ans = -1;
        if(ans != -1)
            ans = len - getlen(ans);
        printf("%d\n", ans);
    }
    return 0;
}