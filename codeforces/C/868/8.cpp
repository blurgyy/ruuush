#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int n, k, in;
bool rec[16];

int main(){
    while(~scanf("%d%d", &n, &k)){
        int tmp;
        for(int i = 1; i <= n; ++ i){
            tmp = 0;
            for(int j = 1; j <= k; ++ j){
                scanf("%d", &in);
                tmp <<= 1;
                if(in)tmp |= 1;
            }
            rec[tmp] = true;
        }
        for(int i = 0; i < 16; ++ i){
            if(rec[i]){
                int m = ~i;
                for(int j = 0; j < 16; ++ j){
                    //printf("j = %d, m = %d, %d\n", j, m, j|m);
                    if((m|j) != m)continue;
                    if(rec[j]){
                        printf("YES\n");
                        return 0;
                    }
                }
            }
        }
        printf("NO\n");
    }
    return 0;
}