#include <bits/stdc++.h>
using namespace std;
const int maxn = 200010;

struct STACK{
    int a[maxn];
    int sz;
    STACK(){init();}
    void init(){sz = 0;}
    void push(int x){a[sz++] = x;}
    void pop(){-- sz;}
    int top(){return a[sz-1];}
    int size(){return sz;}
}stk;

int n;
char s[maxn];

int main(){
    while(~scanf("%d%s", &n, s)){
        stk.init();
        int lbrac = 0, rbrac = 0;
        for(int i = 0; i < n; ++ i){
            if(s[i] == '('){
                ++ lbrac;
            }
            else if(s[i] == ')'){
                if(lbrac > 0) -- lbrac;
                else ++ rbrac;
            }
            else {
                printf("wtf");
            }
        }
        if(lbrac == rbrac && lbrac <= 1){
            printf("Yes\n");
        }
        else {
            printf("No\n");
        }
        // printf("%d %d\n", lbrac, rbrac);
    }
    return 0;
}

