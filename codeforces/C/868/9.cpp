#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int n, k;
int in;
bool rec[16];

int main(){
    while(~scanf("%d%d", &n, &k)){
        memset(rec, 0, sizeof(rec));
        while(n--){
            int tmp = 0;
            for(int i = 1; i <= k; ++ i){
                scanf("%d", &in);
                tmp <<= 1;
                tmp |= (in&1);
            }
            rec[tmp] = true;
        }
        for(int i = 0; i < 16; ++ i){
            if(rec[i]){
                int m = ~i;
                
            }
        }
    }
    return 0;
}