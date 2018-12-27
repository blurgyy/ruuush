#include<bits/stdc++.h>
using namespace std;

char op[5];
int n, result[11];

int get_val(char *s){
    int ret = 0;
    while(*s){
        ret *= 10;
        ret += *s - '0';
        ++ s;
    }
    return ret;
}

int gel(int n){
    int ret = 0;
    while(n>>=1)++ ret;
    return ret + 1;
}

int main(){
    while(~scanf("%d\n", &n)){
        memset(result, -1, sizeof(result));
        gets(op);
        int val = get_val(op + 2);
        for(int i = 0; i < 10; ++ i){
            result[i+1] = ((val>>i) & 1);
        }
        n--;
        int len = 0;
        while(n--){
            gets(op);
            val = get_val(op + 2);
            len = max(len, gel(val));
            for(int i = 0; i < 10; ++ i){
                if(op[0] == '&')result[i+1] = result[i+1] & ((val>>i) & 1);
                else if(op[0] == '|')result[i+1] = result[i+1] | ((val>>i) & 1);
                else result[i+1] ^= (val>>i) & 1;
            }
        }
        //printf("len = %d\n", len);
        int a = 1023, o = 0;
        for(int i = 1; i <= len; ++ i)
            if(result[i])o |= (1<<(i-1));
            else a &= (~(1<<(i-1)));
        printf("2\n| %d\n& %d\n", o, a);
        /*
        for(int i = 10; i > 0; -- i)
            printf("%d", result[i]);
        printf("\n");
        */
    }
    return 0;
}
