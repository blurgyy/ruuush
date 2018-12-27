#include<bits/stdc++.h>
using namespace std;
const int maxn = 200010;

char s[maxn];
int n, a, b, cnt;

void proc(int pos, int flag){
    for(int i = 0; s[pos+i] == '.'; ++ i){
        if(i & 1) {
            if(flag == 1 && a > 0){
                s[pos+i] = 'A';
                a --;
                cnt ++;
            }
            if(flag == 0 && b > 0){
                s[pos+i] = 'B';
                b --;
                cnt ++;
            }
        }
        else {
            if(flag == 1 && b > 0){
                s[pos+i] = 'B';
                b --;
                cnt ++;
            }
            if(flag == 0 && a > 0){
                s[pos+i] = 'A';
                a --;
                cnt ++;
            }
        }
    }
}

int main(){
    while(~scanf("%d%d%d%s", &n, &a, &b, s)){
        cnt = 0;
        /*if(s[0] == '.'){
            if(a >= b){
                s[0] = 'A';
                a --;
            }
            else {
                s[0] = 'B';
                b --;
            }
            cnt ++;
        }*/
        for(int i = 0; i < n; ++ i){
            if(s[i] == '.'){
                if(a > 0 && b > 0){
                    if(a >= b && (i == 0 || s[i-1] != 'A'))proc(i, 0);
                    if(a < b && (i == 0 || s[i-1] != 'B'))proc(i, 1);
                }
                else if(a > 0 && (i == 0 || s[i-1] != 'A')){
                    proc(i, 0);
                }
                else if(b > 0 && (i == 0 || s[i-1] != 'B')){
                    proc(i, 1);
                }
            }
        }
        //printf("cnt = %d\n%s\n", cnt, s);
        printf("%d\n", cnt);
    }
    return 0;
}

/**

5 1 1
*...*

6 2 3
*...*.

11 3 10
.*....**.*.

3 2 3
***

*/