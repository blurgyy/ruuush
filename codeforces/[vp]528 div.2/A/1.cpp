#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;

char s[maxn];

int main(){
    while(~scanf("%s", s)){
        int len = strlen(s);
        int mid = len - 1 >> 1;
        int shift = 1;
        printf("%c", s[mid]);
        while(true){
            if(mid+shift >= len) break;
            printf("%c", s[mid+shift]);
            if(mid-shift < 0) break;
            printf("%c", s[mid-shift]);
            shift ++;
        }
        printf("\n");
    }
    return 0;
}