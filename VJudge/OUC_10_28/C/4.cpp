#include<bits/stdc++.h>
using namespace std;
const int maxn = 500010;

int n, mark[11];    /** 0: no operation;
                     *  1: | 1;
                     *  2: & 0;
                     *  3: ^ 1;
                     */
char op[5];

int get_val(char *s){
    int ret = 0;
    while(*s){
        ret *= 10;
        ret += *s - '0';
        ++ s;
    }
    return ret;
}

int main(){
    while(~scanf("%d\n", &n)){
        int v1 = 1023, v2 = 0;
        for(int i = 0; i < n; ++ i){
            gets(op);
            int val = get_val(op+2);
            if(op[0] == '&'){
                v1 &= val;
                v2 &= val;
            }
            else if(op[0] == '|'){
                v1 |= val;
                v2 |= val;
            }
            else {
                v1 ^= val;
                v2 ^= val;
            }
        }
        for(int i = 0; i < 10; ++ i){
            int t1 = (v1 >> i) & 1;
            int t2 = (v2 >> i) & 1;
            if(t1 == 1){
                if(t2 == 0)mark[i+1] = 0;
                else mark[i+1] = 1;
            }
            else{
                if(t2 == 0)mark[i+1] =2;
                else mark[i+1] = 3;
            }
        }
        int a = 1023, o = 0, x = 0;
        for(int i = 1; i < 11; ++ i){
            if(mark[i] == 0);
            else if(mark[i] == 1)
                o |= (1<<(i-1));
            else if(mark[i] == 2)
                a &= ~(1<<(i-1));
            else x |= (1<<(i-1));
        }
        printf("3\n| %d\n& %d\n^ %d\n", o, a, x);
    }
    return 0;
}
