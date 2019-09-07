#include <bits/stdc++.h>
using namespace std;
const int maxn = 210;

int a, b;
char digits[maxn];

int main(){
    while(~scanf("%d%d", &a, &b)){
        int c = a + b;
        if(c < 0) printf("-");
        c = abs(c);
        int p = 0, cnt = 0;
        while(c){
            if(cnt == 3){
                digits[p++] = ',';
                cnt = 0;
            }
            digits[p++] = '0' + c%10;
            c /= 10;
            cnt ++;
        }
        if(p == 0){
            digits[p++] = '0';
        }
        for(int i = p-1; i >= 0; -- i){
            printf("%c", digits[i]);
        }
        printf("\n");
    }
    return 0;
}
