#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;

int n;
int c[maxn];
int p[maxn];
int rec[8];
char in[5];

int min(int a, int b, int c, int d){
    return min(min(a, b), min(c, d));
}

int main(){
    while(~scanf("%d", &n)){
        memset(p, 0, sizeof(p));
        for(int i = 0; i < 8; ++ i){
            rec[i] = 10000000;
        }
        for(int i = 1; i <= n; ++ i){
            scanf("%d%s", c + i, in);
            int len = strlen(in);
            for(int j = 0; j < len; ++ j){
                if(in[j] == 'A'){
                    p[i] |= 1;
                }
                if(in[j] == 'B'){
                    p[i] |= 2;
                }
                if(in[j] == 'C'){
                    p[i] |= 4;
                }
            }
            rec[p[i]] = min(rec[p[i]], c[i]);
        }
        //for(int i = 1; i <= n; ++ i){
        //    printf("p[%d] = %d\n", i, p[i]);
        //}
        //for(int i = 1; i <= 8; ++ i){
        //    printf("rec[%d] = %d\n", i, rec[i]);
        //}
        rec[3] = min(rec[3], rec[1] + rec[2]);
        rec[5] = min(rec[5], rec[1] + rec[4]);
        rec[6] = min(rec[6], rec[2] + rec[4]);
        rec[7] = min(rec[7], rec[3] + rec[4], rec[5] + rec[2], rec[6] + rec[1]);
        rec[7] = min(rec[7], rec[3] + rec[5], rec[3] + rec[6], rec[5] + rec[6]);
        rec[7] = min(rec[7], rec[1] + rec[2] + rec[4]);
        if(rec[7] >= 10000000){
            rec[7] = -1;
        }
        printf("%d\n", rec[7]);
    }
    return 0;
}