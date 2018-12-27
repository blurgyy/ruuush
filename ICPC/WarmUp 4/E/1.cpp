#include<bits/stdc++.h>
using namespace std;
const int maxn = 10010;

char s[maxn];

int main(){
    freopen("easy.in", "r", stdin);
    freopen("easy.out", "w", stdout);
    while(~scanf("%s", s)){
        int len = strlen(s);
        for(int i = 0; i < len; ++ i){
            if(s[i] == '+'){
                printf("+");
                ++ i;
                for(; s[i] >= '0' && s[i] <= '9'; ++ i)
                    printf("%c", s[i]);
                -- i;
            }
            else if(s[i] == '-'){
                printf("-%c", s[++i]);
                int nlen = 0;
                for(; s[i+nlen] >= '0' && s[i+nlen] <= '9'; ++ nlen);
                if(nlen == 1)continue;
                else{
                    int top = i + nlen;
                    for(++ i; i < top; ++ i){
                        if(s[i] == '0')printf("+0");
                        else{
                            printf("+");
                            for(; i < top; ++ i)
                                printf("%c", s[i]);
                            break;
                        }
                    }
                    -- i;
                }
            }
            else{
                for(; s[i] >= '0' && s[i] <= '9'; ++ i)
                    if(s[i-1] == '+')printf("+%c", s[i]);
                    else printf("%c", s[i]);
                -- i;
            }
        }
        printf("\n");
    }
    return 0;
}