/// B
#include <bits/stdc++.h>
using namespace std;
const int maxn = 500010;

int a, b;
char s[maxn];
int sp[maxn];
int wordlen[maxn];

int main(){
//    freopen("in.in", "r", stdin);
    // while(~scanf("%d%d", &a, &b)){
//        getchar();
        fgets(s, maxn, stdin);
        scanf("%d%d", &a, &b);
        int len = strlen(s);
        s[--len] = 0;
        int tmp = 0;
        for(int i = 0; i < len; ++ i){
            if(s[i] == ' ') sp[i] = tmp = i + 1;
            else sp[i] = tmp;
        }
        for(int i = 0; i < len; ++ i){
            if(i == 0 || s[i-1] == ' '){
                int j = i;
                while(true){
                    if(j == len || s[j] == ' '){
                        wordlen[i] = j-i;
                        i = j;
                        break;
                    }
                    ++ j;
                }
            }
        }
//        for(int i = 0; i < len; ++ i){
//            printf("sp[%d] = %d, wordlen[%d] = %d\n", i, sp[i], i, wordlen[i]);
//        }
        for(int i = a; i <= b; ++ i){
            int ans = 0, cnt = 0;
            for(int j = 0; j < len; j += i){
//                printf("j = %d\n", j);
                j = sp[j];
                ans += wordlen[j];
                cnt ++;
            }
            printf("%d\n", ans + cnt - 1);
        }

    return 0;
}

/**

its a long way to the top if you wanna rock n roll
13 16

*/





















