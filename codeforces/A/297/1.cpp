#include<bits/stdc++.h>
using namespace std;
const int maxn = 1010;
const char out[2][5] = {"NO", "YES"};

int cnt, len;
char a[maxn], b[maxn];

int main(){
    while(~scanf("%s%s", a, b)){
        len = strlen(b) - 1;
        if(!len){
            printf("YES\n");
            continue;
        }
        cnt = 0;
        bool ans = true;
        int lena = strlen(a);
        if(lena >= len){
            int i;
            for(i = len; i >= 0; -- i){
                //printf("%c %c\n", b[i], a[lena-len+i-1]);
                if(b[i] != a[lena-len+i-1])break;
            }
            if(i == -1){
                printf("YES\n");
                continue;
            }
        }
        for(int i = 0; i <= len; ++ i)
            cnt += b[i] - '0';
        for(int i = len; i >= 0; -- i){
            if(b[i] - '0' != ((cnt-b[i]+'0') & 1))
                ans = false;
            cnt -= b[i] - '0';
        }
        printf("%s\n", out[ans]);
    }
    return 0;
}