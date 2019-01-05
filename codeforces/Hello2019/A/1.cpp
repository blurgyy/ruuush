#include <bits/stdc++.h>
using namespace std;

char s[5], x[5];

int main(){
    while(~scanf("%s", s)){
        bool ans = false;
        for(int i = 0; i < 5; ++ i){
            scanf("%s", x);
            if(x[0] == s[0] || x[1] == s[1]){
                ans = true;
            }
        }
        if(ans) printf("YES\n");
        else printf("NO\n");
    }
}