#include <bits/stdc++.h>
using namespace std;
const int maxn = 200010;

int n, k;
char s[maxn];

int main(){
    while(~scanf("%d%d%s", &n, &k, s)){
        int len = strlen(s);
        int x = 0;
        for(int ch = 'a'; ch <= 'z'; ch += 1){
            int curlev = 0;
            for(int i = 0, cnt = 0; i < len; ++ i){
                if(s[i] != ch){
                    cnt = 0;
                }
                else {
                    cnt ++;
                }
                if(cnt == k){
                    curlev ++;
                    cnt = 0;
                }
            }
            x = max(x, curlev);
        }
        printf("%d\n", x);
    }
    return 0;
}