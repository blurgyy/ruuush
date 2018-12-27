#include<bits/stdc++.h>
using namespace std;
const int maxn = 500010;

int n, a, o, x;
char op[5];

int get_val(char *s){
    int ret = 0, len = strlen(s);
    for(int i = 0; i < len; ++ i){
        ret *= 10;
        ret += s[i] - '0';
    }
    return ret;
}


int main(){
    for(int i = 0; i < 1024; ++ i){
        printf("%d %d\n", (i|1)&1017, i&1);
    }
    return 0;
}

/*
int main(){
    while(~scanf("%d\n", &n)){
        a = 1023;
        o = x = 0;
        while(n--){
            gets(op);
            //printf("op = %s\n", op);
            int val = get_val(op + 2);
            //printf("val = %d\n", val);
            if(op[0] == '&')a &= val;
            else if(op[0] == '|')o |= val;
            else x ^= val;
        }
        printf("3\n");
        printf("| %d\n^ %d\n& %d\n", a, o, x);
    }
    return 0;
}
*/
