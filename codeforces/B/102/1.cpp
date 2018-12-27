#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;

char n[maxn];

int main(){
    while(~scanf("%s", n)){
        int ans = maxn;
        int cnt = 0;
        if(strlen(n) < 2){
            printf("0\n");
            continue;
        }
        while(9 < ans){
            ++ cnt;
            ans = 0;
            int len = strlen(n);
            for(int i = 0; i < len; ++ i)
                ans += n[i] - '0';
            //printf("ans = %d, n = %s\n", ans, n);
            int tmp = ans, p = 0;
            while(tmp){
                //printf("tmp = %d\n", tmp);
                n[p++] = tmp % 10 + '0';
                tmp /= 10;
                //system("pause");
            }
            n[p++] = 0;
        }
        printf("%d\n", cnt);
    }
    return 0;
}