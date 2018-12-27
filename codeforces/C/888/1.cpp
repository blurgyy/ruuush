#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;

char s[maxn];
int slen;
int rec[256];

bool check(int len){
    int prv;
    bool ans[256] = {false};
    for(int i = 'a'; i <= 'z'; ++ i){
        prv = -1;
        for(int j = 0; j < slen; ++ j){
            if(s[j] == i){
                ans[i] = true;
                if(j - prv <= len)
                    prv = j;
                else{
                    ans[i] = false;
                    continue;
                }
            }
        }
        if(slen - prv > len)
            ans[i] = false;
    }
    for(int i = 'a'; i <= 'z'; ++ i)
        if(ans[i])return true;
    return false;
}

int bs(int left = 1, int right = (slen >> 1) + 1){
    if(left >= right)return right;
    int mid((left + right) >> 1);
    //printf("mid = %d\n", mid);
    if(check(mid))return bs(left, mid);
    return bs(mid + 1, right);
}

int main(){
    freopen("in.in", "r", stdin);
    while(~scanf("%s", s)){
        slen = strlen(s);
        printf("%d\n", bs());
    }
    return 0;
}