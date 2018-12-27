#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int q, n;
int ans[maxn], summands[maxn], p;

bool checkp(int n){
    if(n == 2)return false;
    if(!(n&1))return false;
    int top = sqrt(n);
    for(int i = 2; i <= top; ++ i)
        if(!(n % i))return false;
    return true;
}

void init(){
    p = 0;
    for(int i = 4; i < maxn; ++ i)
        if(!checkp(i))summands[p++] = i;
    printf("%d\n", p);
    /*memset(ans, 0, sizeof(ans));
    ans[8] = 1;
    for(int i = 12; i < maxn; i += 4){
        for(int j = 0; j < p; ++ j){
            if(i - summands[j] <= 7)break;
            ans[i] += ans[i - summands[j]] + 1;
        }
    }*/
    for(int i = 0; i < 30; ++ i)
        printf("%d\n", summands[i]);
}

int main(){
    init();
    while(~scanf("%d", &q)){
        while(q--){
            scanf("%d", &n);
            printf("%d\n", ans[n]);
        }
    }
    return 0;
}