#include<bits/stdc++.h>
using namespace std;
const int maxn = 310;

char cipher[maxn];

int main(){
    while(~scanf("%s", cipher+1)){
        int len = strlen(cipher+1) + 1;
        int ans = 0;
        for(int i = 1; i < len; ++ i){
            if(i%3 == 1 && cipher[i] != 'P')
                ++ ans;
            else if(i%3 == 2 && cipher[i] != 'E')
                ++ ans;
            else if(i%3 == 0 && cipher[i] != 'R')
                ++ ans;
        }
        printf("%d\n", ans);
    }
    return 0;
}
