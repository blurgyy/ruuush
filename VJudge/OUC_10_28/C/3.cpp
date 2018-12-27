#include<bits/stdc++.h>
using namespace std;

int n, result[11], rec[11];
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
        memset(result, -1, sizeof(result));
        memset(rec, -1, sizeof(rec));
        gets(op);
        int val = get_val(op+2);
        for(int i = 0; i < 10; ++ i){
            if(op[0] == '&'){
                if((val>>i)&1)continue;
                result[i+1] = 0;
            }
            else if(op[0] == '|'){
                if((val>>1)&1)
                    result[i+1] = 1;
            }
            else{
                if((val>>1)&1)
                    result[i+1] = 2;
            }
        }
        for(int i = 10; i > 0; -- i)
            printf("%d", result[i]);
        printf("\n");
        n--;
        while(n--){
            gets(op);
            val = get_val(op + 2);
            for(int i = 0; i < 10; ++ i){
                if(op[0] == '&'){
                    if((val>>i)&1)continue;
                    result[i+1] = 0;
                }
                else if(op[0] == '|'){
                    if((val>>i)&1){
                        result[i+1] = 1;
                    }
                }
                else{
                    if((val>>i)&1){
                        if(result[i+1] == 0 || result[i+1] == 1){
                            rec[i+1] = result[i+1];
                        }
                        result[i+1] = result[i+1] == 2 ? 3 : 2;
                    }
                }
            }
        }
        for(int i = 10; i > 0; -- i)
            printf("%d", result[i]);
        printf("\n");
        int a = 1023, o = 0, x = 0;
        for(int i = 1; i < 11; ++ i){
            if(result[i] == 1)o |= (1<<(i-1));
            else if(result[i] == 0)a |= ~(1<<(i-1));
            else{
                if(rec[i] == 1)o |= (1<<(i-1));
                if(rec[i] == 0)a |= ~(1<<(i-1));
                if(result[i] == 2)x |= (1<<(i-1));
            }
        }
        printf("3\n| %d\n& %d\n^ %d\n", o, a, x);
    }
    return 0;
}
