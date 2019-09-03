#include <bits/stdc++.h>
using namespace std;
const int maxn = 110;

char s[maxn];

int main(){
    while(~scanf("%s", s)){
        int len = strlen(s);
        bool flag = len & 1;
        for(int i = 1; i < len; ++ i){
            if(s[i] == '1'){
                flag = false;
                break;
            }
        }
        int ans = (len + 1) / 2 - flag;
        printf("%d\n", ans);
    }
    return 0;
}
